
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

#ifndef BAGEL_BOFLIB_STDINC_H
#define BAGEL_BOFLIB_STDINC_H

#include "common/scummsys.h"
#include "bagel/boflib/boffo.h"

namespace Bagel {

#define MAKEuint32(a, b) MAKELPARAM(a, b)
#define MAKERGB(R, G, B) ((uint32)(((uint32)((byte)(R))) | (((uint32)((byte)(G))) << 8) | (((uint32)((byte)(B))) << 16)))

/*
 * Math Function Macros
 */
#define isodd(x) ((x)&1)   /* Returns 1 if number is odd  */
#define iseven(x) !((x)&1) /* Returns 1 if number is even */
#ifndef min
#define min(x, y) (x < y ? x : y) /* returns the min of x and y */
#endif
#ifndef max
#define max(x, y) (x > y ? x : y) /* returns the max of x and y */
#endif

/*
 * normal types
 */
typedef void *(*BOFCALLBACK)(int, void *);

typedef long Fixed;

/*
 * extended types
 */
struct ST_SIZE {
	int cx;
	int cy;
};

struct ST_POINT {
	int x;
	int y;
};

struct ST_RECT {
	int left;
	int top;
	int right;
	int bottom;
};

struct VECTOR {
	double x;
	double y;
	double z;
};

struct WINDOWPOS {
	void *hwnd = nullptr;
	void *hwndInsertAfter = nullptr;
	int x = 0;
	int y = 0;
	int cx = 0;
	int cy = 0;
	uint32 flags = 0;
};


#ifndef LOBYTE
#define LOBYTE(w) ((byte)(w))
#endif
#ifndef HIBYTE
#define HIBYTE(w) ((byte)(((uint32)(w) >> 8) & 0xFF))
#endif
#ifndef LOWORD
#define LOWORD(l) ((uint16)(uint32)(l))
#endif
#ifndef HIWORD
#define HIWORD(l) ((uint16)((((uint32)(l)) >> 16) & 0xFFFF))
#endif

#define MAKE_WORD(a, b) ((uint16)(((byte)(a)) | ((uint16)((byte)(b))) << 8))
#define MAKE_LONG(low, high) ((int32)(((uint16)(low)) | (((uint32)((uint16)(high))) << 16)))

/* for big-endian platforms (i.e. MAC) */
#define SWAPWORD(x) MAKE_WORD(HIBYTE(x), LOBYTE(x))
#define SWAPLONG(x) MAKE_LONG(SWAPWORD(HIWORD(x)), SWAPWORD(LOWORD(x)))

/*
 * Boolean types
 */
enum {
	YES = 1,
	NO = 0
};
#ifndef TRUE
#define TRUE true
#define FALSE false
#endif
typedef bool boolEAN;

#ifndef MAX_FNAME
#define MAX_FNAME 256
#endif

#define MAX_DIRPATH 256

/**
 * Displays assertion failure
 * @param bExpression       Expression to evaluate (fail if false)
 * @param nLine             Source code line number of assertion
 * @param pszSourceFile     Source code file of assertion
 * @param pszTimeStamp      Time and date version of source file
 */
extern void BofAssert(bool bExpression, int nLine, const char *pszSourceFile, const char *pszTimeStamp);

#ifdef _DEBUG
#define Assert(f) assert(f)
#else

#ifdef __TIMESTAMP__
#define Assert(f) BofAssert(f, __LINE__, __FILE__, __TIMESTAMP__)
#else
#define Assert(f) BofAssert(f, __LINE__, __FILE__, nullptr)
#endif /* __TIMESTAMP__ */

#endif /* _DEBUG */

#define Abort(p) BofAbort(p, __FILE__, __LINE__);

#define BOF_MALLOC(nSize) BofAlloc(nSize)
#define BOF_ALLOC(nSize) BofAlloc(nSize)
#define BOF_CALLOC(nElem, nSize) BofCAlloc(nElem, nSize)
#define BOF_FREE(pvPointer) BofFree(pvPointer)
#define BOF_REALLOC(pvPointer, nSize) BofReAlloc(pvPointer, nSize)

} // namespace Bagel

#endif
