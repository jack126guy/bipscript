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
#ifndef SYSTEMPACKAGE_H
#define SYSTEMPACKAGE_H

namespace bipscript {
namespace system {

class System
{
    static int argumentCount;
    static char **argumentVector;
public:
    static void setArguments(int argc, char **argv) {
        argumentCount = argc;
        argumentVector = argv;
    }
    static const char *getArgument(int index) {
        if(index >= argumentCount) {
            return 0;
        }
        return argumentVector[index];
    }
};

}}

#endif // SYSTEMPACKAGE_H
