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

#ifndef AGS_ENGINE_AC_PARSER_H
#define AGS_ENGINE_AC_PARSER_H

namespace AGS3 {

int Parser_FindWordID(const char *wordToFind);
const char *Parser_SaidUnknownWord();
void ParseText(const char *text);
int Said(const char *checkwords);

//=============================================================================

int find_word_in_dictionary(const char *lookfor);
int is_valid_word_char(char theChar);
int FindMatchingMultiWordWord(char *thisword, const char **text);
int parse_sentence(const char *src_text, int *numwords, short *wordarray, short *compareto, int comparetonum);

} // namespace AGS3

#endif
