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

#include "titanic/moves/trip_down_canal.h"

namespace Titanic {

BEGIN_MESSAGE_MAP(CTripDownCanal, CMovePlayerTo)
	ON_MESSAGE(MouseButtonDownMsg)
END_MESSAGE_MAP()

CTripDownCanal::CTripDownCanal() : CMovePlayerTo() {
}

void CTripDownCanal::save(SimpleFile *file, int indent) {
	file->writeNumberLine(1, indent);
	CMovePlayerTo::save(file, indent);
}

void CTripDownCanal::load(SimpleFile *file) {
	file->readNumber();
	CMovePlayerTo::load(file);
}

bool CTripDownCanal::MouseButtonDownMsg(CMouseButtonDownMsg *msg) {
	if (stateGetSeason() == SEASON_WINTER) {
		petDisplayMessage(CANAL_CLOSED_FOR_WINTER);
	} else if (getGameManager()) {
		changeView(_destination);
	}

	return true;
}

} // End of namespace Titanic
