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

/*
 * This code is based on Broken Sword 2.5 engine
 *
 * Copyright (c) Malte Thiesen, Daniel Queteschiner and Michael Elsdoerfer
 *
 * Licensed under GNU GPL v2
 *
 */

#ifndef SWORD25_ROOTRENDEROBJECT_H
#define SWORD25_ROOTRENDEROBJECT_H

// Includes
#include "sword25/kernel/common.h"
#include "sword25/gfx/renderobject.h"

namespace Sword25 {

// -----------------------------------------------------------------------------
// Forward Declarations
// -----------------------------------------------------------------------------

class Kernel;

// Klassendefinition
class RenderObjectManager;

class RootRenderObject : public RenderObject {
	friend class RenderObjectManager;

private:
	RootRenderObject(RenderObjectManager *managerPtr, int width, int height) :
		RenderObject(RenderObjectPtr<RenderObject>(), TYPE_ROOT) {
		_managerPtr = managerPtr;
		_width = width;
		_height = height;
	}

protected:
	bool doRender(RectangleList *updateRects) override {
		return true;
	}
};

} // End of namespace Sword25

#endif
