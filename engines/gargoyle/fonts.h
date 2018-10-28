/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#ifndef GARGOYLE_FONTS_H
#define GARGOYLE_FONTS_H

#include "gargoyle/glk_types.h"
#include "common/str.h"
#include "common/ustr.h"
#include "graphics/font.h"

namespace Gargoyle {

#define FONTS_TOTAL 8

enum FACES { MONOR, MONOB, MONOI, MONOZ, PROPR, PROPB, PROPI, PROPZ };
enum TYPES { MONOF, PROPF };
enum STYLES { FONTR, FONTB, FONTI, FONTZ };

class Fonts {
private:
	Graphics::ManagedSurface *_surface;
	Graphics::Font *_fontTable[FONTS_TOTAL];
private:
	Graphics::Font *loadFont(FACES face, double size, double aspect, int style);
public:
	/**
	 * Get the index/id of a font by name
	 */
	static FACES getId(const Common::String &name);
public:
	/**
	 * Constructor
	 */
	Fonts(Graphics::ManagedSurface *surface);

	/**
	 * Destructor
	 */
	virtual ~Fonts();

	int drawString(const Common::Point &pos, int fontIdx, const byte *rgb, const Common::String &text, int spw = 0);

	int drawStringUni(const Common::Point &pos, int fontIdx, const byte *rgb, const Common::U32String &text, int spw = 0);

	size_t stringWidth(int fontIdx, const Common::String &text, int spw = -1);

	size_t stringWidthUni(int fontIdx, const Common::U32String &text, int spw = -1);
};

} // End of namespace Gargoyle

#endif
