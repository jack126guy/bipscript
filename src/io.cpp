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

#include "io.h"

#include <fstream>
#include <stdexcept>

namespace bipscript {
namespace io {

const char *File::readAll()
{
    std::ifstream stream;
    stream.open(name);
    if(!stream) {
        throw std::logic_error("could not read file " + name);
    }
    stream.seekg(0, std::ios::end);
    length = stream.tellg();
    if(buffer) { delete[] buffer; }
    buffer = new char[length + 1];
    stream.seekg(0, std::ios::beg);
    stream.read(buffer, length);
    stream.close();
    buffer[length] = '\0';
    return buffer;
}

}}