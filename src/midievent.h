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
#ifndef MIDIEVENT_H
#define MIDIEVENT_H

#include "event.h"

namespace bipscript {
namespace midi {

class Event : public bipscript::Event
{
    unsigned char type;
    unsigned char databyte1;
    unsigned char databyte2;
public:
    static const unsigned char TYPE_NOTE_OFF = 0x80;
    static const unsigned char TYPE_NOTE_ON = 0x90;
    static const unsigned char TYPE_CONTROL = 0xB0;
    static const unsigned char TYPE_PITCH_BEND = 0xE0;
    uint8_t channel;
    Event() : bipscript::Event(1, 1, 1) {}
    Event(Position &position, int databyte1, int databyte2, int type, unsigned char channel);
    Event(const Event&);
    friend std::ostream& operator<< (std::ostream &out, Event &evt);
    void setPosition(int bar, int position, int division) {
        Position(bar, position, division);
    }
    void setChannel(uint8_t channel) {
        this->channel = channel;
    }
    unsigned char getDatabyte1() {
        return databyte1;
    }
    void setDatabyte1(unsigned char databyte) {
        this->databyte1 = databyte;
    }
    unsigned char getDatabyte2() {
        return databyte2;
    }
    unsigned char getType() {
        return type;
    }
    uint8_t dataSize();
    void pack(void *buffer);
    void unpack(const uint8_t *buffer, size_t size);
    bool matches(int type);
    bool matches(int type, int databyte1, int low, int high);
};

}}

#endif // MIDIEVENT_H
