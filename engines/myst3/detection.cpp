/* Residual - A 3D game interpreter
 *
 * Residual is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the AUTHORS
 * file distributed with this source distribution.
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.

 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.

 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA
 *
 * $URL$
 * $Id$
 *
 */

#include "engines/advancedDetector.h"

#include "engines/myst3/myst3.h"

namespace Myst3 {

struct Myst3GameDescription {
	ADGameDescription desc;
	int flags;
};

static const PlainGameDescriptor myst3Games[] = {
	{"myst3", "Myst III Exile"},
	{0, 0}
};

using Common::GUIO_NONE;

static const Myst3GameDescription gameDescriptions[] = {
	{
		// Myst 3 French Version
		{
			"myst3",
			0,
			AD_ENTRY1s("RSRC.m3r", "a2c8ed69800f60bf5667e5c76a88e481", 1223862),
			Common::FR_FRA,
			Common::kPlatformPC,
			ADGF_NO_FLAGS,
			GUIO_NONE
		},
		0,
	},


	{ AD_TABLE_END_MARKER, 0 }
};

static const Myst3GameDescription fallbackGameDescriptions[] = {
	{{"myst3", 0, {{0, 0, 0, 0}}, Common::UNK_LANG, Common::kPlatformPC, ADGF_NO_FLAGS, GUIO_NONE}, 0}
};

static const ADFileBasedFallback myst3Fallback[] = {
	{&fallbackGameDescriptions[0], {"RSRC.m3r"}},
	{0, {0}}
};

static const ADParams detectionParams = {
	// Pointer to ADGameDescription or its superset structure
	(const byte *)gameDescriptions,
	// Size of that superset structure
	sizeof(Myst3GameDescription),
	// Number of bytes to compute MD5 sum for
	5000,
	// List of all engine targets
	myst3Games,
	// Structure for autoupgrading obsolete targets
	0,
	// Name of single gameid (optional)
	"myst3",
	// List of files for file-based fallback detection (optional)
	myst3Fallback,
	// Flags
	0,
	// Additional GUI options (for every game}
	Common::GUIO_NOMIDI
};

class Myst3MetaEngine : public AdvancedMetaEngine {
public:
	Myst3MetaEngine() : AdvancedMetaEngine(detectionParams) {}

	virtual const char *getName() const {
		return "Myst III Engine";
	}

	virtual const char *getOriginalCopyright() const {
		return "Myst III Game (C) Presto Studios";
	}

	virtual bool createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const;
};

bool Myst3MetaEngine::createInstance(OSystem *syst, Engine **engine, const ADGameDescription *desc) const {
	const Myst3GameDescription *gd = (const Myst3GameDescription *)desc;
	if (gd) {
		*engine = new Myst3Engine(syst, gd->flags);
	}
	return gd != 0;
}

} // End of namespace Myst3

#if PLUGIN_ENABLED_DYNAMIC(MYST3)
	REGISTER_PLUGIN_DYNAMIC(MYST3, PLUGIN_TYPE_ENGINE, Myst3::Myst3MetaEngine);
#else
	REGISTER_PLUGIN_STATIC(MYST3, PLUGIN_TYPE_ENGINE, Myst3::Myst3MetaEngine);
#endif
