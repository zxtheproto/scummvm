/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
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

#include "director/director.h"
#include "director/castmember/palette.h"

namespace Director {

PaletteCastMember::PaletteCastMember(Cast *cast, uint16 castId, Common::SeekableReadStreamEndian &stream, uint16 version)
	: CastMember(cast, castId, stream) {
	_type = kCastPalette;
	_palette = nullptr;
}

Common::String PaletteCastMember::formatInfo() {
	Common::String result;
	if (_palette) {
		result = "data: ";
		for (size_t i = 0; i < (size_t)_palette->length; i++) {
			result += Common::String::format("%02X%02X%02X", _palette->palette[3 * i], _palette->palette[3 * i + 1], _palette->palette[3 * i + 2]);
		}
	}
	return result;
}

}
