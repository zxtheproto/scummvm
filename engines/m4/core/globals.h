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

/**
 * I know this is confusing, but the original game had two different Globals arrays
 */

#ifndef M4_CORE_GLOBALS_H
#define M4_CORE_GLOBALS_H

#include "common/array.h"
#include "common/serializer.h"
#include "m4/fileio/sys_file.h"
#include "m4/m4_types.h"

namespace M4 {

/**
 * Global entry constants
 */
enum {
	GLB_TIME = 0,
	GLB_WATCH_DOG = 1,
	GLB_MIN_Y = 2,
	GLB_MAX_Y = 3,
	GLB_MIN_SCALE = 4,
	GLB_MAX_SCALE = 5,
	GLB_SCALER = 6,

	GLB_TEMP_1 = 7,
	GLB_TEMP_2 = 8,
	GLB_TEMP_3 = 9,
	GLB_TEMP_4 = 10,
	GLB_TEMP_5 = 11,
	GLB_TEMP_6 = 12,
	GLB_TEMP_7 = 13,
	GLB_TEMP_8 = 14,
	GLB_TEMP_9 = 15,
	GLB_TEMP_10 = 16,
	GLB_TEMP_11 = 17,
	GLB_TEMP_12 = 18,
	GLB_TEMP_13 = 19,
	GLB_TEMP_14 = 20,
	GLB_TEMP_15 = 21,
	GLB_TEMP_16 = 22,
	GLB_TEMP_17 = 23,
	GLB_TEMP_18 = 24,
	GLB_TEMP_19 = 25,
	GLB_TEMP_20 = 26,
	GLB_TEMP_21 = 27,
	GLB_TEMP_22 = 28,
	GLB_TEMP_23 = 29,
	GLB_TEMP_24 = 30,
	GLB_TEMP_25 = 31,
	GLB_TEMP_26 = 32,
	GLB_TEMP_27 = 33,
	GLB_TEMP_28 = 34,
	GLB_TEMP_29 = 35,
	GLB_TEMP_30 = 36,
	GLB_TEMP_31 = 37,
	GLB_TEMP_32 = 38,

	GLB_SCRATCH_VARS = 7,		// 19-16 globals reserved for the compiler
	GLB_USER_VARS = 17		// 17+ globals for the applications programmer
};

constexpr int GLB_SHARED_VARS = 256;

/**
 * Globals array class.
 * This design is complicated by the fact that the original sometimes used it
 * to store pointers as well as numbers, assuming they were 32-bits. Because of this,
 * the new Globals class has to support both
 */
class Globals {
	struct Entry {
	private:
		uint32 &_numValue;
		void *&_ptrValue;
		bool &_isPtr;
	public:
		Entry(uint32 &numValue, void *&ptrValue, bool &isPtr) :
			_numValue(numValue), _ptrValue(ptrValue), _isPtr(isPtr) {
		}

		operator uint32() const {
			assert(!_isPtr);
			return _numValue;
		}
		template<class T>
		operator T *() const {
			assert(_isPtr);
			return (T *)_ptrValue;
		}
		Entry &operator=(uint32 val) {
			_isPtr = false;
			_numValue = val;
			return *this;
		}
		template<class T>
		Entry &operator=(T *val) {
			_isPtr = true;
			_ptrValue = val;
			return *this;
		}
	};
private:
	frac16 _numData[GLB_SHARED_VARS];
	void *_ptrData[GLB_SHARED_VARS];
	bool _isPtr[GLB_SCRATCH_VARS];
public:
	Globals();

	/**
	 * Dummy operator to allow for original code that did !globals to see if
	 * the globals array had been created
	 */
	bool operator!() const { return false; }

	/**
	 * Accesses the numeric array. Needed by several wscript methods
	 */
	frac16 *getData() {
		return _numData;
	}

	Entry operator[](uint idx) {
		assert(idx < GLB_SHARED_VARS);
		return Entry(_numData[idx], _ptrData[idx], _isPtr[idx]);
	}
};

} // namespace M4

#endif
