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

#include "ags/shared/font/ttf_font_renderer.h"
#include "ags/lib/alfont/alfont.h"
#include "ags/shared/core/platform.h"
#include "ags/shared/ac/game_version.h"
#include "ags/globals.h"
#include "ags/shared/core/asset_manager.h"
#include "ags/shared/util/stream.h"
#include "ags/shared/ac/game_struct_defines.h"
#include "ags/shared/font/fonts.h"

namespace AGS3 {

using namespace AGS::Shared;

// project-specific implementation
extern bool ShouldAntiAliasText();


// ***** TTF RENDERER *****
void TTFFontRenderer::AdjustYCoordinateForFont(int *ycoord, int fontNumber) {
	// TTF fonts already have space at the top, so try to remove the gap
	// TODO: adding -1 was here before (check the comment above),
	// but how universal is this "space at the top"?
	// Also, why is this function used only in one case of text rendering?
	// Review this after we upgrade the font library.
	ycoord[0]--;
}

void TTFFontRenderer::EnsureTextValidForFont(char *text, int fontNumber) {
	// do nothing, TTF can handle all characters
}

int TTFFontRenderer::GetTextWidth(const char *text, int fontNumber) {
	return alfont_text_length(_fontData[fontNumber].AlFont, text);
}

int TTFFontRenderer::GetTextHeight(const char *text, int fontNumber) {
	return alfont_get_font_real_height(_fontData[fontNumber].AlFont);
}

void TTFFontRenderer::RenderText(const char *text, int fontNumber, BITMAP *destination, int x, int y, int colour) {
	if (y > destination->cb)  // optimisation
		return;

	// Y - 1 because it seems to get drawn down a bit
	if ((ShouldAntiAliasText()) && (bitmap_color_depth(destination) > 8))
		alfont_textout_aa(destination, _fontData[fontNumber].AlFont, text, x, y - 1, colour);
	else
		alfont_textout(destination, _fontData[fontNumber].AlFont, text, x, y - 1, colour);
}

bool TTFFontRenderer::LoadFromDisk(int fontNumber, int fontSize) {
	return LoadFromDiskEx(fontNumber, fontSize, nullptr, nullptr);
}

bool TTFFontRenderer::IsBitmapFont() {
	return false;
}

static int GetAlfontFlags(int load_mode) {
	int flags = ALFONT_FLG_FORCE_RESIZE | ALFONT_FLG_SELECT_NOMINAL_SZ;
	// Compatibility: font ascender is always adjusted to the formal font's height;
	// EXCEPTION: not if it's a game made before AGS 3.4.1 with TTF anti-aliasing
	// (the reason is uncertain, but this is to emulate old engine's behavior).
	if (((load_mode & FFLG_ASCENDERFIXUP) != 0) &&
		!(ShouldAntiAliasText() && (_G(loaded_game_file_version) < kGameVersion_341)))
		flags |= ALFONT_FLG_ASCENDER_EQ_HEIGHT;
	return flags;
}

bool TTFFontRenderer::LoadFromDiskEx(int fontNumber, int fontSize,
	const FontRenderParams *params, FontMetrics *metrics) {
	String file_name = String::FromFormat("agsfnt%d.ttf", fontNumber);
	Stream *reader = _GP(AssetMgr)->OpenAsset(file_name);
	char *membuffer;

	if (reader == nullptr)
		return false;

	const size_t lenof = reader->GetLength();
	membuffer = (char *)malloc(lenof);
	reader->ReadArray(membuffer, lenof, 1);
	delete reader;

	ALFONT_FONT *alfptr = alfont_load_font_from_mem(membuffer, lenof);
	free(membuffer);

	if (alfptr == nullptr)
		return false;

	if (fontSize <= 0)
		fontSize = 8; // compatibility fix
	if (params && params->SizeMultiplier > 1)
		fontSize *= params->SizeMultiplier;

	alfont_set_font_size_ex(alfptr, fontSize, GetAlfontFlags(params->LoadMode));

	_fontData[fontNumber].AlFont = alfptr;
	_fontData[fontNumber].Params = params ? *params : FontRenderParams();

	if (metrics) {
		metrics->Height = alfont_get_font_height(alfptr);
		metrics->RealHeight = alfont_get_font_real_height(alfptr);
	}
	return true;
}

const char *TTFFontRenderer::GetName(int fontNumber) {
	return alfont_get_name(_fontData[fontNumber].AlFont);
}

void TTFFontRenderer::AdjustFontForAntiAlias(int fontNumber, bool aa_mode) {
	if (_G(loaded_game_file_version) < kGameVersion_341) {
		ALFONT_FONT *alfptr = _fontData[fontNumber].AlFont;
		const FontRenderParams &params = _fontData[fontNumber].Params;
		int old_height = alfont_get_font_height(alfptr);
		alfont_set_font_size_ex(alfptr, old_height, GetAlfontFlags(params.LoadMode));
	}
}

void TTFFontRenderer::FreeMemory(int fontNumber) {
	alfont_destroy_font(_fontData[fontNumber].AlFont);
	_fontData.erase(fontNumber);
}

} // namespace AGS3
