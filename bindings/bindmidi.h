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
#ifndef BINDMIDI_H
#define BINDMIDI_H

#include "squirrel.h"

namespace binding
{
// object references to types in this package
extern HSQOBJECT MidiABCReaderObject;
extern HSQOBJECT MidiInputObject;
extern HSQOBJECT MidiNoteObject;
extern HSQOBJECT MidiControlObject;
extern HSQOBJECT MidiInputBufferObject;
extern HSQOBJECT MidiPatternObject;
extern HSQOBJECT MidiTuneObject;
extern HSQOBJECT MidiOutputObject;
extern HSQOBJECT MidiProgramChangeObject;
extern HSQOBJECT MidiDrumTabReaderObject;
}

#endif // BINDMIDI_H