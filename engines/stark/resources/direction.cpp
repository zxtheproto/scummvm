/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "engines/stark/resources/direction.h"

#include "engines/stark/formats/xrc.h"

namespace Stark {
namespace Resources {

Direction::~Direction() {
}

Direction::Direction(Object *parent, byte subType, uint16 index, const Common::String &name) :
		Object(parent, subType, index, name),
		_field_34(0),
		_field_38(0),
		_field_3C(0) {
	_type = TYPE;
}

void Direction::readData(Formats::XRCReadStream *stream) {
	_field_34 = stream->readUint32LE();
	_field_38 = stream->readUint32LE();
	_field_3C = stream->readUint32LE();
}

void Direction::printData() {
	debug("field_34: %d", _field_34);
	debug("field_38: %d", _field_38);
	debug("field_3C: %d", _field_3C);
}

} // End of namespace Resources
} // End of namespace Stark
