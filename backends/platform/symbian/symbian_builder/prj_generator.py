# ScummVM - Graphic Adventure Engine
# Copyright (C) 2020 - 2021 Stryzhniou Fiodar

# ScummVM is the legal property of its developers, whose names
# are too numerous to list here. Please refer to the COPYRIGHT
# file distributed with this source distribution.

# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.

# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.

# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.


from __future__ import with_statement
import os, stat
from common_names import *


# ---------------------------
# Expect: reg_rss_template %(UID3, ordnum, ordnum)
reg_rss_template = """
/*
 * Warning: autogenerated file
 */
// All registration files need to #include appinfo.rh.
#include <AppInfo.rh>

// All registration files must define UID2, which is always
// KUidAppRegistrationResourceFile, and UID3, which is the application's UID.
UID2 KUidAppRegistrationResourceFile
UID3 %s // application UID

// Registration file need to containo an APP_REGISTRATION_INFO resource that
// minimally needs to provide the name of the application binary (using the
// app_file statement).
RESOURCE APP_REGISTRATION_INFO
	{
	app_file = "ScummVM%s"; // filename of application binary (minus extension)
	// Specify the location of the localisable icon/caption definition file
	localisable_resource_file = "\\Resource\\Apps\\ScummVM%s_loc";
	}
"""

# ---------------------------
# Expect:  loc_rss_template %UID3
loc_rss_template = """
/*
 * Warning: autogenerated file
 */
#include <AppInfo.rh>

// This file localise the applications icons and caption
RESOURCE LOCALISABLE_APP_INFO
	{
	caption_and_icon =
		{
		CAPTION_AND_ICON_INFO
			{
			// The caption text is defined in the rls file
			caption = "ScummVM %s";
			// Icons are used to represent applications in the
			// application launcher and application title bar.
			// The number_of_icons value identifies how many icons
			// that exist in the icon_file.
			number_of_icons = 1;
			// Using the application icons.
			icon_file = "\\Resource\\Apps\\ScummVM.mif";
			}
		};
	}
"""

# ---------------------------
# Expect: rss_template %(UID3, UID3)
rss_template = """
/*
 * Warning: autogenerated file
 */

// ScummVM%s.rss

NAME SCUM

// Include definitions of resource STRUCTS used by this
// resource script
#include <eikon.rh>


RESOURCE RSS_SIGNATURE
	{
	}

RESOURCE TBUF16 { buf=""; }

RESOURCE EIK_APP_INFO
	{
		menubar = r_scum_menubar;
	}

RESOURCE MENU_BAR r_scum_menubar                                         // *** Menu bar
{
      titles =
    {
		MENU_TITLE { menu_pane = r_scum_menu; txt = "ScummVM%s"; }
	};
}

RESOURCE MENU_PANE r_scum_menu                                  // *** Submenu
{
	items =
	{

		MENU_ITEM{command = EEikCmdExit;txt = "Exit";}
    };
}

"""

# ---------------------------
# Expect: mmp_template %(ordnum, UID3, ordnum, ordnum, ordnum, ordnum, ordnum)
mmp_template = """
/*
 * Warning: autogenerated file
 */

//
// EPOC S60 MMP makefile project for ScummVM
//

// *** Definitions


TARGET          ScummVM%s.exe
TARGETPATH      sys\\bin
TARGETTYPE      exe
OPTION			GCCE -Wno-multichar -Wno-reorder -Wno-unused -Wno-format -fsigned-char \
 -fno-asynchronous-unwind-tables -std=c++11 // -ffreestanding -fno-sized-deallocation //--verbose //-flto -fuse-linker-plugin //-Wl, -v  -fbuiltin
// fixes error "section .data loaded at [...] overlaps section .text loaded at [...]"
LINKEROPTION 	GCCE -Tdata 0xAA00000 // -v -flto -fuse-linker-plugin
//--print-gc-sections --stats --gc-sections --strip-all// removes unused code

UID             0x100039ce %s

bytepaircompresstarget

START RESOURCE  ScummVM%s.rss
HEADER
TARGETPATH              \Resource\Apps
LANG                    SC
END

START RESOURCE  ScummVM%s_reg.rss
TARGETPATH              \private\\10003a3f\\apps
END

START RESOURCE  ScummVM%s_loc.rss
TARGETPATH              \Resource\Apps
LANG                    SC
END

EPOCSTACKSIZE	80000
EPOCHEAPSIZE	5000000 64000000

MACRO   SCUMMVM_PT_%s

#define SCUMMVM_PT_%s
#include "macros.mmh"
#include "build_config.mmh"
#include "build_app_config.mmh" // must be above engines.mmh
#include "engines.mmh"
"""
# ---------------------------
bld_inf_template = """
PRJ_PLATFORMS
GCCE WINSCW

PRJ_MMPFILES

gnumakefile icons.mk
gnumakefile ..\\help\\build_help.mk

"""
# ---------------------------


def data_dump(macros):
   with open(macros) as ff:
      f = ff.readlines()
   n = []
   for x in f:
      if x.startswith("// MACRO"):
         x = x.strip("// ")
      if x.startswith(('STATICLIBRARY', 'MACRO')):
         n.append(x.strip())
   n.sort()
   return n


def data_diff(data_cached, data):
   data_cached = data_dump(data_cached)
   data = data_dump(data)
   return set(data_cached).symmetric_difference(set(data))


def check_cashed(path):
   macros_cached = os.path.join(path, "macros.mmh")
   if os.path.exists(macros_cached):
      macros = os.path.join(mmps, "macros.mmh")
      engines_cached = os.path.join(path, "engines.mmh")
      engines = os.path.join(mmps, "engines.mmh")

      try:
         macros_diff = data_diff(macros_cached, macros)
         engines_diff = data_diff(engines_cached, engines)
      except IOError:
         return

      if macros_diff:
         os.chmod(macros_cached, stat.S_IWRITE)
         print "new macro(s) found: %s" %macros_diff
         AppendToFile(macros_cached, list(macros_diff))
         AppendToFile(build_log, "new macro found: ")
         AppendToFile(build_log, list(macros_diff))

      if engines_diff:
         os.chmod(engines_cached, stat.S_IWRITE)
         print "new engine(s) found: %s" %engines_diff
         AppendToFile(engines_cached, list(engines_diff))
         AppendToFile(build_log, "new macro found: ")
         AppendToFile(build_log, list(engines_diff))

      os.chmod(macros_cached, stat.S_IREAD)
      os.chmod(engines_cached, stat.S_IREAD)
      AppendToFile(build_log, '\n')


def create_mmps(build, path):
   uids = get_UIDs(build)
   bld_inf = os.path.join(path, "bld.inf")
   SafeWriteFile(bld_inf, bld_inf_template)
   for i in range(len(uids)):
      UID3 = uids[i]
      idx = i + 1
      idx2 = i + 1
      if build == 'full':
         idx = "%s_test" %idx
      rss_name = "ScummVM%s.rss" %idx
      data = rss_template %(idx, idx)
      SafeWriteFile(os.path.join(path, rss_name), data)
      data = loc_rss_template %idx
      rss_loc_name = "ScummVM%s_loc.rss" %idx
      SafeWriteFile(os.path.join(path, rss_loc_name), data)
      data = reg_rss_template %(UID3, idx, idx)
      rss_reg_name = "ScummVM%s_reg.rss" %idx
      SafeWriteFile(os.path.join(path, rss_reg_name), data)
      data = mmp_template %(idx, UID3, idx, idx, idx, idx2, idx2)
      mmp_name = "ScummVM%s.mmp" %idx2
      SafeWriteFile(os.path.join(path, mmp_name), data)
      AppendToFile(bld_inf, mmp_name + "\n")
   check_cashed(path)

if __name__ == "__main__":
   create_mmps(build = 'release', path = "S60v3")
