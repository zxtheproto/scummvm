/* ResidualVM - A 3D game interpreter
 *
 * ResidualVM is the legal property of its developers, whose names
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
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	 See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

/*
 * This file is based on WME.
 * http://dead-code.org/redir.php?target=wme
 * Copyright (c) 2003-2013 Jan Nedoma and contributors
 */

#ifndef WINTERMUTE_AD_GEOM_EXT_NODE_H
#define WINTERMUTE_AD_GEOM_EXT_NODE_H

#include "engines/wintermute/ad/ad_types.h"
#include "engines/wintermute/base/base.h"

namespace Wintermute {

class AdGeomExtNode : public BaseClass {
public:
	AdGeomExtNode(BaseGame *inGame);
	virtual ~AdGeomExtNode();
	bool loadBuffer(byte *buffer, bool complete);

	bool setupNode(const char *namePattern, TGeomNodeType type = GEOM_GENERIC, bool receiveShadows = false);
	bool matchesName(const char *name);

	bool _receiveShadows;
	TGeomNodeType _type;

private:
	char *_namePattern;
};

} // namespace Wintermute

#endif
