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

#include "efh/constants.h"

namespace Efh {

const uint8 kFontWidthArray[96] = {
	3, 2, 3, 5, 5, 5, 5, 2, 3, 3, 5, 5, 3, 3, 2, 7, 4, 3, 4, 4, 5, 4, 4, 4, 4, 4, 3, 4, 4, 5, 4, 5, 1, 4, 4, 4,
	4, 4, 4, 4, 4, 3, 4, 4, 4, 7, 5, 4, 4, 4, 4, 4, 5, 4, 5, 7, 5, 5, 5, 3, 7, 3, 5, 0, 2, 4, 4, 4, 4, 4, 4, 4,
	4, 1, 2, 4, 1, 7, 4, 4, 4, 4, 4, 4, 3, 4, 5, 7, 4, 4, 5, 3, 0, 3, 0, 0};

const uint8 kFontExtraLinesArray[96] = {
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 3,
	1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 1, 1, 2, 1, 1, 0, 1, 0, 0};

const Font kFontData[96] = {
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x80, 0x80, 0x80, 0x80, 0x80, 0x00, 0x80, 0x00},
	{0xA0, 0xA0, 0xA0, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x50, 0xF8, 0x50, 0xF8, 0x50, 0x00, 0x00},
	{0x20, 0x78, 0xA0, 0x70, 0x28, 0xF0, 0x20, 0x00},
	{0xC8, 0xC8, 0x10, 0x20, 0x40, 0x98, 0x98, 0x00},
	{0x20, 0x50, 0x20, 0x40, 0xA8, 0x90, 0x68, 0x00},
	{0x40, 0x40, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x40, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x40},
	{0x40, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x40},
	{0x00, 0xA8, 0x70, 0xF8, 0x70, 0xA8, 0x00, 0x00},
	{0x00, 0x20, 0x20, 0xF8, 0x20, 0x20, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x20, 0x20, 0x40},
	{0x00, 0x00, 0x00, 0xE0, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x40, 0x00},
	{0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x00},
	{0x60, 0x90, 0x90, 0x90, 0x90, 0x90, 0x60, 0x00},
	{0x40, 0xC0, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00},
	{0x60, 0x90, 0x10, 0x20, 0x40, 0x80, 0xF0, 0x00},
	{0x60, 0x90, 0x10, 0x20, 0x10, 0x90, 0x60, 0x00},
	{0x10, 0x30, 0x50, 0x90, 0xF8, 0x10, 0x10, 0x00},
	{0xF0, 0x80, 0xE0, 0x10, 0x10, 0x90, 0x60, 0x00},
	{0x60, 0x90, 0x80, 0xE0, 0x90, 0x90, 0x60, 0x00},
	{0xF0, 0x10, 0x20, 0x20, 0x40, 0x40, 0x40, 0x00},
	{0x60, 0x90, 0x90, 0x60, 0x90, 0x90, 0x60, 0x00},
	{0x60, 0x90, 0x90, 0x70, 0x10, 0x90, 0x60, 0x00},
	{0x00, 0x00, 0x40, 0x00, 0x00, 0x40, 0x00, 0x00},
	{0x00, 0x00, 0x20, 0x00, 0x00, 0x20, 0x40, 0x00},
	{0x10, 0x20, 0x40, 0x80, 0x40, 0x20, 0x10, 0x00},
	{0x00, 0x00, 0xF8, 0x00, 0x00, 0xF8, 0x00, 0x00},
	{0x80, 0x40, 0x20, 0x10, 0x20, 0x40, 0x80, 0x00},
	{0x70, 0x88, 0x08, 0x10, 0x20, 0x00, 0x20, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x60, 0x90, 0x90, 0xF0, 0x90, 0x90, 0x90, 0x00},
	{0xE0, 0x90, 0x90, 0xE0, 0x90, 0x90, 0xE0, 0x00},
	{0x60, 0x90, 0x80, 0x80, 0x80, 0x90, 0x60, 0x00},
	{0xE0, 0x90, 0x90, 0x90, 0x90, 0x90, 0xE0, 0x00},
	{0xF0, 0x80, 0x80, 0xE0, 0x80, 0x80, 0xF0, 0x00},
	{0xF0, 0x80, 0x80, 0xE0, 0x80, 0x80, 0x80, 0x00},
	{0x60, 0x90, 0x80, 0xB0, 0x90, 0x90, 0x70, 0x00},
	{0x90, 0x90, 0x90, 0xF0, 0x90, 0x90, 0x90, 0x00},
	{0xE0, 0x40, 0x40, 0x40, 0x40, 0x40, 0xE0, 0x00},
	{0x10, 0x10, 0x10, 0x10, 0x10, 0x90, 0x60, 0x00},
	{0x90, 0x90, 0x90, 0xE0, 0x90, 0x90, 0x90, 0x00},
	{0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xF0, 0x00},
	{0x82, 0xC6, 0xAA, 0x92, 0x82, 0x82, 0x82, 0x00},
	{0x88, 0x88, 0xC8, 0xA8, 0x98, 0x88, 0x88, 0x00},
	{0x60, 0x90, 0x90, 0x90, 0x90, 0x90, 0x60, 0x00},
	{0xE0, 0x90, 0x90, 0xE0, 0x80, 0x80, 0x80, 0x00},
	{0x60, 0x90, 0x90, 0x90, 0x90, 0x90, 0x60, 0x10},
	{0xE0, 0x90, 0x90, 0xE0, 0x90, 0x90, 0x90, 0x00},
	{0x60, 0x90, 0x80, 0x60, 0x10, 0x90, 0x60, 0x00},
	{0xF8, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x00},
	{0x90, 0x90, 0x90, 0x90, 0x90, 0x90, 0x60, 0x00},
	{0x88, 0x88, 0x88, 0x50, 0x50, 0x20, 0x20, 0x00},
	{0x82, 0x82, 0x82, 0x92, 0xAA, 0xC6, 0x82, 0x00},
	{0x88, 0x88, 0x50, 0x20, 0x50, 0x88, 0x88, 0x00},
	{0x88, 0x88, 0x50, 0x20, 0x20, 0x20, 0x20, 0x00},
	{0xF8, 0x08, 0x10, 0x20, 0x40, 0x80, 0xF8, 0x00},
	{0xC0, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0xC0},
	{0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x00},
	{0x60, 0x20, 0x20, 0x20, 0x20, 0x20, 0x20, 0x60},
	{0x20, 0x50, 0x88, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x80, 0x80, 0x40, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x60, 0x10, 0x70, 0x90, 0x70, 0x00},
	{0x80, 0x80, 0xE0, 0x90, 0x90, 0x90, 0xE0, 0x00},
	{0x00, 0x00, 0x60, 0x90, 0x80, 0x90, 0x60, 0x00},
	{0x10, 0x10, 0x70, 0x90, 0x90, 0x90, 0x70, 0x00},
	{0x00, 0x00, 0x60, 0x90, 0xF0, 0x80, 0x60, 0x00},
	{0x30, 0x40, 0xE0, 0x40, 0x40, 0x40, 0x40, 0x00},
	{0x70, 0x90, 0x90, 0x90, 0x70, 0x10, 0xE0, 0x00},
	{0x80, 0x80, 0xE0, 0x90, 0x90, 0x90, 0x90, 0x00},
	{0x80, 0x00, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00},
	{0x40, 0x00, 0x40, 0x40, 0x40, 0x40, 0x40, 0x80},
	{0x80, 0x80, 0x90, 0x90, 0xE0, 0x90, 0x90, 0x00},
	{0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x80, 0x00},
	{0x00, 0x00, 0xEC, 0x92, 0x92, 0x92, 0x92, 0x00},
	{0x00, 0x00, 0xE0, 0x90, 0x90, 0x90, 0x90, 0x00},
	{0x00, 0x00, 0x60, 0x90, 0x90, 0x90, 0x60, 0x00},
	{0x00, 0xE0, 0x90, 0x90, 0x90, 0xE0, 0x80, 0x80},
	{0x00, 0x70, 0x90, 0x90, 0x90, 0x70, 0x10, 0x10},
	{0x00, 0x00, 0xB0, 0xC0, 0x80, 0x80, 0x80, 0x00},
	{0x00, 0x00, 0x70, 0x80, 0x60, 0x10, 0xE0, 0x00},
	{0x40, 0x40, 0xE0, 0x40, 0x40, 0x40, 0x40, 0x00},
	{0x00, 0x00, 0x90, 0x90, 0x90, 0x90, 0x70, 0x00},
	{0x00, 0x00, 0x88, 0x50, 0x50, 0x20, 0x20, 0x00},
	{0x00, 0x00, 0x92, 0x92, 0x92, 0x92, 0x6E, 0x00},
	{0x00, 0x00, 0x90, 0x90, 0x60, 0x90, 0x90, 0x00},
	{0x00, 0x90, 0x90, 0x90, 0x90, 0x70, 0x10, 0xE0},
	{0x00, 0x00, 0xF8, 0x10, 0x20, 0x40, 0xF8, 0x00},
	{0x20, 0x40, 0x40, 0x80, 0x40, 0x40, 0x20, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x80, 0x40, 0x40, 0x20, 0x40, 0x40, 0x80, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00},
	{0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}
};

const Encounter kEncounters[] {
	{"Indian", 0, 5, 50, {64, 64, 68, 70, 92}, 25, 2},
	{"Warrior", 0, 6, 85, {70, 64, 68, 70, 92}, 35, 2},
	{"Tracker", 0, 8, 115, {92, 64, 68, 70, 92}, 38, 2},
	{"Savage", 0, 15, 150, {92, 64, 68, 70, 92}, 50, 2},
	{"Chief", 0, 50, 200, {94, 64, 70, 92, 95}, 95, 2},
	{"Archer", 1, 5, 50, {70, 71, 64, 66, 69}, 35, 2},
	{"Bowman", 1, 10, 50, {70, 71, 64, 66, 69}, 50, 2},
	{"Ranger", 1, 20, 150, {70, 71, 64, 66, 69}, 45, 2},
	{"Censor", 2, 5, 35, {205, 64, 64, 64, 64}, 25, 2},
	{"Noisy Guy", 2, 7, 80, {205, 64, 64, 64, 64}, 27, 2},
	{"Cruiser", 2, 12, 55, {205, 210, 64, 64, 64}, 32, 2},
	{"Boomer", 2, 20, 110, {205, 210, 210, 64, 64}, 45, 2},
	{"Neanderthal", 3, 5, 65, {127, 127, 127, 127, 64}, 25, 2},
	{"Savage", 3, 7, 90, {127, 127, 127, 127, 64}, 35, 2},
	{"Roughian", 3, 15, 110, {127, 127, 127, 87, 64}, 37, 2},
	{"Troglodyte", 3, 20, 135, {127, 127, 127, 127, 64}, 45, 2},
	{"Scuba Guy", 4, 5, 50, {211, 64, 144, 165, 64}, 25, 2},
	{"Diver", 4, 12, 80, {211, 165, 144, 165, 64}, 28, 2},
	{"Surfer", 4, 10, 75, {212, 212, 144, 205, 64}, 30, 2},
	{"Warrior", 4, 15, 100, {66, 69, 68, 64, 66}, 35, 2},
	{"Maniac", 4, 20, 150, {214, 201, 205, 81, 90}, 38, 2},
	{"Loon", 4, 35, 250, {214, 201, 205, 81, 90}, 45, 2},
	{"Crypt Thing", 5, 15, 200, {215, 215, 215, 217, 217}, 35, 2},
	{"Crypt Corpse", 5, 20, 250, {215, 215, 215, 217, 217}, 40, 2},
	{"Zombie", 5, 25, 225, {215, 215, 215, 217, 217}, 45, 2},
	{"Dead Being", 5, 40, 350, {215, 215, 216, 217, 217}, 55, 2},
	{"Despair", 6, 10, 125, {127, 127, 128, 128, 129}, 25, 2},
	{"Apparition", 6, 15, 245, {127, 127, 128, 128, 129}, 29, 2},
	{"Burial Spirit", 6, 25, 300, {127, 128, 128, 129, 129}, 55, 2},
	{"Ghoul", 6, 32, 410, {127, 127, 128, 128, 129}, 70, 2},
	{"Skeleton", 6, 6, 75, {127, 127, 128, 128, 129}, 60, 2},
	{"Soul", 6, 40, 400, {127, 127, 128, 128, 129}, 62, 2},
	{"Projection", 6, 27, 350, {127, 127, 128, 128, 129}, 65, 2},
	{"Cowboy", 7, 5, 150, {90, 90, 90, 90, 91}, 25, 2},
	{"Sheriff", 7, 8, 250, {90, 90, 90, 91, 91}, 35, 2},
	{"Bad Bart", 7, 35, 500, {90, 90, 91, 91, 91}, 95, 2},
	{"Gun Slinger", 7, 20, 380, {90, 90, 91, 91, 91}, 55, 2},
	{"Fast Draw", 7, 17, 290, {90, 91, 91, 91, 91}, 45, 2},
	{"Quick Draw", 7, 30, 420, {90, 91, 92, 93, 92}, 65, 2},
	{"Dinosaur", 8, 35, 200, {128, 128, 128, 126, 126}, 25, 2},
	{"Biped", 8, 50, 225, {128, 128, 128, 126, 126}, 30, 2},
	{"Dino Beast", 8, 65, 250, {128, 128, 128, 126, 126}, 35, 2},
	{"Intellosaur", 8, 80, 380, {128, 128, 128, 126, 126}, 45, 2},
	{"Awful Animal", 8, 105, 495, {128, 128, 128, 126, 126}, 55, 2},
	{"Death Serpent", 9, 60, 450, {94, 97, 98, 99, 135}, 75, 2},
	{"Demon Snake", 9, 80, 580, {97, 98, 94, 99, 137}, 85, 2},
	{"Fire Lizard", 9, 100, 400, {135, 98, 99, 137, 136}, 95, 2},
	{"Winged Demon", 9, 110, 475, {97, 98, 138, 139, 140}, 100, 2},
	{"Duke of Hell", 10, 500, 2000, {137, 138, 139, 140, 135}, 100, 2},
	{"Beach Fiend", 10, 150, 580, {137, 138, 139, 136, 98}, 100, 2},
	{"Arch Devil", 10, 2000, 10000, {98, 97, 98, 140, 139}, 100, 2},
	{"Major Fiend", 10, 195, 666, {98, 99, 98, 99, 137}, 100, 2},
	{"Enforcer", 11, 20, 110, {127, 126, 76, 75, 145}, 25, 2},
	{"Grunt", 11, 30, 150, {163, 127, 161, 165, 152}, 35, 2},
	{"Behemoth", 11, 35, 175, {144, 148, 160, 161, 163}, 45, 2},
	{"Giant Demon", 11, 50, 245, {127, 107, 151, 155, 159}, 55, 2},
	{"Slaver", 11, 42, 225, {127, 124, 114, 115, 121}, 65, 2},
	{"Minor Demon", 12, 6, 100, {73, 73, 130, 130, 130}, 27, 2},
	{"Common Demon", 12, 9, 150, {73, 73, 130, 130, 130}, 30, 2},
	{"Small Demon", 12, 15, 175, {73, 73, 73, 73, 130}, 38, 2},
	{"Simple Demon", 12, 20, 200, {73, 73, 73, 130, 130}, 45, 2},
	{"Lesser Demon", 12, 12, 160, {73, 73, 73, 73, 73}, 32, 2},
	{"Warrior", 13, 7, 50, {65, 65, 66, 66, 64}, 30, 2},
	{"Gladiator", 13, 12, 95, {65, 65, 66, 66, 64}, 35, 2},
	{"Moutaineer", 13, 10, 80, {66, 66, 80, 72, 64}, 45, 2},
	{"Strong Guy", 13, 13, 98, {66, 66, 66, 66, 66}, 55, 2},
	{"Hell Private", 14, 10, 150, {66, 66, 66, 65, 65}, 35, 2},
	{"Hell Corporal", 14, 15, 150, {66, 66, 66, 65, 65}, 40, 2},
	{"Hell Sgt.", 14, 17, 150, {66, 66, 66, 65, 65}, 45, 2},
	{"Hell LT.", 14, 25, 245, {105, 66, 66, 65, 65}, 50, 2},
	{"Hell Guard", 14, 6, 100, {66, 66, 66, 65, 65}, 20, 2},
	{"Hell Soldier", 14, 35, 380, {106, 66, 66, 163, 65}, 65, 2},
	{"Demon Fighter", 14, 40, 400, {106, 105, 163, 65, 65}, 75, 2},
	{"Ice Beast", 15, 25, 650, {69, 69, 69, 68, 68}, 45, 2},
	{"Snow Fiend", 15, 30, 666, {132, 69, 69, 68, 68}, 55, 2},
	{"SalivaMonster", 15, 45, 750, {107, 110, 132, 157, 129}, 65, 2},
	{"Spit Grunt", 15, 40, 666, {107, 110, 132, 157, 129}, 75, 2},
	{"Cold Demon", 15, 42, 666, {107, 110, 68, 69, 69}, 85, 2},
	{"Insectoid", 16, 15, 400, {153, 152, 154, 161, 147}, 35, 2},
	{"Giant Insect", 16, 17, 400, {94, 96, 96, 202, 202}, 45, 2},
	{"Insect Guard", 16, 25, 400, {94, 96, 99, 202, 202}, 55, 2},
	{"Roaming Bug", 16, 35, 450, {94, 96, 99, 136, 134}, 45, 2},
	{"Blade Bug", 16, 45, 590, {135, 158, 156, 202, 202}, 45, 2},
	{"Logger", 17, 7, 125, {89, 78, 89, 89, 64}, 30, 2},
	{"Massacrer", 17, 10, 175, {89, 89, 89, 89, 64}, 35, 2},
	{"Murderer", 17, 12, 225, {89, 89, 89, 79, 64}, 38, 2},
	{"Crazy Guy", 17, 13, 235, {89, 87, 88, 89, 64}, 40, 2},
	{"Massive Dude", 17, 15, 250, {89, 89, 81, 89, 64}, 36, 2},
	{"Chainsaw Guy", 17, 11, 180, {89, 89, 88, 89, 64}, 45, 2},
	{"DevilDaughter", 18, 75, 850, {181, 182, 182, 181, 195}, 100, 2},
	{"Evil Woman", 18, 5, 85, {181, 182, 182, 181, 195}, 35, 2},
	{"Enchantress'", 18, 7, 150, {181, 182, 182, 181, 195}, 40, 2},    // The extra quote is in the original game
	{"Temptress'", 18, 9, 200, {181, 182, 182, 181, 195}, 55, 2},      // The extra quote is in the original game
	{"Lustivious'", 18, 100, 1750, {181, 182, 196, 197, 197}, 100, 1}, // The extra quote is in the original game
	{"Major Demon", 19, 25, 666, {106, 105, 163, 65, 65}, 45, 2},
	{"Giant Demon", 19, 50, 865, {106, 105, 163, 65, 65}, 55, 2},
	{"Gnarly Demon", 19, 75, 999, {106, 105, 163, 65, 65}, 65, 2},
	{"Pit Fiend", 19, 40, 777, {114, 113, 163, 163, 163}, 95, 2},
	{"Hellish Fiend", 19, 80, 1500, {113, 114, 113, 163, 163}, 100, 2},
	{"Monk", 20, 6, 75, {0, 0, 0, 0, 0}, 0, 2},
	{"Unholy Monk", 20, 12, 100, {202, 197, 96, 108, 149}, 30, 2},
	{"Evil Monk", 20, 15, 150, {202, 197, 96, 153, 149}, 33, 2},
	{"Sacrificer", 20, 18, 185, {202, 197, 108, 108, 108}, 37, 2},
	{"Nasty Guy", 20, 25, 200, {202, 197, 96, 153, 149}, 45, 2},
	{"Mutant Demon", 21, 15, 100, {93, 91, 90, 94, 95}, 35, 2},
	{"Hell Captain", 21, 25, 275, {93, 91, 90, 94, 95}, 37, 2},
	{"Muscle Demon", 21, 32, 350, {93, 91, 90, 94, 95}, 40, 2},
	{"Blaster Demon", 21, 60, 690, {93, 91, 90, 94, 95}, 45, 2},
	{"Knight", 22, 15, 150, {133, 133, 150, 128, 128}, 35, 2},
	{"Evil Knight", 22, 25, 200, {133, 150, 116, 122, 128}, 40, 2},
	{"UnJust Knight", 22, 35, 375, {133, 150, 128, 122, 128}, 45, 2},
	{"Astray Knight", 22, 50, 450, {133, 150, 120, 121, 128}, 65, 2},
	{"Anit-Paladin", 22, 75, 750, {109, 115, 128, 128, 128}, 85, 2},
	{"Moaning", 23, 3, 3, {72, 78, 81, 83, 83}, 50, 2},
	{"Tormented", 23, 5, 5, {72, 78, 81, 83, 83}, 50, 2},
	{"Suffering", 23, 4, 4, {72, 78, 81, 83, 83}, 50, 2},
	{"Starving Guy", 23, 2, 2, {72, 78, 81, 83, 83}, 50, 2},
	{"Withered Soul", 23, 1, 1, {72, 78, 81, 83, 83}, 50, 2},
	{"Ogre", 24, 20, 275, {109, 106, 65, 163, 163}, 45, 2},
	{"ElectroKnight", 24, 25, 290, {109, 106, 65, 163, 163}, 55, 2},
	{"Energy Demon", 24, 30, 320, {109, 106, 65, 163, 163}, 55, 2},
	{"Power Devil", 24, 35, 350, {107, 109, 114, 207, 207}, 65, 2},
	{"Sorcerer", 24, 42, 400, {109, 106, 65, 163, 163}, 75, 2},
	{"Enchanter", 24, 35, 350, {109, 106, 65, 163, 163}, 85, 2},
	{"Canon Monk", 28, 35, 100, {0, 0, 0, 0, 0}, 0, 2},
	{"Canon Monk", 28, 35, 100, {0, 0, 0, 0, 0}, 0, 2},
	{"Canon Monk", 28, 35, 100, {0, 0, 0, 0, 0}, 0, 2},
	{"Canon Monk", 28, 35, 100, {0, 0, 0, 0, 0}, 0, 2},
	{"Canon Monk", 28, 35, 100, {0, 0, 0, 0, 0}, 0, 2},
	{"Screamer", 26, 5, 35, {152, 152, 146, 145, 64}, 30, 2},
	{"Moaner", 26, 7, 40, {152, 152, 146, 145, 64}, 35, 2},
	{"Screacher", 26, 12, 85, {152, 152, 146, 145, 64}, 40, 2},
	{"Singer", 26, 15, 100, {152, 152, 146, 145, 64}, 45, 2},
	{"Pilot", 27, 12, 150, {90, 90, 90, 92, 92}, 35, 2},
	{"Crashed Pilot", 27, 20, 200, {90, 90, 90, 92, 92}, 40, 2},
	{"WW I Pilot", 27, 25, 225, {90, 90, 90, 92, 92}, 45, 2},
	{"WW II Pilot", 27, 35, 280, {94, 134, 136, 136, 92}, 55, 2},
	{"Boney Soldier", 27, 45, 350, {90, 134, 136, 137, 138}, 65, 2},
	{"ModernSoldier", 27, 75, 845, {97, 97, 98, 99, 94}, 95, 2},
	{"Surpriser", 28, 10, 100, {100, 101, 102, 103, 104}, 35, 2},
	{"Shocker", 28, 15, 350, {100, 101, 102, 103, 104}, 45, 2},
	{"Blast Monk", 28, 20, 400, {100, 101, 102, 103, 104}, 55, 2},
	{"Canon Monk", 28, 28, 480, {100, 101, 102, 103, 104}, 65, 2},
	{"Killer", 28, 35, 550, {100, 101, 102, 103, 104}, 75, 2},
	{"Rubber Necker", 29, 45, 1000, {152, 153, 144, 111, 112}, 20, 2},
	{"Skull Thing", 29, 60, 1250, {113, 114, 115, 105, 112}, 30, 2},
	{"Laser Eye", 29, 80, 1750, {94, 134, 135, 90, 91}, 40, 2},
	{"Beamer", 29, 100, 2200, {94, 134, 135, 90, 91}, 50, 2},
	{"Hideous Beast", 29, 150, 3500, {94, 134, 135, 90, 91}, 60, 2},
	{"Samurai", 30, 10, 35, {67, 67, 67, 68, 68}, 30, 2},
	{"Ninja", 30, 15, 90, {67, 67, 67, 68, 68}, 32, 2},
	{"SegaSamurai", 30, 20, 150, {67, 67, 67, 68, 68}, 45, 2},
	{"NintendoNinja", 30, 35, 220, {67, 67, 67, 68, 68}, 45, 2},
	{"OrientalSlayr", 30, 45, 250, {67, 67, 67, 68, 68}, 55, 2},
	{"Soldier", 31, 10, 100, {100, 101, 102, 90, 92}, 30, 2},
	{"Fighter", 31, 15, 125, {100, 93, 94, 96, 104}, 35, 2},
	{"Grenader", 31, 20, 175, {100, 101, 102, 103, 104}, 45, 2},
	{"Gunner", 31, 25, 190, {137, 136, 135, 134, 94}, 50, 2},
	{"Scratche", 32, 6, 95, {0, 0, 0, 0, 0}, 0, 2},
	{"Claw", 32, 15, 150, {0, 0, 0, 0, 0}, 0, 2},
	{"Claw Demon", 32, 25, 264, {0, 0, 0, 0, 0}, 0, 2},
	{"Talon Demon", 32, 35, 300, {0, 0, 0, 0, 0}, 0, 2},
	{"Malicioun", 32, 50, 350, {0, 0, 0, 0, 0}, 0, 2},
	{"Imp", 33, 3, 100, {64, 64, 131, 131, 131}, 35, 2},
	{"Tiny Demon", 33, 6, 150, {64, 132, 131, 131, 131}, 40, 2},
	{"Short Devil", 33, 12, 255, {132, 132, 131, 131, 132}, 45, 2},
	{"Gremlin", 33, 25, 300, {64, 64, 131, 131, 131}, 50, 2},
	{"Thug", 34, 8, 175, {93, 93, 94, 92, 95}, 30, 2},
	{"Punk", 34, 15, 250, {93, 93, 94, 92, 95}, 35, 2},
	{"Killer", 34, 18, 275, {93, 93, 94, 92, 95}, 40, 2},
	{"Street Dude", 34, 25, 350, {93, 93, 94, 92, 95}, 45, 2},
	{"Slasher", 35, 5, 190, {131, 131, 131, 131, 131}, 30, 2},
	{"Blade Demon", 35, 15, 250, {132, 131, 131, 131, 131}, 35, 2},
	{"Cleaver Devil", 35, 30, 290, {132, 132, 131, 131, 131}, 45, 2},
	{"Stench Beast", 36, 6, 75, {0, 0, 0, 0, 0}, 0, 2},
	{"Breather", 36, 10, 150, {0, 0, 0, 0, 0}, 0, 2},
	{"Smelly Thing", 36, 15, 175, {0, 0, 0, 0, 0}, 0, 2},
	{"Ugly Devil", 36, 25, 225, {0, 0, 0, 0, 0}, 0, 2},
	{"Surf Nazi", 37, 5, 67, {64, 86, 218, 218, 219}, 30, 2},
	{"Beacher", 37, 8, 95, {64, 86, 218, 218, 219}, 35, 2},
	{"Scum", 37, 12, 125, {64, 86, 218, 218, 219}, 45, 2},
	{"Waste", 37, 18, 150, {64, 86, 218, 218, 219}, 55, 2},
	{"Duelist", 38, 6, 65, {65, 65, 65, 147, 66}, 40, 2},
	{"Sword Guy", 38, 10, 87, {65, 155, 65, 153, 66}, 50, 2},
	{"Muskateer", 38, 15, 97, {65, 65, 154, 66, 66}, 65, 2},
	{"Valkyrie", 39, 7, 37, {65, 65, 65, 66, 66}, 35, 2},
	{"WarriorMaiden", 39, 20, 137, {65, 65, 65, 66, 66}, 55, 2},
	{"Worm King", 40, 150, 4500, {202, 194, 195, 181, 181}, 100, 2},
	{"Worm Lord", 40, 100, 3300, {202, 194, 195, 181, 181}, 100, 2},
	{"Eye of Hell", 40, 60, 1200, {202, 194, 195, 181, 181}, 70, 2},
	{"Visionary", 40, 40, 800, {202, 194, 195, 181, 181}, 55, 2},
	{"Thing", 40, 25, 650, {202, 194, 195, 181, 181}, 45, 2},
	{"Zombie", 41, 10, 450, {97, 97, 98, 98, 127}, 35, 2},
	{"Police Dude", 41, 25, 350, {97, 161, 148, 98, 127}, 45, 2},
	{"Cop", 41, 15, 275, {97, 152, 98, 156, 127}, 30, 2},
	{"Dark Cop", 41, 20, 300, {97, 162, 98, 98, 127}, 35, 2},
	{"Bully Cop", 41, 25, 350, {97, 97, 98, 98, 127}, 45, 2},
	{"Drowning", 42, 10, 50, {0, 0, 0, 0, 0}, 0, 2},
	{"Watery Guy", 42, 35, 150, {0, 0, 0, 0, 0}, 0, 2},
	{"Evangelist", 43, 8, 50, {0, 0, 0, 0, 0}, 0, 2},
	{"Preacher", 43, 15, 150, {0, 0, 0, 0, 0}, 0, 2},
	{"Smooth Talker", 43, 20, 175, {0, 0, 0, 0, 0}, 0, 2},
	{"Hulk", 44, 20, 100, {220, 220, 220, 220, 202}, 32, 0},
	{"MIGHTY Guy", 44, 30, 200, {220, 220, 220, 220, 202}, 43, 2},
	{"Powerful Dude", 44, 45, 400, {220, 220, 220, 220, 202}, 55, 2},
	{ "XXXXXXXXXXXXX", 0xFF, 0xFFFF, 0xFFFF, {0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF}, 0, 0 }
};

const char kSkillArray[37][20] = {
	"Flying",
	"Swimming",
	"Electrical",
	"Mechanical",
	"Hacking",
	"Bluffing",
	"Boatman",
	"Pilot",
	"Bureaucracy",
	"Find Trap",
	"Parachuting",
	"Pick Lock",
	"Explosives",
	"Chemistry",
	"Steal",
	"Dueling",
	"Marksmanship",
	"Fist Fighting",
	"Martial Arts",
	"Acrobatics",
	"Melee Weapon",
	"Pistol Combat",
	"Rifle Combat",
	"Automatic/SMG",
	"Archery",
	"Rocket Lncher",
	"Strength",
	"Intelligence",
	"Piety",
	"Agility",
	"Stamina",
	"Stealth",
	"Evasion",
	"Comprehension",
	"Perception",
	"Psychic Force",
	"Alignment"
};

const uint8 kByte2C7D0[60] = {
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 2, 0, 2, 2, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 1, 0, 1, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};

const char kPossessive[3][4] = { "his", "her", "its"};
const char kPersonal[3][4] = {"him", "her", "it"};

const char kAttackVerbs[51][20] = {
	"hits",
	"strikes",
	"hits",
	"slashes",
	"hacks",
	"slashes",
	"stabs",
	"sticks",
	"pokes",
	"pounds",
	"bashes",
	"hammers",
	"blasts",
	"blasts",
	"roasts",
	"blasts",
	"chills",
	"zaps",
	"zaps",
	"zaps",
	"zaps",
	"shoots",
	"hits",
	"strikes",
	"zaps",
	"zaps",
	"zaps",
	"blasts",
	"blasts",
	"blasts",
	"blasts",
	"blasts",
	"blasts",
	"blasts",
	"blasts",
	"blasts",
	"blasts",
	"shoots",
	"shoots",
	"blasts",
	"shoots",
	"shoots",
	"blasts",
	"shoots",
	"shoots",
	"gases",
	"sprays",
	"fumigates",
	"shoots",
	"shoots",
	"shoots"
};
} // End of namespace Efh
