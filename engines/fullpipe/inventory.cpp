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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "fullpipe/fullpipe.h"

#include "fullpipe/utils.h"
#include "fullpipe/inventory.h"
#include "fullpipe/gameloader.h"
#include "fullpipe/statics.h"

namespace Fullpipe {

bool CInventory::load(MfcArchive &file) {
	debug(5, "CInventory::load()");

	_sceneId = file.readUint16LE();
	int numInvs = file.readUint32LE();

	for (int i = 0; i < numInvs; i++) {
		InventoryPoolItem *t = new InventoryPoolItem();
		t->id = file.readUint16LE();
		t->pictureObjectNormal = file.readUint16LE();
		t->pictureObjectId1 = file.readUint16LE();
		t->pictureObjectHover = file.readUint16LE();
		t->pictureObjectSelected = file.readUint16LE();
		t->flags = file.readUint32LE();
		t->field_C = 0;
		t->field_A = -536;
		_itemsPool.push_back(t);
	}

	return true;
}

int CInventory::getInventoryPoolItemIndexById(int itemId) {
	if (_itemsPool.size() <= 0)
		return -1;

	for (uint i = 0; i < _itemsPool.size(); i++) {
		if (_itemsPool[i]->id == itemId)
			return i;
	}

	return 0;
}

bool CInventory::setItemFlags(int itemId, int flags) {
	int idx = getInventoryPoolItemIndexById(itemId);

	if (idx < 0)
		return false;
	else
		_itemsPool[idx]->flags = flags;

	return true;
}

CInventory2::CInventory2() {
	_selectedId = -1;
	_field_48 = -1;
	_scene = 0;
	_picture = 0;
	_isInventoryOut = false;
	_isLocked = 0;
	_topOffset = -65;
}

bool CInventory2::loadPartial(MfcArchive &file) { // CInventory2_SerializePartially
	int numInvs = file.readUint32LE();

	for (int i = 0; i < numInvs; i++) {
		InventoryItem *t = new InventoryItem();
		t->itemId = file.readUint16LE();
		t->count = file.readUint16LE();
		_inventoryItems.push_back(t);
	}

	return true;
}

void CInventory2::addItem(int itemId, int count) {
	if (getInventoryPoolItemIndexById(itemId) >= 0)
		_inventoryItems.push_back(new InventoryItem(itemId, count));
}

void CInventory2::addItem2(StaticANIObject *obj) {
	if (getInventoryPoolItemIndexById(obj->_id) >= 0 && getInventoryPoolItemFieldCById(obj->_id) != 2) {
		addItem(obj->_id, 1);
		obj->hide();
	}
}

void CInventory2::removeItem(int itemId, int count) {
	warning("STUB: CInventory2::removeItem(%d, %d)", itemId, count);
}

void CInventory2::removeItem2(Scene *sceneObj, int itemId, int x, int y, int priority) {
	warning("STUB: void removeItem2(sc, %d, %d, %d, %d)", itemId, x, y, priority);
}

int CInventory2::getCountItemsWithId(int itemId) {
	int res = 0;

	for (uint i = 0; i < _inventoryItems.size(); i++) {
		if (_inventoryItems[i]->itemId == itemId)
			res += _inventoryItems[i]->count;
	}

	return res;
}

int CInventory2::getInventoryPoolItemFieldCById(int itemId) {
	for (uint i = 0; i < _itemsPool.size(); i++) {
		if (_itemsPool[i]->id == itemId)
			return _itemsPool[i]->field_C;
	}

	return 0;
}

void CInventory2::rebuildItemRects() {
	_scene = g_fullpipe->accessScene(_sceneId);

	if (!_scene)
		return;

	_picture = _scene->getBigPicture(0, 0);
	_picture->setAlpha(50);

	int itemX = 9;
	int itemY = 0;

	for (uint i = 0; i < _scene->_picObjList.size(); i++) {
		PictureObject *pic = (PictureObject *)_scene->_picObjList[i];

		for (uint j = 0; j < _itemsPool.size(); j++) {
			if (_itemsPool[j]->pictureObjectNormal == pic->_id) {
				if (pic->_okeyCode)
					_scene->deletePictureObject(pic);
				else
					pic->_flags &= 0xFFFB;
			}
		}
	}

	for (uint i = 0; i < _inventoryItems.size(); i++) {
		Common::Point point;

		int idx = getInventoryPoolItemIndexById(_inventoryItems[i]->itemId);

		InventoryIcon *icn = new InventoryIcon();

		icn->inventoryItemId = _itemsPool[idx]->id;
		
		icn->pictureObjectNormal = _scene->getPictureObjectById(_itemsPool[idx]->pictureObjectNormal, 0);
		icn->pictureObjectHover = _scene->getPictureObjectById(_itemsPool[idx]->pictureObjectHover, 0);
		icn->pictureObjectSelected = _scene->getPictureObjectById(_itemsPool[idx]->pictureObjectSelected, 0);

		icn->pictureObjectNormal->getDimensions(&point);

		if (_itemsPool[idx]->flags & 0x10000) {
			icn->x1 = 730;
			icn->y1 = itemY;
			icn->x2 = point.x + 730;
			icn->y2 = point.y + itemY + 10;
		} else {
			icn->x1 = itemX;
			icn->y1 = itemY;
			icn->x2 = itemX + point.x;
			itemX = icn->x2 + 1;
			icn->y2 = point.y + itemY + 10;
		}

		_inventoryIcons.push_back(icn);

		if (itemX >= 2 * (icn->x1 - icn->x2) + 800) {
			itemX = 9;
			itemY = icn->y2 + 1;
		}
	}
}

void CInventory2::draw() {
	if (!_scene)
		return;

	int oldScLeft = g_fullpipe->_sceneRect.left;
	int oldScTop = g_fullpipe->_sceneRect.top;

	g_fullpipe->_sceneRect.top = -_topOffset;
	g_fullpipe->_sceneRect.left = 0;

	_picture->draw(-1, -1, 0, 0);

	for (uint i = 0; i < _inventoryIcons.size(); i++) {
		InventoryIcon *icn = _inventoryIcons[i];

		if (icn->isSelected) {
			icn->pictureObjectSelected->drawAt(icn->x1, icn->y1 + 10);
		} else {
			if (icn->isMouseHover)
				icn->pictureObjectHover->drawAt(icn->x1, icn->y1 + 10);
			else
				icn->pictureObjectNormal->drawAt(icn->x1, icn->y1 + 10);
		}
    }

	if (!_isInventoryOut)
		goto LABEL_30;

	int v10, v11, v12;

	if (_topOffset != -10) {
		if (_topOffset < -10) {
			v10 = -10;
			goto LABEL_13;
		}
		if (_topOffset + 10 >= 20) {
			v11 = -20;
cont:
			_topOffset += v11;
			goto reset;
		}
		v12 = -10;
		goto LABEL_25;
	}
	if (!_isInventoryOut) {
LABEL_30:
		if (_topOffset != -65) {
			if (_topOffset < -65) {
				v10 = -65;
LABEL_13:
				v11 = v10 - _topOffset;
				if (v11 >= 20)
					v11 = 20;
				goto cont;
			}
			if (_topOffset + 65 >= 20) {
				v11 = -20;
				goto cont;
			}
			v12 = -65;
LABEL_25:
			v11 = v12 - _topOffset;
			goto cont;
		}
	}

reset:

	g_fullpipe->_sceneRect.top = oldScTop;
	g_fullpipe->_sceneRect.left = oldScLeft;

}

void CInventory2::slideIn() {
	_isInventoryOut = false;

	ExCommand *ex = new ExCommand(0, 17, 65, 0, 0, 0, 1, 0, 0, 0);

	ex->_field_2C = 10;
	ex->_field_14 = _isInventoryOut;
	ex->_field_20 = !_isInventoryOut;
	ex->_excFlags |= 3;
	ex->postMessage();
}

void CInventory2::slideOut() {
	_isInventoryOut = true;

	ExCommand *ex = new ExCommand(0, 17, 65, 0, 0, 0, 1, 0, 0, 0);

	ex->_field_2C = 10;
	ex->_field_14 = _isInventoryOut;
	ex->_field_20 = !_isInventoryOut;
	ex->_excFlags |= 3;
	ex->postMessage();
}

int CInventory2::handleLeftClick(ExCommand *cmd) {
	warning("STUB: CInventory2::handleLeftClick()");

	return 0;
}

int CInventory2::unselectItem(bool flag) {
	warning("STUB: CInventory2::unselectItem()");

	return 0;
}

int CInventory2::getHoveredItem(Common::Point *point) {
	int selId = getSelectedItemId();

	if (point->y <= 20 && !_isInventoryOut && !_isLocked )
		slideOut();

	if (!selId && point->y >= 55) {
		if (!_isInventoryOut)
			return 0;

		if (!_isLocked)
			slideIn();
	}

	if (!_isInventoryOut)
		return 0;

	for (uint i = 0; i < _inventoryIcons.size(); i++) {
		InventoryIcon *icn = _inventoryIcons[i];
		if (selId ||
			point->x < icn->x1 ||
			point->x > icn->x2 ||
			point->y < _topOffset + icn->y1 ||
			point->y > _topOffset + icn->y2) {
			icn->isMouseHover = 0;
		} else {
			icn->isMouseHover = 1;
			return icn->inventoryItemId;
		}
    }

	return 0;
}

} // End of namespace Fullpipe
