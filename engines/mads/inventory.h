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

#ifndef MADS_INVENTORY_H
#define MADS_INVENTORY_H

#include "common/scummsys.h"
#include "common/array.h"

namespace MADS {

class MADSEngine;

class InventoryObject {
public:
	int _descId;
	int _roomNumber;
	int _article;
	int _vocabCount;
	struct {
		int _actionFlags1;
		int _actionFlags2;
		int _vocabId;
	} _vocabList[3];
	char _mutilateString[10];	// ???
	const byte *_objFolder;		// ???

	/**
	 * Loads the data for a given object
	 */
	void load(Common::SeekableReadStream &f);
};

class InventoryObjects: public Common::Array<InventoryObject> {
private:
	MADSEngine *_vm;
public:
	Common::Array<int> _inventoryList;

	/** 
	 * Constructor
	 */
	InventoryObjects(MADSEngine *vm): _vm(vm) {}

	/**
	 * Loads the game's object list
	 */
	void load();

	/**
	 * Returns the inventory item from the player's inventory
	 */
	InventoryObject &getItem(int itemIndex) {
		return (*this)[_inventoryList[itemIndex]];
	}

	/**
	 * Set the associated data? pointer with an inventory object
	 */
	void setData(int objIndex, int id, const byte *p);

	/**
	 * Sets the room number
	 */
	void setRoom(int objectId, int roomNumber);

	/**
	 * Returns true if a given object is in the player's current scene
	 */
	bool isInRoom(int objectId) const;
};

} // End of namespace MADS

#endif /* MADS_INVENTORY_H */
