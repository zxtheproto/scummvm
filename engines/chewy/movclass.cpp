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

#include "chewy/ngshext.h"
#include "chewy/movclass.h"
#include "chewy/defines.h"
#include "chewy/global.h"

namespace Chewy {

#define LEFT_VECT -1
#define RIGHT_VECT 1
#define UP_VECT -gpkt->Breite
#define DOWN_VECT gpkt->Breite
#define GEFUNDEN 1
#define UNBEGEHBAR 2
#define Y_DOWN 1
#define Y_UP 2
#define SOURCE_COL 14
#define DEST_COL 19
#define CHECK_COL 255
#define MIN_COL 8
#define UNBEGEHBAR_COL 3
#define CONNECT_COL 15
#define CUR_COL 13
#define S_OBEN 0
#define S_RECHTS 1
#define S_UNTEN 2
#define S_LINKS 3
#define MOV_X 1
#define MOV_Y 2

movclass::movclass() {
	vec_tbl[0] = -40;
	vec_tbl[1] = 1;
	vec_tbl[2] = 40;
	vec_tbl[3] = -1;
}

movclass::~movclass() {
}

void movclass::goto_xy(GotoPkt *gp) {
	int16 start_feld;
	int16 ziel_feld;
	//int16 anz;
	int16 tmp;
	gpkt = gp;
	agv.AutoGo = false;
	agv.Continue = false;
	vec_tbl[0] = -gpkt->Breite;
	vec_tbl[2] = gpkt->Breite;
	plot_delay = 20;
	calc_xy();
	plot_delay = 0;
	start_feld = get_feld_nr(gpkt->Sx, gpkt->Sy);
	ziel_feld = get_feld_nr(gpkt->Dx, gpkt->Dy);
	tmp = ziel_feld;
	/*anz = */calc_go(start_feld, &ziel_feld);

	if (tmp != ziel_feld) {
		get_mov_line();
		if (gml.MLineFeld != -1) {
			calc_mov_line_xit(gml.MLineFeld);
			if (mle.FNr != -1) {
				agv.AutoGo = true;
				agv.Start = 0;
				agv.LastFeld = -1;
				agv.AkKnoten = 0;
				start_feld = get_feld_nr(gpkt->Sx, gpkt->Sy);
				ziel_feld = gml.MLineFeld;
				calc_go(start_feld, &ziel_feld);
				if (gml.MLineFeld != ziel_feld) {
					agv.PktAnz = 2;
				} else {
					agv.PktAnz = 1;
				}
			}
		}
	}
}

int16 movclass::calc_auto_go(int16 x, int16 y, int16 *auto_x, int16 *auto_y) {
	byte *speicher;
	int16 i;
	int16 ok;
	int16 ret;
	ret = -1;

	if (agv.AutoGo == true) {
		speicher = gpkt->Mem;
		speicher += (gpkt->Breite * gpkt->Hoehe) * gpkt->AkMovEbene;
		if (!agv.Start) {
			agv.Start = agv.PktAnz;
			if (agv.PktAnz == 1) {
				agv.Start = 3;
				get_feld_xy(gml.MLineFeld, &agv.X_End, &agv.Y_End);
				agv.AkFeld = gml.MLineFeld;
			} else {
				get_feld_xy(gml.GotoFeld, &agv.X_End, &agv.Y_End);
				agv.AkFeld = gml.GotoFeld;
			}
			*auto_x = agv.X_End + 4;
			*auto_y = agv.Y_End + 4;
			ret = true;
		} else {
			if (get_feld_nr(x, y) == agv.AkFeld) {
				if (agv.Start == 2) {
					agv.Start = 3;
					get_feld_xy(gml.GotoFeld, &agv.X_End, &agv.Y_End);
					*auto_x = agv.X_End + 4;
					*auto_y = agv.Y_End + 4;
					ret = true;
				} else if (agv.Start == 3) {
					if (agv.LastFeld == -1) {
						agv.LastFeld = gml.MLineFeld;
						agv.AkFeld = gml.MLineFeld + mle.Direction;
						if (speicher[agv.AkFeld] == MOV_LINE_KNOTEN) {
							feld1knoten = true;
						} else
							feld1knoten = false;
						get_feld_xy(agv.AkFeld, &agv.X_End, &agv.Y_End);
						*auto_x = agv.X_End + 4;
						*auto_y = agv.Y_End + 4;
						ret = true;
					} else if (get_feld_nr(x, y) == agv.AkFeld) {
						if (agv.AkFeld == mle.FNr) {
							agv.AutoGo = false;
							*auto_x = gpkt->Dx;
							*auto_y = gpkt->Dy;
							ret = true;
						} else {
							ok = 0;
							if (feld1knoten) {
								feld1knoten = false;
								agv.LastFeld = agv.AkFeld;
								agv.AkFeld = mle.KnPkt[agv.AkKnoten];
								++agv.AkKnoten;
								if (agv.AkFeld != -1)
									ok = 1;
							} else {
								for (i = 0; i < 4 && !ok; i++) {
									if (speicher[agv.AkFeld + vec_tbl[i]] == MOV_LINE_IDX) {
										if (agv.AkFeld + vec_tbl[i] != agv.LastFeld) {
											agv.LastFeld = agv.AkFeld;
											agv.AkFeld += vec_tbl[i];
											ok = 1;
										}
									} else if (speicher[agv.AkFeld + vec_tbl[i]] == MOV_LINE_KNOTEN) {
										if (agv.AkFeld + vec_tbl[i] != agv.LastFeld) {
											agv.LastFeld = agv.AkFeld + vec_tbl[i];
											agv.AkFeld = mle.KnPkt[agv.AkKnoten];
											++agv.AkKnoten;
											if (agv.AkFeld == -1)
												ok = 0;
											else
												ok = 1;
										}
									}
								}
							}
							if (ok) {
								get_feld_xy(agv.AkFeld, &agv.X_End, &agv.Y_End);
								*auto_x = agv.X_End + 4;
								*auto_y = agv.Y_End + 4;
							} else {
								agv.AutoGo = false;
								*auto_x = gpkt->Dx;
								*auto_y = gpkt->Dy;
							}
							ret = true;
						}
					}
				}
			}
		}
	}

	return ret;
}

void movclass::stop_auto_go() {
	agv.AutoGo = false;
	agv.Continue = true;
}

void movclass::continue_auto_go() {
	agv.AutoGo = agv.Continue;
}

bool movclass::auto_go_status() {
	return agv.AutoGo;
}

void movclass::calc_xy() {
	int16 ende;
	int16 i;
	int16 seite;
	int16 count;
	int16 anz;
	int16 x, y;
	int16 min_x, min_y;
	int16 min_steps;
	int16 aksteps;
	int16 xvector = 0;
	int16 yvector = 0;
	int16 tmp_feld;

	if (!ged->ged_idx(gpkt->Dx, gpkt->Dy, gpkt->Breite, gpkt->Mem)) {
		ende = 0;
		count = 0;
		min_x = -1;
		min_y = -1;

		while (!ende) {
			min_steps = 30000;
			x = gpkt->Dx - (count + 1) * 8;
			y = gpkt->Dy - (count + 1) * 8;

			for (seite = 0; seite < 4; seite++) {
				anz = 2 + (count * 2);

				switch (seite) {
				case S_OBEN:
					xvector = 8;
					yvector = 0;
					break;

				case S_RECHTS:
					xvector = 0;
					yvector = 8;
					break;

				case S_UNTEN:
					xvector = -8;
					yvector = 0;
					break;

				case S_LINKS:
					xvector = 0;
					yvector = -8;
					break;

				default:
					break;
				}

				for (i = 0; i < anz; i++) {
					if (x >= 0 && x < gpkt->Breite * 8 &&
					        y >= 0 && y < gpkt->Hoehe * 8) {
						if (ged->ged_idx(x, y, gpkt->Breite, gpkt->Mem)) {
							aksteps = abs(gpkt->Dx - x);
							aksteps += abs(gpkt->Dy - y);
							if (aksteps < min_steps) {
								min_steps = aksteps;
								min_x = x;
								min_y = y;
							}
						}
					}
					x += xvector;
					y += yvector;
				}
			}

			++count;
			if (min_steps != 30000) {
				ende = 1;
				tmp_feld = get_feld_nr(min_x, min_y);
				get_feld_xy(tmp_feld, &gpkt->Dx, &gpkt->Dy);
				gpkt->Dx += 4;
				gpkt->Dy += 4;
			}
		}
	}
}

short movclass::calc_go(int16 src_feld, int16 *dst_feld) {
	int16 tmpx;
	int16 tmpy;
	int16 tmpz;

	int16 ende;
	int16 mov_ok;
	int16 steps;
	int16 abbruch;
	int16 new_vector = true;
	ObjMov om;
	MovInfo mi;

	mi.Vorschub = gpkt->Vorschub;
	get_feld_xy(src_feld, &om.Xypos[0], &om.Xypos[1]);
	get_feld_xy(*dst_feld, &mi.XyzEnd[0], &mi.XyzEnd[1]);
	mi.XyzStart[0] = om.Xypos[0];
	mi.XyzStart[1] = om.Xypos[1];
	get_mov_vector(mi.XyzStart, mi.Vorschub, &om);
	ende = 0;
	mov_ok = 0;
	steps = 0;
	abbruch = 0;

	while (!ende && !abbruch) {
		if (om.Count > 0) {
			--om.Count;
			tmpx = om.Xyvo[0];
			tmpy = om.Xyvo[1];
			tmpz = om.Xyvo[2];
			om.Xyna[0][0] += om.Xyna[0][1];
			if (om.Xyna[0][1] < 0) {
				if (om.Xyna[0][0] < -1000) {
					om.Xyna[0][0] += 1000;
					--tmpx;
				}
			} else if (om.Xyna[0][0] > 1000) {
				om.Xyna[0][0] -= 1000;
				++tmpx;
			}
			om.Xyna[1][0] += om.Xyna[1][1];
			if (om.Xyna[1][1] < 0) {
				if (om.Xyna[1][0] < -1000) {
					om.Xyna[1][0] += 1000;
					--tmpy;
				}
			} else if (om.Xyna[1][0] > 1000) {
				om.Xyna[1][0] -= 1000;
				++tmpy;
			}
			om.Xyna[2][0] += om.Xyna[2][1];
			if (om.Xyna[2][1] < 0) {
				if (om.Xyna[2][0] < -1000) {
					om.Xyna[2][0] += 1000;
					--tmpz;
				}
			} else if (om.Xyna[2][0] > 1000) {
				om.Xyna[2][0] -= 1000;
				++tmpz;
			}

			tmpz = 0;
			if (!ged->ged_idx(om.Xypos[0] + tmpx + tmpz,
			                  om.Xypos[1] + tmpy + tmpz,
			                  gpkt->Breite, gpkt->Mem)) {

				if (!ged->ged_idx(om.Xypos[0] + tmpx + tmpz,
				                  om.Xypos[1] + tmpz,
				                  gpkt->Breite, gpkt->Mem)) {

					if (!ged->ged_idx(om.Xypos[0] + tmpz,
					                  om.Xypos[1] + tmpy + tmpz,
					                  gpkt->Breite, gpkt->Mem)) {

						abbruch = UNBEGEHBAR;
					} else {
						if (!tmpy) {
							abbruch = UNBEGEHBAR;
						} else if (abs(om.Xypos[1] - mi.XyzEnd[1]) <= abs(tmpy)) {
							abbruch = GEFUNDEN;
						} else {
							mov_ok = MOV_Y;
						}
					}
				} else {
					if (!tmpx) {
						abbruch = UNBEGEHBAR;
					} else  if (abs(om.Xypos[0] - mi.XyzEnd[0]) <= abs(tmpx)) {
							abbruch = GEFUNDEN;
					} else {
						mov_ok = MOV_X;
					}
				}
			} else {
				++steps;
				om.Xypos[0] += tmpx;
				om.Xypos[1] += tmpy;
				om.Xypos[2] += tmpz;
				if (new_vector) {
					new_vector = false;
					mi.XyzStart[0] = om.Xypos[0];
					mi.XyzStart[1] = om.Xypos[1];
					get_mov_vector(mi.XyzStart, mi.Vorschub, &om);
				}
				if (om.Count == 0) {

					abbruch = GEFUNDEN;
				}
			}

			if (mov_ok) {
				++steps;
				if (mov_ok == MOV_X)
					om.Xypos[0] += tmpx;
				else
					om.Xypos[1] += tmpy;
				om.Xypos[2] += tmpz;
				mi.XyzStart[0] = om.Xypos[0];
				mi.XyzStart[1] = om.Xypos[1];
				get_mov_vector(mi.XyzStart, mi.Vorschub, &om);
				if (mov_ok == MOV_X) {
					if (om.Xyvo[0] != 0)
						new_vector = true;
				} else {
					if (om.Xyvo[1] != 0)
						new_vector = true;
				}
				if (om.Count == 0) {

					abbruch = GEFUNDEN;
				}
				mov_ok = false;
			}
		} else
			ende = 1;
	}
	if (abbruch == UNBEGEHBAR)
		*dst_feld = get_feld_nr(om.Xypos[0], om.Xypos[1]);

	return steps;
}

void movclass::get_mov_line() {
	int16 ende;
	int16 start_feld;
	int16 tmp_feld;
	int16 ak_steps;
	int16 min_steps;
	int16 vector;
	int16 abbruch;
	int16 count_vect;
	int16 count;
	int16 y_richtung;
	byte *speicher;
	gml.GotoFeld = -1;
	gml.MLineFeld = -1;
	if (gpkt->Ebenen > 1) {
		speicher = gpkt->Mem;

		speicher += (gpkt->Breite * gpkt->Hoehe) * gpkt->AkMovEbene;

		start_feld = get_feld_nr(gpkt->Sx, gpkt->Sy);
		ende = 0;
		count = 0;
		min_steps = 30000;
		count_vect = DOWN_VECT;
		y_richtung = Y_DOWN;
		while (!ende) {

			tmp_feld = start_feld + count * count_vect;
			if (ged->ged_idx(tmp_feld, gpkt->Breite, gpkt->Mem)) {
				abbruch = 0;
				vector = 0;
				while ((tmp_feld % gpkt->Breite) < (gpkt->Breite - 1) && !abbruch)
				{
					if (ged->ged_idx(tmp_feld + vector, gpkt->Breite, gpkt->Mem)) {
						tmp_feld += vector;
						if (speicher[tmp_feld] == MOV_LINE_IDX) {
							ak_steps = abs((tmp_feld % gpkt->Breite) - (start_feld % gpkt->Breite));
							ak_steps += abs((tmp_feld / gpkt->Breite) - (start_feld / gpkt->Breite));
							if (ak_steps < min_steps) {
								min_steps = ak_steps;
								gml.GotoFeld = start_feld + count * count_vect;
								gml.MLineFeld = tmp_feld;
							}
						}
						vector = RIGHT_VECT;
					} else {
						abbruch = UNBEGEHBAR;
					}
				}

				tmp_feld = start_feld + count * count_vect;
				vector = LEFT_VECT;
				abbruch = 0;
				while ((tmp_feld % gpkt->Breite) > 0 && !abbruch) {
					if (ged->ged_idx(tmp_feld + vector, gpkt->Breite, gpkt->Mem)) {
						tmp_feld += vector;
						if (speicher[tmp_feld] == MOV_LINE_IDX) {
							ak_steps = abs((tmp_feld % gpkt->Breite) - (start_feld % gpkt->Breite));
							ak_steps += abs((tmp_feld / gpkt->Breite) - (start_feld / gpkt->Breite));
							if (ak_steps < min_steps) {
								min_steps = ak_steps;
								gml.GotoFeld = start_feld + count * count_vect;
								gml.MLineFeld = tmp_feld;
							}
						}
					} else {
						abbruch = UNBEGEHBAR;
					}
				}
				++count;
			} else {
				if (y_richtung == Y_DOWN) {

					y_richtung = Y_UP;
					count = 1;
					count_vect = UP_VECT;
				} else
					ende = 1;
			}
		}
	}
}

void movclass::calc_mov_line_xit(int16 start_feld) {
	int16 calc_feld;
	int16 last_feld;
	int16 ziel_feld;
	int16 tmp_feld;
	int16 i;
	int16 found;
	int16 steps;
	int16 dest_steps;

	int16 ok;
	int16 k;
	//int16 found_min;
	int16 TmpKnPkt[MAX_KNOTEN_PKT];
	int16 min_step_unerreicht;
	int16 dir_unerreicht = 0;
	int16 KnPkt_unrreicht[MAX_KNOTEN_PKT];
	int16 feld_unerreicht = 0;
	int16 knoten_felder[MAX_KNOTEN_PKT][6];

	int16 ak_knoten;
	int16 knoten_flag;
	int16 tbl_dir;
	int16 tbl_ptr;
	int16 dir;
	byte *speicher;
	for (i = 0; i < MAX_KNOTEN_PKT; i++)
		TmpKnPkt[i] = -1;
	if (gpkt->Ebenen > 1) {
		memset((char *)knoten_felder, -1, MAX_KNOTEN_PKT * 6);
		speicher = gpkt->Mem;
		speicher += (gpkt->Breite * gpkt->Hoehe) * gpkt->AkMovEbene;
		mle.Steps = 30000;
		min_step_unerreicht = 30000;
		mle.FNr = -1;
		ziel_feld = get_feld_nr(gpkt->Dx, gpkt->Dy);
		calc_feld = start_feld;
		last_feld = start_feld;
		steps = 0;
		found = 0;
		ak_knoten = -1;
		tbl_dir = 1;
		tbl_ptr = 0;
		knoten_flag = 0;

		//found_min = 0;
		dir = 30000;
		while (!found) {
			tmp_feld = ziel_feld;
			calc_go(calc_feld, &tmp_feld);
			if (tmp_feld == ziel_feld) {
				dest_steps = abs((ziel_feld % gpkt->Breite) - (calc_feld % gpkt->Breite));
				dest_steps += abs((ziel_feld / gpkt->Breite) - (calc_feld / gpkt->Breite));
				if (dest_steps < mle.Steps) {
					mle.Steps = dest_steps;
					mle.FNr = calc_feld;
					if (dir == 30000)
						mle.Direction = 0;
					else
						mle.Direction = dir;
					for (i = 0; i < MAX_KNOTEN_PKT; i++)
						mle.KnPkt[i] = TmpKnPkt[i];
				}
			} else {
				dest_steps = abs((ziel_feld % gpkt->Breite) - (tmp_feld % gpkt->Breite));
				dest_steps += abs((ziel_feld / gpkt->Breite) - (tmp_feld / gpkt->Breite));
				if (dest_steps < min_step_unerreicht) {
					min_step_unerreicht = dest_steps;
					feld_unerreicht = tmp_feld;
					if (dir == 30000)
						dir_unerreicht = 0;
					else
						dir_unerreicht = dir;
					for (i = 0; i < MAX_KNOTEN_PKT; i++)
						KnPkt_unrreicht[i] = TmpKnPkt[i];
				}
			}
			ok = 0;
			for (i = 0; i < 4 && !ok; i++) {
				if (speicher[calc_feld + vec_tbl[tbl_ptr + i * tbl_dir]] == MOV_LINE_IDX)
				{
					if (calc_feld + vec_tbl[tbl_ptr + i * tbl_dir] != last_feld)
					{
						last_feld = calc_feld;
						calc_feld += vec_tbl[tbl_ptr + i * tbl_dir];
						++steps;
						ok = 1;
						if (dir == 30000) {
							dir = vec_tbl[tbl_ptr + i * tbl_dir];
						}
						if (knoten_flag) {
							TmpKnPkt[ak_knoten] = calc_feld;
							knoten_felder[ak_knoten][tbl_ptr + i * tbl_dir] = calc_feld;
							knoten_flag = false;
						}
					}
				} else if (speicher[calc_feld + vec_tbl[tbl_ptr + i * tbl_dir]] == MOV_LINE_KNOTEN) {
					if (calc_feld + vec_tbl[tbl_ptr + i * tbl_dir] != last_feld) {
						if (dir == 30000) {
							dir = vec_tbl[tbl_ptr + i * tbl_dir];
						}
						++ak_knoten;
						for (k = 0; k < 6; k++)
							knoten_felder[ak_knoten][k] = -1;
						switch (tbl_ptr + i * tbl_dir) {
						case MLE_UP:
							k = MLE_DOWN;
							break;
						case MLE_RIGHT:
							k = MLE_LEFT;
							break;
						case MLE_LEFT:
							k = MLE_RIGHT;
							break;
						case MLE_DOWN:
							k = MLE_UP;
							break;
						}
						knoten_felder[ak_knoten][k] = calc_feld;
						last_feld = calc_feld;
						calc_feld += vec_tbl[tbl_ptr + i * tbl_dir];
						knoten_felder[ak_knoten][4] = calc_feld;
						++steps;
						knoten_felder[ak_knoten][5] = steps;
						knoten_flag = true;
						ok = 1;
					}
				}
			}
			if (!ok) {

				if (ak_knoten != -1)
				{
					ok = 0;
					for (i = 0; i < 4 && !ok; i++) {
						if (knoten_felder[ak_knoten][tbl_ptr + i * tbl_dir] == -1) {
							tmp_feld = knoten_felder[ak_knoten][4];
							if (speicher[tmp_feld + vec_tbl[tbl_ptr + i * tbl_dir]] == MOV_LINE_IDX)
							{
								last_feld = knoten_felder[ak_knoten][4];
								calc_feld = tmp_feld + vec_tbl[tbl_ptr + i * tbl_dir];

								TmpKnPkt[ak_knoten] = calc_feld;
								knoten_felder[ak_knoten][tbl_ptr + i * tbl_dir] = calc_feld;
								steps = knoten_felder[ak_knoten][5];
								ok = 1;
							}
						}
					}
					if (!ok) {
						--ak_knoten;
					}
				} else if (tbl_dir == 1) {
					tbl_dir = -1;
					tbl_ptr = 3;
					dir = 30000;
					//found_min = 0;
					calc_feld = start_feld;
					last_feld = start_feld;
				} else {
					found = 1;
					if (mle.FNr == -1) {
						mle.Steps = min_step_unerreicht;
						mle.FNr = feld_unerreicht;
						mle.Direction = dir_unerreicht;
						for (i = 0; i < MAX_KNOTEN_PKT; i++)
							mle.KnPkt[i] = KnPkt_unrreicht[i];

						get_feld_xy(feld_unerreicht, &gpkt->Dx, &gpkt->Dy);
						gpkt->Dx += 4;
						gpkt->Dy += 4;
					}
				}
			}
		}
	}
}

int16 movclass::get_feld_nr(int16 x, int16 y) {
	x >>= 3;
	y >>= 3;

	return x + (y * gpkt->Breite);
}

void movclass::get_feld_xy(int16 fnr, int16 *x, int16 *y) {
	*x = (fnr % gpkt->Breite);
	*y = (fnr / gpkt->Breite);
	*x <<= 3;
	*y <<= 3;
}

void movclass::get_mov_vector(int16 *xyz, int16 vorschub, ObjMov *om) {
	uint8 xvector;
	uint8 yvector;
	uint8 zvector;
	float xstep;
	float ystep;
	float zstep;
	int16 tmp;
	int16 absx, absy, absz;
	int16 x, y, z, x1, y1, z1;

	if (vorschub > 0) {
		x = xyz[0];
		y = xyz[1];
		z = xyz[2];
		x1 = xyz[3];
		y1 = xyz[4];
		z1 = xyz[5];
		om->Xypos[0] = x;
		om->Xypos[1] = y;
		om->Xypos[2] = z;
		x = x - x1;
		y = y - y1;
		z = z - z1;

		if (x < 0) {
			xvector = 1;
			--x;
		} else {
			xvector = 0;
			++x;
		}
		if (y < 0) {
			yvector = 1;
			--y;
		} else {
			yvector = 0;
			++y;
		}
		if (z < 0) {
			zvector = 1;
			--z;
		} else {
			zvector = 0;
			++z;
		}

		absx = abs(x);
		absy = abs(y);
		absz = abs(z);
		if (absx < absy) {
			xstep = (float)absx / ((float)absy / (float)vorschub);
			ystep = vorschub;
			om->Count = (int16)((float) y / (float)ystep);
		} else {
			xstep = vorschub;
			ystep = (float)absy / ((float)absx / (float)vorschub);
			om->Count = (int16)((float) x / (float)xstep);
		}
		om->Count = abs(om->Count);
		if (!om->Count) {
			zstep = (float)absz / 1.0;
		} else
			zstep = (float)absz / ((float)((abs)(om->Count)));

		if (!xvector)
			xstep = -xstep;
		if (!yvector)
			ystep = -ystep;
		if (!zvector)
			zstep = -zstep;

		om->Xyvo[0] = (int16)xstep;
		om->Xyvo[1] = (int16)ystep;
		om->Xyvo[2] = (int16)zstep;
		tmp = (int16)((float)xstep * 1000.0);
		om->Xyna[0][1] = tmp - (om->Xyvo[0] * 1000);
		om->Xyna[0][0] = 0;
		tmp = (int16)((float)ystep * 1000.0);
		om->Xyna[1][1] = tmp - (om->Xyvo[1] * 1000);
		om->Xyna[1][0] = 0;
		tmp = (int16)((float)zstep * 1000.0);
		om->Xyna[2][1] = tmp - (om->Xyvo[2] * 1000);
		om->Xyna[2][0] = 0;
		if (!om->Count) {
			xyz[0] = xyz[3];
			xyz[1] = xyz[4];
			om->Xypos[0] = xyz[3];
			om->Xypos[1] = xyz[4];
		}
	} else {
		om->Count = 0;

		om->Xypos[0] = xyz[0];
		om->Xypos[1] = xyz[1];
		om->Xypos[2] = xyz[2];
		om->Xyvo[0] = 0;
		om->Xyvo[1] = 0;
		om->Xyvo[2] = 0;
		om->Xyna[0][1] = 0;
		om->Xyna[0][0] = 0;
		om->Xyna[1][1] = 0;
		om->Xyna[1][0] = 0;
		om->Xyna[2][1] = 0;
		om->Xyna[2][0] = 0;
	}
}

} // namespace Chewy
