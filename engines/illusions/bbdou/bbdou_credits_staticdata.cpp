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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "illusions/bbdou/bbdou_credits.h"

namespace Illusions {

const char *kCreditsText[] = {
	"@center",
	"@normal",
	"Directed by",
	"@bold",
	"Darren Bartlett",
	"@normal",
	"",
	"Produced by",
	"@bold",
	"James C\xF6liz, Jr.",
	"@normal",
	"",
	"Developed by",
	"@bold",
	"The Illusions Gaming Company",
	"@normal",
	"",
	"@split",
	"Creative Director",
	"Darren Bartlett",
	"Designer",
	"Ryan Modjeski",
	"Associate Designer",
	"David Sirlin",
	"",
	"",
	"Technical Director",
	"James C\xF6liz, Jr.",
	"Lead Programmer",
	"Bill Fowler",
	"Programmer",
	"Chuck Woo",
	"",
	"",
	"3D Artist",
	"Eric Chyn",
	"",
	"Bill Eral",
	"Production Artist",
	"Jim Eral",
	"Asst. Production Artist",
	"Eli Remus",
	"@center",
	"",
	"2D Animation by",
	"@bold",
	"LA West Productions",
	"@normal",
	"",
	"@split",
	"Director of Animation",
	"Ivan Tomicic",
	"Production Manager",
	"Susan McGirr",
	"Studio Supervisor",
	"Danijel Tomicic",
	"",
	"",
	"Lead Animator",
	"Dario Pustaj",
	"",
	"Ivica Horvat",
	"Animator",
	"Kristijan Dulic",
	"",
	"Elvis Popovic",
	"In-Between",
	"Maja Surijak",
	"",
	"Zlatko Zlatunic",
	"",
	"",
	"Lead Ink & Paint",
	"Sasa Zec",
	"Ink & Paint",
	"Darko Dukaric",
	"",
	"Marcela Kumparic",
	"",
	"Vlado Lencur",
	"",
	"Jura Milinkovic",
	"",
	"Bernard Ojdanic",
	"",
	"Peggy Skrlec",
	"@center",
	"",
	"3D Backgrounds by",
	"@bold",
	"LA West Productions",
	"@normal",
	"",
	"@split",
	"3D Artist",
	"Daniela Tomicic",
	"",
	"Diana-Barbara Stepanic",
	"@center",
	"",
	"2D Animation by",
	"@bold",
	"Six Foot Two Productions",
	"@normal",
	"",
	"@split",
	"Director of Animation",
	"Tom Arndt",
	"Producer",
	"Suzanne D. Atherly",
	"",
	"",
	"Character Animator",
	"Robbin Atherly",
	"",
	"Alan Lau",
	"",
	"David Ball",
	"",
	"Jeff Nevins",
	"",
	"",
	"Ink & Paint",
	"Steve Bellin",
	"",
	"Corrine Wong",
	"",
	"Jeff Nevins",
	"@center",
	"",
	"Written by",
	"@bold",
	"Bo Weinberg",
	"@normal",
	"",
	"Principal Voice by",
	"@bold",
	"Mike Judge",
	"@normal",
	"",
	"Secondary Voice Recorded at",
	"@bold",
	"Private Island Trax",
	"@normal",
	"",
	"Secondary Voices by",
	"Dean Julian",
	"Mia Altieri",
	"Nicole Schallig",
	"Rick Calvert",
	"John Campana",
	"Alex Mebane",
	"Denise Askew",
	"Michael Jamal",
	"",
	"Studio Engineered by",
	"Mark V",
	"",
	"Sound and Music by",
	"@bold",
	"Tommy Tallarico Studios",
	"@normal",
	"",
	"@split",
	"Sound Designer",
	"Joey Kuras",
	"Foley",
	"Scott Barrett",
	"@center",
	"",
	"Illusions is represented by",
	"@bold",
	"Interactive Studio Management",
	"@normal",
	"",
	"Published by",
	"@bold",
	"GT Interactive Software",
	"@normal",
	"",
	"@split",
	"Producer",
	"Nathan Rose",
	"Assistant Producer",
	"Jamal Jennings",
	"Group Product Manager",
	"Evan Stein",
	"Product Manager",
	"Robert J. Ricci",
	"Senior Communications Manager",
	"Alan Lewis",
	"Director, Product Development Services",
	"Mary Steer",
	"Director, Creative Services",
	"Leslie Mills",
	"Creative Director",
	"Vic Merritt",
	"Art/Traffic Manager",
	"Liz Fierro",
	"Manual Editor",
	"Peter Witcher",
	"",
	"",
	"@center",
	"",
	"Licensed by",
	"@bold",
	"MTV Networks",
	"@normal",
	"",
	"@split",
	"MTV Executive Producer",
	"Allie Eberhardt",
	"MTV Producer",
	"Tony Calandra",
	"MTV Creative Consultants",
	"Kristofor Brown",
	"",
	"David Felton",
	"",
	"Mike Judge",
	"",
	"Nick Litwinko",
	"MTV Standards and Practices",
	"Dr. Thomas Shea",
	"MTV Legal Affairs",
	"Beth Matthews",
	"@center",
	"",
	"MTV would like to thank",
	"Mary Frances Budig",
	"George Eichen",
	"Matt Farber",
	"Rick Holzman",
	"Jessica Jarrett",
	"Mike Judge",
	"Judith McGrath",
	"David Milch",
	"Abby Terkuhle",
	"Van Toffler",
	"Paige Wolfson",
	"Marcia Zellers",
	"",
	"@bold",
	"Special Thanks",
	"@normal",
	"Clyde Grossman",
	"Hiromi Nobata",
	"John Durentas",
	"Jeff Teachworth",
	"John Lawrence",
	"Bill Hendrickson",
	"Fred Schiller",
	"Sam Fletcher",
	"Elizabeth, Stephanie & Hannah",
	"Sheila Mendoza",
	"Yukari Yamano",
	"Hang Yim, King Yip & Wayne",
	"Li-Ming, Der-Lin & Fansy",
	"Bobbi Eral",
	"Miss Melissa",
	"Yasmin, Aparna & Jenny",
	"Tony the Cat",
	"Sammy the Cat",
	"@end"
};

const char *BbdouCredits::getText(uint index) {
	return kCreditsText[index - 1];
}

} // End of namespace Illusions
