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

#include "bindtypes.h"

#include "audioport.h"
#include "bindaudio.h"
#include "bindlv2.h"
#include "bindmidi.h"
#include "lv2plugin.h"
#include "midiport.h"
#include "mixer.h"

namespace binding
{

    AudioSource *getAudioSource(HSQUIRRELVM &vm, int index) {
        SQUserPointer sourcePtr;
        if (!SQ_FAILED(sq_getinstanceup(vm, index, (SQUserPointer*)&sourcePtr, &AudioMixerObject))) {
            return static_cast<Mixer*>(sourcePtr);
        }
        if (!SQ_FAILED(sq_getinstanceup(vm, index, (SQUserPointer*)&sourcePtr, &AudioSystemInObject))) {
            return static_cast<AudioInputPort*>(sourcePtr);
        }
        if (!SQ_FAILED(sq_getinstanceup(vm, index, (SQUserPointer*)&sourcePtr, &AudioStereoInObject))) {
            return static_cast<AudioStereoInput*>(sourcePtr);
        }
        if (!SQ_FAILED(sq_getinstanceup(vm, index, (SQUserPointer*)&sourcePtr, &Lv2PluginObject))) {
            return static_cast<Lv2Plugin*>(sourcePtr);
        }
        return 0;
    }
    
    MidiMessage *getMidiMessage(HSQUIRRELVM &vm, int index) {
        SQUserPointer sourcePtr;
        if (!SQ_FAILED(sq_getinstanceup(vm, index, (SQUserPointer*)&sourcePtr, &MidiNoteOnObject))) {
            return static_cast<NoteOn*>(sourcePtr);
        }
        if (!SQ_FAILED(sq_getinstanceup(vm, index, (SQUserPointer*)&sourcePtr, &MidiNoteOffObject))) {
            return static_cast<NoteOff*>(sourcePtr);
        }
        if (!SQ_FAILED(sq_getinstanceup(vm, index, (SQUserPointer*)&sourcePtr, &MidiControlObject))) {
            return static_cast<Control*>(sourcePtr);
        }
        if (!SQ_FAILED(sq_getinstanceup(vm, index, (SQUserPointer*)&sourcePtr, &MidiPitchBendObject))) {
            return static_cast<PitchBend*>(sourcePtr);
        }
        if (!SQ_FAILED(sq_getinstanceup(vm, index, (SQUserPointer*)&sourcePtr, &MidiProgramChangeObject))) {
            return static_cast<ProgramChange*>(sourcePtr);
        }
        return 0;
    }
    
    MidiSource *getMidiSource(HSQUIRRELVM &vm, int index) {
        SQUserPointer sourcePtr;
        if (!SQ_FAILED(sq_getinstanceup(vm, index, (SQUserPointer*)&sourcePtr, &Lv2PluginObject))) {
            return static_cast<Lv2Plugin*>(sourcePtr);
        }
        if (!SQ_FAILED(sq_getinstanceup(vm, index, (SQUserPointer*)&sourcePtr, &MidiSystemInObject))) {
            return static_cast<MidiInputPort*>(sourcePtr);
        }
        return 0;
    }
    
    MidiSink *getMidiSink(HSQUIRRELVM &vm, int index) {
        SQUserPointer sourcePtr;
        if (!SQ_FAILED(sq_getinstanceup(vm, index, (SQUserPointer*)&sourcePtr, &Lv2PluginObject))) {
            return static_cast<Lv2Plugin*>(sourcePtr);
        }
        if (!SQ_FAILED(sq_getinstanceup(vm, index, (SQUserPointer*)&sourcePtr, &MidiSystemOutObject))) {
            return static_cast<MidiOutputPort*>(sourcePtr);
        }
        return 0;
    }
    
}