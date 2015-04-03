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
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "common/debug.h"
#include "common/system.h"

#include "audio/fmopl.h"
#include "audio/mpu401.h"
#include "audio/softsynth/emumidi.h"

namespace Parallaction {

const uint kNumVoices = 9;
// adlib FM voices 0-5
const uint kNumMelodic = 6;
// adlib FM voice 6 and 7-8
const uint kNumPercussion = 5;

// mask for maximum volume level
#define LEVEL_MASK 0x7f

struct OPLOperator {
	uint8 characteristic; // amplitude modulation, vibrato, envelope, keyboard scaling, modulator frequency
	uint8 levels;
	uint8 attackDecay;
	uint8 sustainRelease;
	uint8 waveform;
};

struct MelodicProgram {
	OPLOperator op[2];
	uint8 feedbackAlgo;
};

struct PercussionNote {
	OPLOperator op[2];
	uint8 feedbackAlgo;
	uint8 percussion;
	uint8 valid;
	uint16 frequency;
	uint8 octave;
};

static const MelodicProgram melodicPrograms[128] = {
	{{{   0x1, 0x51, 0xf2, 0xb2,  0x0 }, { 0x11,  0x0, 0xf2, 0xa2,  0x0 }},  0x0 },
	{{{  0xc2, 0x4b, 0xf1, 0x53,  0x0 }, { 0xd2,  0x0, 0xf2, 0x74,  0x0 }},  0x4 },
	{{{  0x81, 0x9d, 0xf2, 0x74,  0x0 }, { 0x13,  0x0, 0xf2, 0xf1,  0x0 }},  0x6 },
	{{{   0x3, 0x4f, 0xf1, 0x53,  0x0 }, { 0x17,  0x3, 0xf2, 0x74,  0x0 }},  0x6 },
	{{{  0xd1, 0x81, 0x81, 0x73,  0x2 }, { 0xd4,  0x0, 0xe1, 0x34,  0x0 }},  0x3 },
	{{{   0x1,  0x0, 0x94, 0xa6,  0x0 }, {  0x2,  0x0, 0x83, 0x26,  0x0 }},  0x1 },
	{{{  0xf3, 0x84, 0x81,  0x2,  0x1 }, { 0x55, 0x80, 0xdd,  0x3,  0x0 }},  0x4 },
	{{{   0x5, 0x8a, 0xf2, 0x26,  0x0 }, {  0x1, 0x80, 0xf3, 0x48,  0x0 }},  0x0 },
	{{{  0x32,  0x0, 0xb1, 0x14,  0x0 }, { 0x12,  0x0, 0xfd, 0x36,  0x0 }},  0x3 },
	{{{   0x1,  0x0, 0x82,  0xa,  0x2 }, {  0x2,  0x0, 0x85, 0x15,  0x0 }},  0x3 },
	{{{  0xd1,  0x1, 0x97, 0xaa,  0x0 }, {  0x4,  0xd, 0xf3, 0xa5,  0x1 }},  0x9 },
	{{{  0x17,  0x0, 0xf2, 0x62,  0x0 }, { 0x12,  0x0, 0xf2, 0x72,  0x0 }},  0x8 },
	{{{   0x6,  0x0, 0xff, 0xf4,  0x0 }, { 0xc4,  0x0, 0xf8, 0xb5,  0x0 }},  0xe },
	{{{  0xc0, 0x81, 0xf2, 0x13,  0x2 }, { 0xc0, 0xc1, 0xf3, 0x14,  0x2 }},  0xb },
	{{{  0x44, 0x53, 0xf5, 0x31,  0x0 }, { 0x60, 0x80, 0xfd, 0x22,  0x0 }},  0x6 },
	{{{  0xe0, 0x80, 0xf4, 0xf2,  0x0 }, { 0x61,  0x0, 0xf2,  0x6,  0x0 }},  0x8 },
	{{{  0xc1,  0x6, 0x83, 0x23,  0x0 }, { 0xc1,  0x4, 0xf0, 0x26,  0x0 }},  0x1 },
	{{{  0x26,  0x0, 0xf4, 0xb6,  0x0 }, { 0x21,  0x0, 0x81, 0x4b,  0x0 }},  0x1 },
	{{{  0x24, 0x80, 0xff,  0xf,  0x0 }, { 0x21, 0x80, 0xff,  0xf,  0x0 }},  0x1 },
	{{{  0x24, 0x4f, 0xf2,  0xb,  0x0 }, { 0x31,  0x0, 0x52,  0xb,  0x0 }},  0xb },
	{{{  0x31,  0x8, 0x81,  0xb,  0x0 }, { 0xa1, 0x80, 0x92, 0x3b,  0x0 }},  0x0 },
	{{{  0x70, 0xc5, 0x52, 0x11,  0x1 }, { 0x71, 0x80, 0x31, 0xfe,  0x1 }},  0x0 },
	{{{  0x51, 0x88, 0x10, 0xf0,  0x0 }, { 0x42, 0x83, 0x40, 0xfc,  0x0 }},  0x8 },
	{{{  0xf0, 0xd9, 0x81,  0x3,  0x0 }, { 0xb1, 0x80, 0xf1,  0x5,  0x0 }},  0xa },
	{{{  0x21, 0x4f, 0xf1, 0x31,  0x0 }, {  0x2, 0x80, 0xc3, 0x45,  0x0 }},  0x0 },
	{{{   0x7, 0x8f, 0x9c, 0x33,  0x1 }, {  0x1, 0x80, 0x8a, 0x13,  0x0 }},  0x0 },
	{{{  0x21, 0x40, 0xf1, 0x31,  0x0 }, {  0x6, 0x80, 0xf4, 0x44,  0x0 }},  0x0 },
	{{{  0x21, 0x40, 0xf1, 0x31,  0x3 }, { 0x81,  0x0, 0xf4, 0x44,  0x2 }},  0x2 },
	{{{  0x11, 0x8d, 0xfd, 0x11,  0x0 }, { 0x11, 0x80, 0xfd, 0x11,  0x0 }},  0x8 },
	{{{  0xf0,  0x1, 0x97, 0x17,  0x0 }, { 0x21,  0xd, 0xf1, 0x18,  0x0 }},  0x8 },
	{{{  0xf1,  0x1, 0x97, 0x17,  0x0 }, { 0x21,  0xd, 0xf1, 0x18,  0x0 }},  0x8 },
	{{{  0xcd, 0x9e, 0x55, 0xd1,  0x0 }, { 0xd1,  0x0, 0xf2, 0x71,  0x0 }},  0xe },
	{{{   0x1,  0x0, 0xf2, 0x88,  0x0 }, {  0x1,  0x0, 0xf5, 0x88,  0x0 }},  0x1 },
	{{{  0x30,  0xd, 0xf2, 0xef,  0x0 }, { 0x21,  0x0, 0xf5, 0x78,  0x0 }},  0x6 },
	{{{   0x0, 0x10, 0xf4, 0xd9,  0x0 }, {  0x0,  0x0, 0xf5, 0xd7,  0x0 }},  0x4 },
	{{{   0x1, 0x4c, 0xf2, 0x50,  0x0 }, {  0x1, 0x40, 0xd2, 0x59,  0x0 }},  0x8 },
	{{{  0x20, 0x11, 0xe2, 0x8a,  0x0 }, { 0x20,  0x0, 0xe4, 0xa8,  0x0 }},  0xa },
	{{{  0x21, 0x40, 0x7b,  0x4,  0x1 }, { 0x21,  0x0, 0x75, 0x72,  0x0 }},  0x2 },
	{{{  0x31,  0xd, 0xf2, 0xef,  0x0 }, { 0x21,  0x0, 0xf5, 0x78,  0x0 }},  0xa },
	{{{   0x1,  0xc, 0xf5, 0x2f,  0x1 }, {  0x0, 0x80, 0xf5, 0x5c,  0x0 }},  0x0 },
	{{{  0xb0, 0x1c, 0x81,  0x3,  0x2 }, { 0x20,  0x0, 0x54, 0x67,  0x2 }},  0xe },
	{{{   0x1,  0x0, 0xf1, 0x65,  0x0 }, {  0x1, 0x80, 0xa3, 0xa8,  0x2 }},  0x1 },
	{{{  0xe1, 0x4f, 0xc1, 0xd3,  0x2 }, { 0x21,  0x0, 0x32, 0x74,  0x1 }},  0x0 },
	{{{   0x2,  0x0, 0xf6, 0x16,  0x0 }, { 0x12,  0x0, 0xf2, 0xf8,  0x0 }},  0x1 },
	{{{  0xe0, 0x63, 0xf8, 0xf3,  0x0 }, { 0x70, 0x80, 0xf7, 0xf3,  0x0 }},  0x4 },
	{{{   0x1,  0x6, 0xf3, 0xff,  0x0 }, {  0x8,  0x0, 0xf7, 0xff,  0x0 }},  0x4 },
	{{{  0x21, 0x16, 0xb0, 0x81,  0x1 }, { 0x22,  0x0, 0xb3, 0x13,  0x1 }},  0xc },
	{{{   0x1, 0x4f, 0xf0, 0xff,  0x0 }, { 0x30,  0x0, 0x90,  0xf,  0x0 }},  0x6 },
	{{{   0x0, 0x10, 0xf1, 0xf2,  0x2 }, {  0x1,  0x0, 0xf1, 0xf2,  0x3 }},  0x0 },
	{{{   0x1, 0x4f, 0xf1, 0x50,  0x0 }, { 0x21, 0x80, 0xa3,  0x5,  0x3 }},  0x6 },
	{{{  0xb1,  0x3, 0x55,  0x3,  0x0 }, { 0xb1,  0x3,  0x8,  0xa,  0x0 }},  0x9 },
	{{{  0x22,  0x0, 0xa9, 0x34,  0x1 }, {  0x1,  0x0, 0xa2, 0x42,  0x2 }},  0x2 },
	{{{  0xa0, 0xdc, 0x81, 0x31,  0x3 }, { 0xb1, 0x80, 0xf1,  0x1,  0x3 }},  0x0 },
	{{{   0x1, 0x4f, 0xf1, 0x50,  0x0 }, { 0x21, 0x80, 0xa3,  0x5,  0x3 }},  0x6 },
	{{{  0xf1, 0x80, 0xa0, 0x72,  0x0 }, { 0x74,  0x0, 0x90, 0x22,  0x0 }},  0x9 },
	{{{  0xe1, 0x13, 0x71, 0xae,  0x0 }, { 0xe1,  0x0, 0xf0, 0xfc,  0x1 }},  0xa },
	{{{  0x31, 0x1c, 0x41,  0xb,  0x0 }, { 0xa1, 0x80, 0x92, 0x3b,  0x0 }},  0xe },
	{{{  0x71, 0x1c, 0x41, 0x1f,  0x0 }, { 0xa1, 0x80, 0x92, 0x3b,  0x0 }},  0xe },
	{{{  0x21, 0x1c, 0x53, 0x1d,  0x0 }, { 0xa1, 0x80, 0x52, 0x3b,  0x0 }},  0xc },
	{{{  0x21, 0x1d, 0xa4, 0xae,  0x1 }, { 0x21,  0x0, 0xb1, 0x9e,  0x0 }},  0xc },
	{{{  0xe1, 0x16, 0x71, 0xae,  0x0 }, { 0xe1,  0x0, 0x81, 0x9e,  0x0 }},  0xa },
	{{{  0xe1, 0x15, 0x71, 0xae,  0x0 }, { 0xe2,  0x0, 0x81, 0x9e,  0x0 }},  0xe },
	{{{  0x21, 0x16, 0x71, 0xae,  0x0 }, { 0x21,  0x0, 0x81, 0x9e,  0x0 }},  0xe },
	{{{  0x71, 0x1c, 0x41, 0x1f,  0x0 }, { 0xa1, 0x80, 0x92, 0x3b,  0x0 }},  0xe },
	{{{  0x21, 0x4f, 0x81, 0x53,  0x0 }, { 0x32,  0x0, 0x22, 0x2c,  0x0 }},  0xa },
	{{{  0x22, 0x4f, 0x81, 0x53,  0x0 }, { 0x32,  0x0, 0x22, 0x2c,  0x0 }},  0xa },
	{{{  0x23, 0x4f, 0x81, 0x53,  0x0 }, { 0x34,  0x0, 0x22, 0x2c,  0x0 }},  0xa },
	{{{  0xe1, 0x16, 0x71, 0xae,  0x0 }, { 0xe1,  0x0, 0x81, 0x9e,  0x0 }},  0xa },
	{{{  0x71, 0xc5, 0x6e, 0x17,  0x0 }, { 0x22,  0x5, 0x8b,  0xe,  0x0 }},  0x2 },
	{{{  0xe6, 0x27, 0x70,  0xf,  0x1 }, { 0xe3,  0x0, 0x60, 0x9f,  0x0 }},  0xa },
	{{{  0x30, 0xc8, 0xd5, 0x19,  0x0 }, { 0xb1, 0x80, 0x61, 0x1b,  0x0 }},  0xc },
	{{{  0x32, 0x9a, 0x51, 0x1b,  0x0 }, { 0xa1, 0x82, 0xa2, 0x3b,  0x0 }},  0xc },
	{{{  0xad,  0x3, 0x74, 0x29,  0x0 }, { 0xa2, 0x82, 0x73, 0x29,  0x0 }},  0x7 },
	{{{  0x21, 0x83, 0x74, 0x17,  0x0 }, { 0x62, 0x8d, 0x65, 0x17,  0x0 }},  0x7 },
	{{{  0x94,  0xb, 0x85, 0xff,  0x1 }, { 0x13,  0x0, 0x74, 0xff,  0x0 }},  0xc },
	{{{  0x74, 0x87, 0xa4,  0x2,  0x0 }, { 0xd6, 0x80, 0x45, 0x42,  0x0 }},  0x2 },
	{{{  0xb3, 0x85, 0x76, 0x21,  0x1 }, { 0x20,  0x0, 0x3d, 0xc1,  0x0 }},  0x6 },
	{{{  0x17, 0x4f, 0xf2, 0x61,  0x0 }, { 0x12,  0x8, 0xf1, 0xb4,  0x0 }},  0x8 },
	{{{  0x4f, 0x86, 0x65,  0x1,  0x0 }, { 0x1f,  0x0, 0x32, 0x74,  0x0 }},  0x4 },
	{{{  0xe1, 0x23, 0x71, 0xae,  0x0 }, { 0xe4,  0x0, 0x82, 0x9e,  0x0 }},  0xa },
	{{{  0x11, 0x86, 0xf2, 0xbd,  0x0 }, {  0x4, 0x80, 0xa0, 0x9b,  0x1 }},  0x8 },
	{{{  0x20, 0x90, 0xf5, 0x9e,  0x2 }, { 0x11,  0x0, 0xf4, 0x5b,  0x3 }},  0xc },
	{{{  0xf0, 0x80, 0x34, 0xe4,  0x0 }, { 0x7e,  0x0, 0xa2,  0x6,  0x0 }},  0x8 },
	{{{  0x90,  0xf, 0xff,  0x1,  0x3 }, {  0x0,  0x0, 0x1f,  0x1,  0x0 }},  0xe },
	{{{   0x1, 0x4f, 0xf0, 0xff,  0x0 }, { 0x33,  0x0, 0x90,  0xf,  0x0 }},  0x6 },
	{{{  0x1e,  0x0, 0x1f,  0xf,  0x0 }, { 0x10,  0x0, 0x1f, 0x7f,  0x0 }},  0x0 },
	{{{  0xbe,  0x0, 0xf1,  0x1,  0x3 }, { 0x31,  0x0, 0xf1,  0x1,  0x0 }},  0x4 },
	{{{  0xbe,  0x0, 0xf1,  0x1,  0x3 }, { 0x31,  0x0, 0xf1,  0x1,  0x0 }},  0x4 },
	{{{  0x93,  0x6, 0xc1,  0x4,  0x1 }, { 0x82,  0x0, 0x51,  0x9,  0x0 }},  0x6 },
	{{{  0xa0,  0x0, 0x96, 0x33,  0x0 }, { 0x20,  0x0, 0x55, 0x2b,  0x0 }},  0x6 },
	{{{   0x0, 0xc0, 0xff,  0x5,  0x0 }, {  0x0,  0x0, 0xff,  0x5,  0x3 }},  0x0 },
	{{{   0x4,  0x8, 0xf8,  0x7,  0x0 }, {  0x1,  0x0, 0x82, 0x74,  0x0 }},  0x8 },
	{{{   0x0,  0x0, 0x2f,  0x5,  0x0 }, { 0x20,  0x0, 0xff,  0x5,  0x3 }},  0xa },
	{{{  0x93,  0x0, 0xf7,  0x7,  0x2 }, {  0x0,  0x0, 0xf7,  0x7,  0x0 }},  0xa },
	{{{   0x0, 0x40, 0x80, 0x7a,  0x0 }, { 0xc4,  0x0, 0xc0, 0x7e,  0x0 }},  0x8 },
	{{{  0x90, 0x80, 0x55, 0xf5,  0x0 }, {  0x0,  0x0, 0x55, 0xf5,  0x0 }},  0x8 },
	{{{  0xe1, 0x80, 0x34, 0xe4,  0x0 }, { 0x69,  0x0, 0xf2,  0x6,  0x0 }},  0x8 },
	{{{   0x3,  0x2, 0xf0, 0xff,  0x3 }, { 0x11, 0x80, 0xf0, 0xff,  0x2 }},  0x2 },
	{{{  0x1e,  0x0, 0x1f,  0xf,  0x0 }, { 0x10,  0x0, 0x1f, 0x7f,  0x0 }},  0x0 },
	{{{   0x0,  0x0, 0x2f,  0x1,  0x0 }, {  0x0,  0x0, 0xff,  0x1,  0x0 }},  0x4 },
	{{{  0xbe,  0x0, 0xf1,  0x1,  0x3 }, { 0x31,  0x0, 0xf1,  0x1,  0x0 }},  0x4 },
	{{{  0x93, 0x85, 0x3f,  0x6,  0x1 }, {  0x0,  0x0, 0x5f,  0x7,  0x0 }},  0x6 },
	{{{   0x6,  0x0, 0xa0, 0xf0,  0x0 }, { 0x44,  0x0, 0xc5, 0x75,  0x0 }},  0xe },
	{{{  0x60,  0x0, 0x10, 0x81,  0x0 }, { 0x20, 0x8c, 0x12, 0x91,  0x0 }},  0xe },
	{{{   0x1, 0x40, 0xf1, 0x53,  0x0 }, {  0x8, 0x40, 0xf1, 0x53,  0x0 }},  0x0 },
	{{{  0x31,  0x0, 0x56, 0x31,  0x0 }, { 0x16,  0x0, 0x7d, 0x41,  0x0 }},  0x0 },
	{{{   0x0, 0x10, 0xf2, 0x72,  0x0 }, { 0x13,  0x0, 0xf2, 0x72,  0x0 }},  0xc },
	{{{  0x10,  0x0, 0x75, 0x93,  0x1 }, {  0x1,  0x0, 0xf5, 0x82,  0x1 }},  0x0 },
	{{{   0x0,  0x0, 0xf6, 0xff,  0x2 }, {  0x0,  0x0, 0xf6, 0xff,  0x0 }},  0x8 },
	{{{  0x30,  0x0, 0xff, 0xa0,  0x3 }, { 0x63,  0x0, 0x65,  0xb,  0x2 }},  0x0 },
	{{{  0x2a,  0x0, 0xf6, 0x87,  0x0 }, { 0x2b,  0x0, 0x76, 0x25,  0x0 }},  0x0 },
	{{{  0x85,  0x0, 0xb8, 0x84,  0x0 }, { 0x43,  0x0, 0xe5, 0x8f,  0x0 }},  0x6 },
	{{{   0x7, 0x4f, 0xf2, 0x60,  0x0 }, { 0x12,  0x0, 0xf2, 0x72,  0x0 }},  0x8 },
	{{{   0x5, 0x40, 0xb3, 0xd3,  0x0 }, { 0x86, 0x80, 0xf2, 0x24,  0x0 }},  0x2 },
	{{{  0xd0,  0x0, 0x11, 0xcf,  0x0 }, { 0xd1,  0x0, 0xf4, 0xe8,  0x3 }},  0x0 },
	{{{   0x5, 0x4e, 0xda, 0x25,  0x2 }, {  0x1,  0x0, 0xf9, 0x15,  0x0 }},  0xa },
	{{{   0x3,  0x0, 0x8f,  0x7,  0x2 }, {  0x2,  0x0, 0xff,  0x6,  0x0 }},  0x0 },
	{{{  0x13,  0x0, 0x8f,  0x7,  0x2 }, {  0x2,  0x0, 0xf9,  0x5,  0x0 }},  0x0 },
	{{{  0xf0,  0x1, 0x97, 0x17,  0x0 }, { 0x21,  0xd, 0xf1, 0x18,  0x0 }},  0x8 },
	{{{  0xf1, 0x41, 0x11, 0x11,  0x0 }, { 0xf1, 0x41, 0x11, 0x11,  0x0 }},  0x2 },
	{{{  0x13,  0x0, 0x8f,  0x7,  0x2 }, {  0x2,  0x0, 0xff,  0x6,  0x0 }},  0x0 },
	{{{   0x1,  0x0, 0x2f,  0x1,  0x0 }, {  0x1,  0x0, 0xaf,  0x1,  0x3 }},  0xf },
	{{{   0x1,  0x6, 0xf3, 0xff,  0x0 }, {  0x8,  0x0, 0xf7, 0xff,  0x0 }},  0x4 },
	{{{  0xc0, 0x4f, 0xf1,  0x3,  0x0 }, { 0xbe,  0xc, 0x10,  0x1,  0x0 }},  0x2 },
	{{{   0x0,  0x2, 0xf0, 0xff,  0x0 }, { 0x11, 0x80, 0xf0, 0xff,  0x0 }},  0x6 },
	{{{  0x81, 0x47, 0xf1, 0x83,  0x0 }, { 0xa2,  0x4, 0x91, 0x86,  0x0 }},  0x6 },
	{{{  0xf0, 0xc0, 0xff, 0xff,  0x3 }, { 0xe5,  0x0, 0xfb, 0xf0,  0x0 }},  0xe },
	{{{   0x0,  0x2, 0xf0, 0xff,  0x0 }, { 0x11, 0x80, 0xf0, 0xff,  0x0 }},  0x6 }
};

static const PercussionNote percussionNotes[47] = {
	{{{  0x0,  0xb, 0xa8, 0x38,  0x0 }, {  0x0,  0x0, 0xd6, 0x49,  0x0 }},  0x0,  0x4,  0x1,   0x97,  0x4 },
	{{{ 0xc0, 0xc0, 0xf8, 0x3f,  0x2 }, { 0xc0,  0x0, 0xf6, 0x8e,  0x0 }},  0x0,  0x4,  0x1,   0xf7,  0x4 },
	{{{ 0xc0, 0x80, 0xc9, 0xab,  0x0 }, { 0xeb, 0x40, 0xb5, 0xf6,  0x0 }},  0x1,  0x3,  0x1,   0x6a,  0x6 },
	{{{  0xc,  0x0, 0xd8, 0xa6,  0x0 }, {  0x0,  0x0, 0xd6, 0x4f,  0x0 }},  0x1,  0x3,  0x1,   0x6c,  0x5 },
	{{{  0x1,  0x0, 0xe2, 0xd2,  0x0 }, {  0x3, 0x41, 0x8f, 0x48, 0x49 }},  0xc,  0x4,  0x1,   0x2f,  0x5 },
	{{{  0x0,  0x0, 0xc8, 0x58,  0x3 }, {  0x0,  0x0, 0xf6, 0x4f,  0x0 }},  0x9,  0x3,  0x1,  0x108,  0x4 },
	{{{  0x1,  0x0, 0xff,  0x5,  0x0 }, { 0xf2, 0xff, 0xe0, 0x50, 0x52 }}, 0x5d,  0x2,  0x1,   0x9f,  0x5 },
	{{{  0xe,  0x9, 0xb9, 0x47,  0x0 }, { 0xeb, 0x40, 0xf5, 0xe6,  0x0 }},  0x0,  0x0,  0x1,   0x82,  0x6 },
	{{{  0x0,  0x0, 0xd6, 0x83,  0x0 }, { 0xd6, 0xd7, 0xe0, 0x41, 0x5e }}, 0x4a,  0x2,  0x1,   0xc7,  0x5 },
	{{{  0x1,  0x9, 0x89, 0x67,  0x0 }, { 0xd6, 0xd7, 0xe0, 0x41, 0x5e }}, 0x4a,  0x0,  0x1,   0x80,  0x6 },
	{{{  0x1,  0x0, 0xd6, 0x96,  0x0 }, { 0xd6, 0xd7, 0xe0, 0x41, 0x5e }}, 0x4a,  0x2,  0x1,   0xed,  0x5 },
	{{{  0x0,  0x9, 0xa9, 0x55,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x1,   0x82,  0x6 },
	{{{  0x2,  0x0, 0xc6, 0x96,  0x0 }, { 0xe0,  0x0, 0xe0, 0x40,  0x0 }},  0x1,  0x2,  0x1,  0x123,  0x5 },
	{{{  0x5,  0x0, 0xf6, 0x56,  0x0 }, { 0xf7, 0xff, 0xb3, 0x90, 0x4f }},  0x1,  0x2,  0x1,  0x15b,  0x5 },
	{{{  0x1,  0x0, 0xf7, 0x14,  0x0 }, { 0xf7, 0xff, 0x36, 0x90, 0x79 }}, 0xe7,  0x1,  0x1,  0x1ac,  0x5 },
	{{{  0x0,  0x0, 0xf6, 0x56,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x1,  0x2,  0x1,  0x18b,  0x5 },
	{{{  0x0, 0x83, 0xfb,  0x5,  0x0 }, { 0xf7, 0x41, 0x39, 0x90, 0x79 }},  0x1,  0x1,  0x1,   0xc8,  0x5 },
	{{{  0x0,  0x0, 0xff,  0x5,  0x0 }, { 0xf7, 0xff, 0x36, 0x90, 0x79 }}, 0xe7,  0x1,  0x1,   0xf9,  0x5 },
	{{{  0x1,  0x0, 0xa0,  0x5,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x2,  0x1,  0x27a,  0x6 },
	{{{  0x0,  0x5, 0xf3,  0x6,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x2,  0x1,  0x108,  0x7 },
	{{{  0x1,  0x0, 0xf9, 0x34,  0x0 }, { 0xf7, 0xff, 0x36, 0x90, 0x79 }}, 0xe7,  0x1,  0x1,  0x147,  0x4 },
	{{{  0x0,  0x0, 0xf7, 0x16,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x2,  0x1,  0x120,  0x6 },
	{{{  0x1,  0x0, 0xff,  0x5,  0x0 }, { 0xf7, 0xff, 0x36, 0x90, 0x79 }}, 0xe7,  0x1,  0x1,   0x42,  0x6 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x1,  0x0, 0xff,  0x5,  0x0 }, { 0xf7, 0xff, 0x36, 0x90, 0x79 }}, 0xe7,  0x1,  0x1,   0x6d,  0x5 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 },
	{{{  0x0,  0x0,  0x0,  0x0,  0x0 }, {  0x0,  0x0,  0x0,  0x0,  0x0 }},  0x0,  0x0,  0x0,  0x3fc,  0x4 }
};

const uint16 melodicFrequencies[36] = {
	 0x55,   0x5a,   0x60,   0x66,   0x6c,   0x72,   0x79,   0x80,   0x88,
	 0x90,   0x99,   0xa1,   0xab,   0xb5,   0xc0,   0xcc,   0xd8,   0xe5,
	 0xf2,  0x101,  0x110,  0x120,  0x132,  0x143,  0x156,  0x16b,  0x181,
	0x198,  0x1b0,  0x1ca,  0x1e5,  0x202,  0x220,  0x241,  0x263,  0x286
};

class AdLibDriver;

class AdLibChannel : public MidiChannel_MPU401 {
public:
	void reset();

	uint8 _program;
	uint8 _volume;
	uint8 _pedal;
};

struct MelodicVoice {
	bool _used;
	uint8 _channel;
	uint8 _program;

	uint8 _key;
	uint32 _timestamp;
	uint16 _frequency;
	int8 _octave;
};

class AdLibDriver : public MidiDriver_Emulated {
public:
	AdLibDriver(Audio::Mixer *mixer) : MidiDriver_Emulated(mixer) {
		for (uint i = 0; i < 16; ++i)
			_channels[i].init(this, i);
	}

	int open();
	void close();
	void send(uint32 b);
	MidiChannel *allocateChannel();
	MidiChannel *getPercussionChannel() { return &_channels[9]; }

	bool isStereo() const { return false; }
	int getRate() const { return _mixer->getOutputRate(); }
	int readBuffer(int16 *data, const int numSamples);

	void generateSamples(int16 *buf, int len) {}
	virtual void setTimerCallback(void *timerParam, Common::TimerManager::TimerProc timerProc) {
		_adlibTimerProc = timerProc;
		_adlibTimerParam = timerParam;
	}

protected:
	OPL::OPL *_opl;
	AdLibChannel _channels[16];
	MelodicVoice _voices[kNumMelodic];
	uint8 _notesPerPercussion[kNumPercussion];

	uint _lastVoice;

	uint8 _percussionMask;

	void noteOff(uint8 channel, uint8 note);
	void noteOn(uint8 channel, uint8 note, uint8 velocity);
	void allNotesOff();
	void setModulationWheel(uint8 channel, uint8 value);
	void setFootController(uint8 channel, uint8 value);
	void setVolume(uint8 channel, uint8 value);
	void setPitchBend(uint8 channel, int16 value);

	void playNote(uint8 voice, uint8 octave, uint16 frequency);

	void programOperatorSimple(uint8 offset, const OPLOperator &op);
	void programOperator(uint8 offset, const OPLOperator &op);
	void setOperatorLevel(uint8 offset, const OPLOperator &op, uint8 velocity, uint8 channel, bool forceVolume);

	void setupPercussion(const PercussionNote &note);
	void playPercussion(uint8 channel, const PercussionNote &note, uint8 velocity);

	void programMelodicVoice(uint8 voice, uint8 program);
	void playMelodicNote(uint8 voice, uint8 channel, uint8 note, uint8 velocity);
	void muteMelodicVoice(uint8 voice);

	void initVoices();

private:
	void onTimer();

	Common::TimerManager::TimerProc _adlibTimerProc;
	void *_adlibTimerParam;
};

MidiDriver *createAdLibDriver() {
	return new AdLibDriver(g_system->getMixer());
}

void AdLibChannel::reset() {
	_program = 0;
	_volume = 127;
	_pedal = 0;
}

/*
	bit 7 - Clear:  AM depth is 1 dB
	bit 6 - Clear:  Vibrato depth is 7 cent
	bit 5 - Set:    Rhythm enabled  (6 melodic voices)
	bit 4 - Bass drum off
	bit 3 - Snare drum off
	bit 2 - Tom tom off
	bit 1 - Cymbal off
	bit 0 - Hi Hat off
*/
const uint8 kDefaultPercussionMask = 0x20;

int AdLibDriver::open() {
	if (_isOpen)
		return MERR_ALREADY_OPEN;

	MidiDriver_Emulated::open();

	_opl = OPL::Config::create();
	_opl->init();
	_opl->writeReg(0x1, 0x20); // set bit 5 (enable all waveforms)

	// Reset the OPL registers.
	for (uint i = 0; i < kNumVoices; ++i) {
		_opl->writeReg(0xA0 + i, 0); // frequency
		_opl->writeReg(0xB0 + i, 0); // key on
		_opl->writeReg(0xC0 + i, 0); // feedback
	}
	_opl->writeReg(0xBD, kDefaultPercussionMask);

	initVoices();

	_opl->start(new Common::Functor0Mem<void, AdLibDriver>(this, &AdLibDriver::onTimer));
	_mixer->playStream(Audio::Mixer::kMusicSoundType, &_mixerSoundHandle, this, -1, Audio::Mixer::kMaxChannelVolume, 0, DisposeAfterUse::NO, true);
	return 0;
}

void AdLibDriver::close() {
	if (!_isOpen)
		return;

	_isOpen = false;
	_mixer->stopHandle(_mixerSoundHandle);

	delete _opl;
}

void AdLibDriver::send(uint32 b) {
	uint channel = b & 0xf;
	uint cmd = (b >> 4) & 0xf;
	uint param1 = (b >> 8) & 0xff;
	uint param2 = (b >> 16) & 0xff;

	switch (cmd) {
	case 8:
		noteOff(channel, param1);
		break;
	case 9:
		// TODO: map volume?
		noteOn(channel, param1, param2);
		break;
	case 11:
		// controller change
		switch (param1) {
		case 1:
			setModulationWheel(channel, param2);
			break;
		case 4:
			setFootController(channel, param2);
			break;
		case 7:
			setVolume(channel, param2);
			break;
		case 123:
			// all notes off
			allNotesOff();
			break;
		}
		break;
	case 12:
		// program change
		_channels[channel]._program = param1;
		break;
	case 14:
		setPitchBend(channel, (param1 | (param2 << 7)) - 0x2000);
		break;
	}
}

void AdLibDriver::noteOff(uint8 channel, uint8 note) {
	if (channel == 9) {
		if (note < 35 || note > 81)
			return;

		_percussionMask &= ~(1 << percussionNotes[note - 35].percussion);
		_opl->writeReg(0xBD, _percussionMask);
		return;
	}

	for (int i = kNumMelodic - 1; i >= 0; --i) {
		if (_voices[i]._channel != channel)
			continue;
		if (_voices[i]._key != note)
			continue;
		muteMelodicVoice(i);
		_voices[i]._used = false;
		return;
	}

	//debug(1, "failed to find voice off for channel %d, note %d", channel, note);
}

void AdLibDriver::noteOn(uint8 channel, uint8 note, uint8 velocity) {
	if (channel == 9) {
		if (note < 35 || note > 81)
			return;

		const PercussionNote &info = percussionNotes[note - 35];
		if (!info.valid)
			return;

		if (note != _notesPerPercussion[info.percussion]) {
			setupPercussion(info);
			_notesPerPercussion[info.percussion] = note;
		}

		playPercussion(channel, info, velocity);
		return;
	}

	if (velocity == 0) {
		noteOff(channel, note);
		return;
	}

	// We want to play a note on a melodic (voice) channel.

	// First, look for a voice playing the same note with the same program.
	for (uint i = 0; i < kNumMelodic; ++i) {
		if (_voices[i]._channel != channel || _voices[i]._key != note)
			continue;
		if (_voices[i]._program != _channels[channel]._program)
			continue;
		muteMelodicVoice(i);
		playMelodicNote(i, channel, note, velocity);
		return;
	}

	// The loops below try to start at _lastVoice and find a voice to use.
	// They ignore _lastVoice itself, and update _lastVoice if they succeed.

	// Then, try finding a melodic voice with the same program.
	for (uint i = (_lastVoice + 1) % kNumMelodic; i != _lastVoice; i = (i + 1) % kNumMelodic) {
		if (_voices[i]._used)
			continue;
		if (_voices[i]._program != _channels[channel]._program)
			continue;
		playMelodicNote(i, channel, note, velocity);
		_lastVoice = i;
		return;
	}

	// Then, try finding a free melodic voice of any kind.
	for (uint i = (_lastVoice + 1) % kNumMelodic; i != _lastVoice; i = (i + 1) % kNumMelodic) {
		if (_voices[i]._used)
			continue;
		programMelodicVoice(i, _channels[channel]._program);
		playMelodicNote(i, channel, note, velocity);
		_lastVoice = i;
		return;
	}

	// Then just try finding a melodic voice with the same program,
	// and steal it.
	for (uint i = (_lastVoice + 1) % kNumMelodic; i != _lastVoice; i = (i + 1) % kNumMelodic) {
		if (_voices[i]._program != _channels[channel]._program)
			continue;
		muteMelodicVoice(i);
		playMelodicNote(i, channel, note, velocity);
		_lastVoice = i;
		return;
	}

	// Finally, just take control of the channel used least recently.
	uint voiceId = 0;
	uint32 bestTimestamp = 0xffffffff;
	for (uint i = 0; i < kNumMelodic; ++i)
		if (bestTimestamp > _voices[i]._timestamp) {
			voiceId = i;
			bestTimestamp = _voices[i]._timestamp;
		}

	//debug(1, "ran out of voices for channel %d, note %d, program %d: reused voice %d", channel, note, _channels[channel]._program, voiceId);
	programMelodicVoice(voiceId, _channels[channel]._program);
	playMelodicNote(voiceId, channel, note, velocity);
	_lastVoice = voiceId;
}

// TODO: this doesn't match original
void AdLibDriver::allNotesOff() {
	for (uint i = 0; i < kNumMelodic; ++i) {
		muteMelodicVoice(i);
		_voices[i]._used = false;
	}

	_percussionMask = kDefaultPercussionMask;
	_opl->writeReg(0xBD, kDefaultPercussionMask);
}

void AdLibDriver::setModulationWheel(uint8 channel, uint8 value) {
	if (value >= 64)
		_percussionMask |= 0x80;
	else
		_percussionMask &= 0x7f;

	_opl->writeReg(0xBD, _percussionMask);
}

void AdLibDriver::setFootController(uint8 channel, uint8 value) {
	_channels[channel]._pedal = (value >= 64);
}

void AdLibDriver::setVolume(uint8 channel, uint8 value) {
	_channels[channel]._volume = value;
}

void AdLibDriver::setPitchBend(uint8 channel, int16 value) {
	for (uint i = 0; i < kNumMelodic; ++i) {
		if (_voices[i]._channel != channel || !_voices[i]._used)
			continue;

		// index into frequency table
		uint f = 12 + (_voices[i]._key % 12);

		int16 bendAmount = value;
		if (bendAmount > 0) {
			// bend up two semitones
			bendAmount *= (melodicFrequencies[f + 2] - melodicFrequencies[f]);
		} else {
			// bend down two semitones
			bendAmount *= (melodicFrequencies[f] - melodicFrequencies[f - 2]);
		}
		bendAmount /= 0x2000;
		bendAmount += melodicFrequencies[f]; // add the base frequency
		playNote(i, _voices[i]._octave, bendAmount);
		_voices[i]._timestamp = g_system->getMillis();
	}
}

void AdLibDriver::playNote(uint8 voice, uint8 octave, uint16 frequency) {
	/* Percussions are always fed keyOn = 0 even to set the note, as they are activated using the
	   BD register instead. I wonder if they can just be fed the same value as melodic voice and
	   be done with it. */
	uint8 keyOn = (voice < kNumMelodic) ? 0x20 : 0;

	// key on, octave, high 2 bits of frequency
	_opl->writeReg(0xB0 + voice, keyOn | ((octave & 7) << 2) | ((frequency >> 8) & 3));
	// low 8 bits of frequency
	_opl->writeReg(0xA0 + voice, frequency & 0xff);
}

void AdLibDriver::programOperatorSimple(uint8 offset, const OPLOperator &op) {
	_opl->writeReg(0x40 + offset, op.levels & LEVEL_MASK);
	_opl->writeReg(0x60 + offset, op.attackDecay);
	_opl->writeReg(0x80 + offset, op.sustainRelease);
}

void AdLibDriver::programOperator(uint8 offset, const OPLOperator &op) {
	_opl->writeReg(0x20 + offset, op.characteristic);
	_opl->writeReg(0x60 + offset, op.attackDecay);
	_opl->writeReg(0x80 + offset, op.sustainRelease);
	_opl->writeReg(0xE0 + offset, op.waveform);
	_opl->writeReg(0x40 + offset, op.levels);
}

const uint16 adlibLogVolume[] = {
	0, 37, 58, 73, 85, 95, 103, 110, 116, 121, 127, 131, 135, 139, 143, 146,
	149, 153, 155, 158, 161, 163, 165, 168, 170, 172, 174, 176, 178, 179, 181, 183,
	184, 186, 188, 189, 191, 192, 193, 195, 196, 197, 198, 200, 201, 202, 203, 204,
	205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 219,
	220, 221, 222, 223, 223, 224, 225, 226, 226, 227, 228, 228, 229, 230, 231, 231,
	232, 233, 233, 234, 234, 235, 236, 236, 237, 237, 238, 239, 239, 240, 240, 241,
	241, 242, 242, 243, 244, 244, 245, 245, 246, 246, 247, 247, 248, 248, 248, 249,
	249, 250, 250, 251, 251, 252, 252, 253, 253, 253, 254, 254, 255, 255, 256, 256,
	256
};

void AdLibDriver::setOperatorLevel(uint8 offset, const OPLOperator &op, uint8 velocity, uint8 channel, bool forceVolume) {
	uint8 programLevel = LEVEL_MASK;
	if (!forceVolume)
		programLevel -= (op.levels & LEVEL_MASK);

	uint32 noteLevel = adlibLogVolume[velocity];
	uint32 channelLevel = adlibLogVolume[_channels[channel]._volume];
	// programLevel comes from the static data and is probably already in the correct logarithmic scale
	uint32 finalLevel = LEVEL_MASK - ((noteLevel * channelLevel * programLevel) >> 16);

	// high 2 bits are scaling level, the rest is (inversed) volume
	_opl->writeReg(0x40 + offset, (op.levels & 0xc0) | (finalLevel & 0x3f));
}

const uint8 operatorOffsetsForPercussion[] = {
	0x11, // hi-hat
	0x15, // cymbal
	0x12, // tom tom
	0x14  // snare drum
};

void AdLibDriver::setupPercussion(const PercussionNote &note) {
	if (note.percussion < 4) {
		// simple percussion (1 operator)

		// turn off relevant percussion
		_percussionMask &= ~(1 << note.percussion);
		_opl->writeReg(0xBD, _percussionMask);

		programOperatorSimple(operatorOffsetsForPercussion[note.percussion], note.op[0]);
		return;
	}

	// bass drum (2 operators)

	// turn off bass drum
	_percussionMask &= ~(0x10);
	_opl->writeReg(0xBD, _percussionMask);

	programOperator(0x10, note.op[0]);
	programOperator(0x13, note.op[1]);

	_opl->writeReg(0xC0 + 6, note.feedbackAlgo);
}

void AdLibDriver::playPercussion(uint8 channel, const PercussionNote &note, uint8 velocity) {
	if (note.percussion < 4) {
		// simple percussion (1 operator)

		// turn off relevant percussion
		_percussionMask &= ~(1 << note.percussion);
		_opl->writeReg(0xBD, _percussionMask);

		setOperatorLevel(operatorOffsetsForPercussion[note.percussion], note.op[0], velocity, channel, true);

		if (note.percussion == 2) {
			// tom tom
			playNote(8, note.octave, note.frequency);
		} else if (note.percussion == 3) {
			// snare drum
			playNote(7, note.octave, note.frequency);
		}

		// turn on relevant percussion
		_percussionMask |= (1 << note.percussion);
		_opl->writeReg(0xBD, _percussionMask);
		return;
	}

	// turn off bass drum
	_percussionMask &= ~(0x10);
	_opl->writeReg(0xBD, _percussionMask);

	if (note.feedbackAlgo & 1) {
		// operators 1 and 2 in additive synthesis
		setOperatorLevel(0x10, note.op[0], velocity, channel, true);
		setOperatorLevel(0x13, note.op[1], velocity, channel, true);
	} else {
		// operator 2 is modulating operator 1
		setOperatorLevel(0x13, note.op[1], velocity, channel, true);
	}

	playNote(6, note.octave, note.frequency);

	// turn on bass drum
	_percussionMask |= 0x10;
	_opl->writeReg(0xBD, _percussionMask);
}

const uint8 offset1ForMelodic[kNumVoices] = { 0x0,  0x1,  0x2,  0x8,  0x9,  0xa, 0x10, 0x11, 0x12 };
const uint8 offset2ForMelodic[kNumVoices] = { 0x3,  0x4,  0x5,  0xb,  0xc,  0xd, 0x13, 0x14, 0x15 };

void AdLibDriver::programMelodicVoice(uint8 voice, uint8 program) {
	assert(program < 128);
	assert(voice < kNumMelodic);

	const MelodicProgram &info = melodicPrograms[program];
	uint8 offset1 = offset1ForMelodic[voice];
	uint8 offset2 = offset2ForMelodic[voice];

	// Start at lowest volume.
	_opl->writeReg(0x40 + offset1, LEVEL_MASK);
	_opl->writeReg(0x40 + offset2, LEVEL_MASK);

	muteMelodicVoice(voice);

	programOperator(offset1, info.op[0]);
	programOperator(offset2, info.op[1]);

	_opl->writeReg(0xC0 + voice, info.feedbackAlgo);
}

void AdLibDriver::playMelodicNote(uint8 voice, uint8 channel, uint8 note, uint8 velocity) {
	assert(voice < kNumMelodic);

	uint8 octave = note / 12;
	uint8 f = 12 + (note % 12);

	if (octave > 7)
		octave = 7;

	const MelodicProgram &info = melodicPrograms[_channels[channel]._program];
	uint8 offset1 = offset1ForMelodic[voice];
	uint8 offset2 = offset2ForMelodic[voice];

	if (info.feedbackAlgo & 1) {
		setOperatorLevel(offset1, info.op[0], velocity, channel, false);
		setOperatorLevel(offset2, info.op[1], velocity, channel, false);
	} else {
		setOperatorLevel(offset2, info.op[1], velocity, channel, true);
	}

	playNote(voice, octave, melodicFrequencies[f]);

	_voices[voice]._program = _channels[channel]._program;
	_voices[voice]._key = note;
	_voices[voice]._channel = channel;
	_voices[voice]._timestamp = g_system->getMillis();
	_voices[voice]._frequency = melodicFrequencies[f];
	_voices[voice]._octave = octave;
	_voices[voice]._used = true;
}

void AdLibDriver::muteMelodicVoice(uint8 voice) {
	_opl->writeReg(0xB0 + voice, 0 | ((_voices[voice]._octave & 7) << 2) | ((_voices[voice]._frequency >> 8) & 3));
}

MidiChannel *AdLibDriver::allocateChannel() {
	for (uint i = 0; i < 16; ++i) {
		if (i == 9)
			continue;

		if (_channels[i].allocate())
			return &_channels[i];
	}

	return NULL;
}

int AdLibDriver::readBuffer(int16 *data, const int numSamples) {
	return _opl->readBuffer(data, numSamples);
}

void AdLibDriver::onTimer() {
	if (_adlibTimerProc)
		(*_adlibTimerProc)(_adlibTimerParam);
}

void AdLibDriver::initVoices() {
	_percussionMask = kDefaultPercussionMask;
	_opl->writeReg(0xBD, _percussionMask);

	for (uint i = 0; i < 16; ++i)
		_channels[i].reset();

	for (uint i = 0; i < kNumMelodic; ++i) {
		_voices[i]._key = 0xff;
		_voices[i]._program = 0xff;
		_voices[i]._channel = 0xff;
		_voices[i]._timestamp = 0;
		_voices[i]._frequency = 0;
		_voices[i]._octave = 0;
		_voices[i]._used = false;
	}

	for (uint i = 0; i < kNumPercussion; ++i)
		_notesPerPercussion[i] = 0xff;

	_lastVoice = 0;
}

} // namespace Parallaction
