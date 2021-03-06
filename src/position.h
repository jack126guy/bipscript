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
#ifndef POSITION_H
#define POSITION_H

#include <jack/types.h>
#include <ostream>

namespace bipscript {

class Duration
{
    static const uint32_t MAX_DENOMINATOR = 384000; // frames in a measure 44.1k 60bpm
protected:
    unsigned int whole;
    unsigned int position;
    unsigned int division;
    void normalize();
public:
    Duration(unsigned int whole, unsigned int position, unsigned int division);
    friend std::ostream& operator<< (std::ostream &out, Duration &duration);
    // accessors
    unsigned int getBar() const {
        return whole;
    }
    void setBar(unsigned int bar) {
        this->whole = bar;
    }
    unsigned int getPosition() const {
        return position;
    }
    void setPosition(unsigned int position) {
        this->position = position;
    }
    unsigned int getDivision() const {
        return division;
    }
    void setDivision(unsigned int division) {
        this->division = division;
    }
    // operators
    bool operator< (Duration &other);
    bool operator<= (Duration &other);
    const Duration operator- (const Duration &other);
};

class Position : public Duration
{
public:
    Position() : Duration(0, 0, 1) {}
    Position(unsigned int bar, unsigned int position, unsigned int division);
    friend std::ostream& operator<< (std::ostream &out, Position &pos);
    long calculateFrameOffset(jack_position_t &pos);
    Position &operator +=(const Duration &duration);
    const Position operator+ (const Duration &duration) {
        return Position(*this) += duration;
    }
};

}

#endif // POSITION_H
