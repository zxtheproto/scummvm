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

#include "glk/tads/tads2/post_compilation.h"
#include "glk/tads/tads2/error.h"
#include "glk/tads/tads2/os.h"

namespace Glk {
namespace TADS {
namespace TADS2 {

void supcont(void *ctx, objnum obj, prpnum prp) {
		// No implementation
}

void supivoc(supcxdef *ctx) {
	// No implementation
}

void supfind(errcxdef *ctx, tokthdef *tab, voccxdef *voc,
		objnum *preinit, int warnlevel, int casefold) {
	// No implementation
}

void suprsrv(supcxdef *sup, void(*bif[])(struct bifcxdef *, int),
		toktdef *tab, int fncntmax, int v1compat, char *new_do, int casefold) {
	// No implementation
}

void supbif(supcxdef *sup, void(*bif[])(struct bifcxdef *, int), int bifsiz) {
	// No implementation
}

void sup_log_undefobj(mcmcxdef *mctx, errcxdef *ec, int err,
		char *sym_name, int sym_name_len, objnum objn) {
	// No implementation
}

void supivoc1(supcxdef *sup, voccxdef *ctx, vocidef *v, objnum target,
		int inh_from_obj, int flags) {
	// No implementation
}

} // End of namespace TADS2
} // End of namespace TADS
} // End of namespace Glk
