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
 * This code is based on the CRAB engine
 *
 * Copyright (c) Arvind Raja Yadav
 *
 * Licensed under MIT
 *
 */

#include "crab/crab.h"
#include "crab/ui/ReplyButton.h"

namespace Crab {

using namespace pyrodactyl::ui;
using namespace pyrodactyl::text;
using namespace pyrodactyl::image;

void ReplyButton::load(rapidxml::xml_node<char> *node) {
	Button::load(node);
	orig = *this;

	if (nodeValid("text", node)) {
		rapidxml::xml_node<char> *tenode = node->first_node("text");

		loadColor(col_b, tenode->first_node("col_b"));
		loadColor(col_s, tenode->first_node("col_s"));
		loadColor(col_h, tenode->first_node("col_h"));
		loadNum(font, "font", tenode);
		loadAlign(align, tenode);

		if (nodeValid("line_size", tenode))
			line_size.load(tenode->first_node("line_size"));
	}
}

void ReplyButton::draw(const int &XOffset, const int &YOffset) {
	if (_visible) {
		if (_mousePressed)
			g_engine->_textManager->draw(x + XOffset, y + YOffset, text, col_s, font, align, line_size.x, line_size.y);
		else if (_hoverMouse || _hoverKey)
			g_engine->_textManager->draw(x + XOffset, y + YOffset, text, col_h, font, align, line_size.x, line_size.y);
		else
			g_engine->_textManager->draw(x + XOffset, y + YOffset, text, col_b, font, align, line_size.x, line_size.y);
	}
}

void ReplyButton::Cache(const Common::String &val, const int &spacing, const int &bottom_edge, Rect *parent) {
	text = val;

	// Find out about the font
	int width = 0, height = 0;
#if 0
	TTF_SizeText(g_engine->_textManager->GetFont(font), val, &width, &height);
#endif
	width = g_engine->_textManager->GetFont(font)->getStringWidth(val);
	height = g_engine->_textManager->GetFont(font)->getFontHeight();

	// Find out how many line sizes will the text take
	int lines = ((text.size() - 1) / line_size.x) + 1;

	x = orig.x;
	y = orig.y;
	w = width;
	h = height * lines;
	setUI(parent);

	if (orig.y < bottom_edge)
		y = bottom_edge + spacing;
}

} // End of namespace Crab
