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

#include "common/scummsys.h"
#include "bagel/boflib/llist.h"

namespace Bagel {

CLList::CLList() {
	m_pPrev = nullptr;
	_pNext = nullptr;
	m_pData = nullptr;
}

CLList::CLList(void *pObj) {
	m_pPrev = nullptr;
	_pNext = nullptr;
	m_pData = pObj;
}

CLList::~CLList() {
	this->Delete();
}

void CLList::addToHead(CLList *pNewList) {
	// Can't insert a nullptr record into the list
	assert(pNewList != nullptr);

	CLList *pListHead = GetHead();

	pNewList->_pNext = pListHead;
	pNewList->m_pPrev = nullptr;

	pListHead->m_pPrev = pNewList;
}

void CLList::addToTail(CLList *pNewList) {
	// Can't insert a nullptr record into the list
	assert(pNewList != nullptr);

	CLList *pListTail = GetTail();

	pNewList->m_pPrev = pListTail;
	pNewList->_pNext = nullptr;

	pListTail->_pNext = pNewList;
}

void CLList::Insert(CLList *pList) {
	// Can't insert a nullptr record into the list
	assert(pList != nullptr);

	pList->m_pPrev = this;
	pList->_pNext = _pNext;

	if (_pNext != nullptr)
		_pNext->m_pPrev = pList;

	_pNext = pList;
}

void CLList::Delete() {
	if (m_pPrev != nullptr)
		m_pPrev->_pNext = _pNext;

	if (_pNext != nullptr)
		_pNext->m_pPrev = m_pPrev;

	m_pPrev = _pNext = nullptr;
}

void CLList::MoveToHead() {
	CLList *pHead = GetHead();
	assert(pHead != nullptr);

	if (this != pHead) {
		Delete();
		pHead->addToHead(this);
	}
}

void CLList::MoveToTail() {
	CLList *pTail = GetTail();
	assert(pTail != nullptr);

	if (this != pTail) {
		Delete();
		pTail->addToTail(this);
	}
}

void CLList::MoveLeft() {
	if (m_pPrev != nullptr) {

		CLList *pPrev = m_pPrev->GetPrev();
		if (pPrev != nullptr) {
			Delete();
			pPrev->Insert(this);
		} else {
			MoveToHead();
		}
	}
}

void CLList::MoveRight() {
	CLList *pNext = _pNext;

	if (pNext != nullptr) {

		this->Delete();
		pNext->Insert(this);
	}
}

void CLList::FlushList() {

	CLList *pList = GetHead();

	// Something is wrong if the head is invalid
	assert(pList != nullptr);

	while (pList != nullptr) {
		CLList *pTmpList = pList->_pNext;

		// Don't delete myself
		if (pList != this)
			delete pList;

		pList = pTmpList;
	}
}

CLList *CLList::GetHead() {
	CLList *pList = this;
	while (pList->m_pPrev != nullptr)
		pList = pList->m_pPrev;

	return pList;
}

CLList *CLList::GetTail() {
	CLList *pList = this;
	while (pList->_pNext != nullptr)
		pList = pList->_pNext;

	return pList;
}

} // namespace Bagel
