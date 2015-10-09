#ifndef OBJECTCACHE_H
#define OBJECTCACHE_H
/*
 * This file is part of Bipscript.
 *
 * Bipscript is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Bipscript is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Bipscript.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <map>
#include <set>
#include <jack/types.h>

#include "listable.h"
#include "objectcollector.h"

class ObjectCache
{
public:
    /**
     * Run at the end of every process cycle to update objects that would otherwise block.
     *
     * Runs in the process thread.
     */
    virtual void process(bool rolling, jack_position_t &pos, jack_nframes_t nframes, jack_nframes_t time) = 0;
    /**
     * Called after the script has completed so factories can reset for the next run.
     *
     * Runs in the script thread.
     */
    virtual bool scriptComplete() = 0;
    /**
     * Called when a reposition has been requested so objects can flush/recycle queued events.
     *
     * Runs in the process thread.
     */
    virtual void reposition() = 0;
};

template <class K, class T> class ProcessorCache : public ObjectCache
{
    std::map<K, T*> instanceMap;
    std::set<T*> activeScriptObjects;
    QueueList<T> activeProcessObjects;
    boost::lockfree::spsc_queue<T*> deletedObjects;
    virtual T *createObject(K) { return 0; }
    virtual void scriptReset() {}
protected:
    ProcessorCache() : activeProcessObjects(16), deletedObjects(4) {}
    T *getObject(K key)
    {
        T *obj = instanceMap[key];
        if (!obj) {
            obj = createObject(key);
            instanceMap[key] = obj;
            activeProcessObjects.add(obj);
        }
        activeScriptObjects.insert(obj);
        return obj;
    }
    /**
     * used by subclasses that don't implement createObject
     */
    T *findObject(K key) {
        T *ret = instanceMap[key];
        if(ret) {
            activeScriptObjects.insert(ret);
        }
        return ret;
    }
    /**
     * used by subclasses that don't implement createObject
     */
    void registerObject(std::string &key, T *obj) {
        activeScriptObjects.insert(obj);
        activeProcessObjects.add(obj);
        instanceMap[key] = obj;
    }

public:
    void process(bool rolling, jack_position_t &pos, jack_nframes_t nframes, jack_nframes_t time)
    {
        // remove deleted objects
        T *done;
        while(deletedObjects.pop(done)) {
            activeProcessObjects.remove(done);
            ObjectCollector::instance()->recycle(done);
        }
        // process active ports
        T *obj = activeProcessObjects.getFirst();
        while(obj) {
            obj->processAll(rolling, pos, nframes, time);
            obj = activeProcessObjects.getNext(obj);
        }
    }
    /**
      * Restore cache state after script has completed.
      *
      * Runs in script thread.
      *
      */
    bool scriptComplete() {
        bool activeObjects = false;
        // loop over cached ports
        for(auto iterator = instanceMap.begin(); iterator != instanceMap.end();) {
            T *obj = iterator->second;
            // port was used in the last script run?
            auto it = activeScriptObjects.find(obj);
            if(it != activeScriptObjects.end()) {
                std::cout << typeid(T).name() << " was used in the last run: " << iterator->first << std::endl;
                activeScriptObjects.erase(it);
                activeObjects = true;
                iterator++;
            } else {
                // remove port from map and audio engine
                std::cout << typeid(T).name() << " NOT used in the last run: " << iterator->first << std::endl;
                iterator = instanceMap.erase(iterator);
                while(!deletedObjects.push(obj));
            }
        }
        scriptReset();
        return activeObjects;
    }

    void reposition()
    {
        // remove deleted ports
        T *done;
        while(deletedObjects.pop(done)) {
            activeProcessObjects.remove(done);
            ObjectCollector::instance()->recycle(done);
        }
        // loop over MIDI output ports and reset
        T *obj = activeProcessObjects.getFirst();
        while(obj) {
            obj->reposition();
            obj = activeProcessObjects.getNext(obj);
        }
    }

};

#endif // OBJECTCACHE_H
