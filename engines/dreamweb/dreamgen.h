#ifndef TASMRECOVER_DREAMGEN_STUBS_H__
#define TASMRECOVER_DREAMGEN_STUBS_H__

/* PLEASE DO NOT MODIFY THIS FILE. ALL CHANGES WILL BE LOST! LOOK FOR README FOR DETAILS */

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

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 *
 */

#include "dreamweb/runtime.h"

namespace DreamGen {

#include "structs.h"

class DreamGenContext : public Context {
public:
	void __start();
#include "stubs.h" // Allow hand-reversed functions to have a signature different than void f()

	static const uint16 offset_quitlist = 0x0a84;
	static const uint16 offset_savelist = 0x0f44;
	static const uint16 offset_mainlist = 0x1402;
	static const uint16 offset_gameerror8 = 0x113f;
	static const uint16 offset_gameerror5 = 0x1074;
	static const uint16 offset_error2patch = 0x0ff6;
	static const uint16 offset_openchangesize = 0x0a1c;
	static const uint16 offset_keys = 0x0b14;
	static const uint16 offset_mainlist2 = 0x1440;
	static const uint16 offset_gameerror2 = 0x0fb2;
	static const uint16 offset_loadlist = 0x0ef0;
	static const uint16 offset_gameerror6 = 0x10be;
	static const uint16 offset_speechfile = 0x13f1;
	static const uint16 offset_atmospherelist = 0x147e;
	static const uint16 offset_gameerror4 = 0x1037;
	static const uint16 offset_gameerror1 = 0x0f6e;
	static const uint16 offset_examlist = 0x09be;
	static const uint16 offset_gameinfo = 0x1170;
	static const uint16 offset_opslist = 0x0ec6;
	static const uint16 offset_invlist1 = 0x09fc;
	static const uint16 offset_money2poke = 0x0d97;
	static const uint16 offset_talklist = 0x0a64;
	static const uint16 offset_menulist = 0x0e1e;
	static const uint16 offset_comlist = 0x0ad8;
	static const uint16 offset_withlist1 = 0x0a3a;
	static const uint16 offset_money1poke = 0x0d92;
	static const uint16 offset_gameerror7 = 0x1104;
	static const uint16 offset_discopslist = 0x0f1a;
	static const uint16 offset_commandline = 0x16d7;
	static const uint16 offset_destlist = 0x0a9a;
	static const uint16 offset_shaketable = 0x06af;
	static const uint16 offset_error6patch = 0x10fe;
	static const uint16 offset_keybuffer = 0x1718;
	static const uint16 offset_speechfilename = 0x13eb;
	static const uint16 offset_rootdir = 0x0b8c;
	static const uint16 offset_gameerror3 = 0x1003;
	static const uint16 offset_facelist = 0x0451;
	static const uint16 offset_diarylist = 0x0e9c;
	static const uint16 offset_decidelist = 0x13c1;
	static const uint16 offset_symbollist = 0x0e5e;
	static const uint16 offset_operand1 = 0x0b7e;
	static const uint16 kStartvars = 0;
	static const uint16 kProgresspoints = 1;
	static const uint16 kWatchon = 2;
	static const uint16 kShadeson = 3;
	static const uint16 kSecondcount = 4;
	static const uint16 kMinutecount = 5;
	static const uint16 kHourcount = 6;
	static const uint16 kZoomon = 7;
	static const uint16 kLocation = 8;
	static const uint16 kExpos = 9;
	static const uint16 kExframepos = 10;
	static const uint16 kExtextpos = 12;
	static const uint16 kCard1money = 14;
	static const uint16 kListpos = 16;
	static const uint16 kRyanpage = 18;
	static const uint16 kWatchingtime = 19;
	static const uint16 kReeltowatch = 21;
	static const uint16 kEndwatchreel = 23;
	static const uint16 kSpeedcount = 25;
	static const uint16 kWatchspeed = 26;
	static const uint16 kReeltohold = 27;
	static const uint16 kEndofholdreel = 29;
	static const uint16 kWatchmode = 31;
	static const uint16 kDestafterhold = 32;
	static const uint16 kNewsitem = 33;
	static const uint16 kLiftflag = 34;
	static const uint16 kLiftpath = 35;
	static const uint16 kLockstatus = 36;
	static const uint16 kDoorpath = 37;
	static const uint16 kCounttoopen = 38;
	static const uint16 kCounttoclose = 39;
	static const uint16 kRockstardead = 40;
	static const uint16 kGeneraldead = 41;
	static const uint16 kSartaindead = 42;
	static const uint16 kAidedead = 43;
	static const uint16 kBeenmugged = 44;
	static const uint16 kGunpassflag = 45;
	static const uint16 kCanmovealtar = 46;
	static const uint16 kTalkedtoattendant = 47;
	static const uint16 kTalkedtosparky = 48;
	static const uint16 kTalkedtoboss = 49;
	static const uint16 kTalkedtorecep = 50;
	static const uint16 kCardpassflag = 51;
	static const uint16 kMadmanflag = 52;
	static const uint16 kKeeperflag = 53;
	static const uint16 kLasttrigger = 54;
	static const uint16 kMandead = 55;
	static const uint16 kSeed = 56;
	static const uint16 kNeedtotravel = 59;
	static const uint16 kThroughdoor = 60;
	static const uint16 kNewobs = 61;
	static const uint16 kRyanon = 62;
	static const uint16 kCombatcount = 63;
	static const uint16 kLastweapon = 64;
	static const uint16 kDreamnumber = 65;
	static const uint16 kRoomafterdream = 66;
	static const uint16 kShakecounter = 67;
	static const uint16 kSpeechcount = 68;
	static const uint16 kCharshift = 69;
	static const uint16 kKerning = 71;
	static const uint16 kBrightness = 72;
	static const uint16 kRoomloaded = 73;
	static const uint16 kDidzoom = 74;
	static const uint16 kLinespacing = 75;
	static const uint16 kTextaddressx = 77;
	static const uint16 kTextaddressy = 79;
	static const uint16 kTextlen = 81;
	static const uint16 kLastxpos = 82;
	static const uint16 kIcontop = 84;
	static const uint16 kIconleft = 86;
	static const uint16 kItemframe = 88;
	static const uint16 kItemtotran = 89;
	static const uint16 kRoomad = 90;
	static const uint16 kOldsubject = 92;
	static const uint16 kWithobject = 94;
	static const uint16 kWithtype = 95;
	static const uint16 kLookcounter = 96;
	static const uint16 kCommand = 98;
	static const uint16 kCommandtype = 99;
	static const uint16 kOldcommandtype = 100;
	static const uint16 kObjecttype = 101;
	static const uint16 kGetback = 102;
	static const uint16 kInvopen = 103;
	static const uint16 kMainmode = 104;
	static const uint16 kPickup = 105;
	static const uint16 kLastinvpos = 106;
	static const uint16 kExamagain = 107;
	static const uint16 kNewtextline = 108;
	static const uint16 kOpenedob = 109;
	static const uint16 kOpenedtype = 110;
	static const uint16 kOldmapadx = 111;
	static const uint16 kOldmapady = 113;
	static const uint16 kMapadx = 115;
	static const uint16 kMapady = 117;
	static const uint16 kMapoffsetx = 119;
	static const uint16 kMapoffsety = 121;
	static const uint16 kMapxstart = 123;
	static const uint16 kMapystart = 125;
	static const uint16 kMapxsize = 127;
	static const uint16 kMapysize = 128;
	static const uint16 kHavedoneobs = 129;
	static const uint16 kManisoffscreen = 130;
	static const uint16 kRainspace = 131;
	static const uint16 kFacing = 132;
	static const uint16 kLeavedirection = 133;
	static const uint16 kTurntoface = 134;
	static const uint16 kTurndirection = 135;
	static const uint16 kMaintimer = 136;
	static const uint16 kIntrocount = 138;
	static const uint16 kArrowad = 139;
	static const uint16 kCurrentkey = 141;
	static const uint16 kOldkey = 142;
	static const uint16 kUseddirection = 143;
	static const uint16 kCurrentkey2 = 144;
	static const uint16 kTimercount = 145;
	static const uint16 kOldtimercount = 146;
	static const uint16 kMapx = 147;
	static const uint16 kMapy = 148;
	static const uint16 kNewscreen = 149;
	static const uint16 kRyanx = 150;
	static const uint16 kRyany = 151;
	static const uint16 kLastflag = 152;
	static const uint16 kLastflagex = 153;
	static const uint16 kFlagx = 154;
	static const uint16 kFlagy = 155;
	static const uint16 kCurrentex = 156;
	static const uint16 kCurrentfree = 157;
	static const uint16 kCurrentframe = 158;
	static const uint16 kFramesad = 160;
	static const uint16 kDataad = 162;
	static const uint16 kFrsegment = 164;
	static const uint16 kObjectx = 166;
	static const uint16 kObjecty = 168;
	static const uint16 kOffsetx = 170;
	static const uint16 kOffsety = 172;
	static const uint16 kSavesize = 174;
	static const uint16 kSavesource = 176;
	static const uint16 kSavex = 178;
	static const uint16 kSavey = 179;
	static const uint16 kCurrentob = 180;
	static const uint16 kPrioritydep = 181;
	static const uint16 kDestpos = 182;
	static const uint16 kReallocation = 183;
	static const uint16 kRoomnum = 184;
	static const uint16 kNowinnewroom = 185;
	static const uint16 kResetmanxy = 186;
	static const uint16 kNewlocation = 187;
	static const uint16 kAutolocation = 188;
	static const uint16 kMustload = 189;
	static const uint16 kAnswered = 190;
	static const uint16 kSaidno = 191;
	static const uint16 kDoorcheck1 = 192;
	static const uint16 kDoorcheck2 = 193;
	static const uint16 kDoorcheck3 = 194;
	static const uint16 kDoorcheck4 = 195;
	static const uint16 kMousex = 196;
	static const uint16 kMousey = 198;
	static const uint16 kMousebutton = 200;
	static const uint16 kMousebutton1 = 202;
	static const uint16 kMousebutton2 = 204;
	static const uint16 kMousebutton3 = 206;
	static const uint16 kMousebutton4 = 208;
	static const uint16 kOldbutton = 210;
	static const uint16 kOldx = 212;
	static const uint16 kOldy = 214;
	static const uint16 kLastbutton = 216;
	static const uint16 kOldpointerx = 218;
	static const uint16 kOldpointery = 220;
	static const uint16 kDelherex = 222;
	static const uint16 kDelherey = 224;
	static const uint16 kPointerxs = 226;
	static const uint16 kPointerys = 227;
	static const uint16 kDelxs = 228;
	static const uint16 kDelys = 229;
	static const uint16 kPointerframe = 230;
	static const uint16 kPointerpower = 231;
	static const uint16 kAuxpointerframe = 232;
	static const uint16 kPointermode = 233;
	static const uint16 kPointerspeed = 234;
	static const uint16 kPointercount = 235;
	static const uint16 kInmaparea = 236;
	static const uint16 kReelpointer = 237;
	static const uint16 kSlotdata = 239;
	static const uint16 kThisslot = 240;
	static const uint16 kSlotflags = 241;
	static const uint16 kTakeoff = 242;
	static const uint16 kTalkmode = 244;
	static const uint16 kTalkpos = 245;
	static const uint16 kCharacter = 246;
	static const uint16 kPersondata = 247;
	static const uint16 kTalknum = 249;
	static const uint16 kNumberinroom = 250;
	static const uint16 kCurrentcel = 251;
	static const uint16 kOldselection = 252;
	static const uint16 kStopwalking = 253;
	static const uint16 kMouseon = 254;
	static const uint16 kPlayed = 255;
	static const uint16 kTimer1 = 257;
	static const uint16 kTimer2 = 258;
	static const uint16 kTimer3 = 259;
	static const uint16 kWholetimer = 260;
	static const uint16 kTimer1to = 262;
	static const uint16 kTimer2to = 263;
	static const uint16 kTimer3to = 264;
	static const uint16 kWatchdump = 265;
	static const uint16 kCurrentset = 266;
	static const uint16 kLogonum = 268;
	static const uint16 kOldlogonum = 269;
	static const uint16 kNewlogonum = 270;
	static const uint16 kNetseg = 271;
	static const uint16 kNetpoint = 273;
	static const uint16 kKeynum = 275;
	static const uint16 kCursorstate = 276;
	static const uint16 kPressed = 277;
	static const uint16 kPresspointer = 278;
	static const uint16 kGraphicpress = 280;
	static const uint16 kPresscount = 281;
	static const uint16 kKeypadax = 282;
	static const uint16 kKeypadcx = 284;
	static const uint16 kLightcount = 286;
	static const uint16 kFolderpage = 287;
	static const uint16 kDiarypage = 288;
	static const uint16 kMenucount = 289;
	static const uint16 kSymboltopx = 290;
	static const uint16 kSymboltopnum = 291;
	static const uint16 kSymboltopdir = 292;
	static const uint16 kSymbolbotx = 293;
	static const uint16 kSymbolbotnum = 294;
	static const uint16 kSymbolbotdir = 295;
	static const uint16 kSymboltolight = 296;
	static const uint16 kSymbol1 = 297;
	static const uint16 kSymbol2 = 298;
	static const uint16 kSymbol3 = 299;
	static const uint16 kSymbolnum = 300;
	static const uint16 kDumpx = 301;
	static const uint16 kDumpy = 303;
	static const uint16 kWalkandexam = 305;
	static const uint16 kWalkexamtype = 306;
	static const uint16 kWalkexamnum = 307;
	static const uint16 kCursloc = 308;
	static const uint16 kCurslocx = 310;
	static const uint16 kCurslocy = 312;
	static const uint16 kCurpos = 314;
	static const uint16 kMonadx = 316;
	static const uint16 kMonady = 318;
	static const uint16 kGotfrom = 320;
	static const uint16 kMonsource = 322;
	static const uint16 kNumtodo = 324;
	static const uint16 kTimecount = 326;
	static const uint16 kCounttotimed = 328;
	static const uint16 kTimedseg = 330;
	static const uint16 kTimedoffset = 332;
	static const uint16 kTimedy = 334;
	static const uint16 kTimedx = 335;
	static const uint16 kNeedtodumptimed = 336;
	static const uint16 kHandle = 337;
	static const uint16 kLoadingorsave = 339;
	static const uint16 kCurrentslot = 340;
	static const uint16 kCursorpos = 341;
	static const uint16 kColourpos = 342;
	static const uint16 kFadedirection = 343;
	static const uint16 kNumtofade = 344;
	static const uint16 kFadecount = 345;
	static const uint16 kAddtogreen = 346;
	static const uint16 kAddtored = 347;
	static const uint16 kAddtoblue = 348;
	static const uint16 kLastsoundreel = 349;
	static const uint16 kSoundbuffer = 351;
	static const uint16 kSoundbufferad = 353;
	static const uint16 kSoundbufferpage = 355;
	static const uint16 kSoundtimes = 356;
	static const uint16 kNeedsoundbuff = 357;
	static const uint16 kOldint9seg = 358;
	static const uint16 kOldint9add = 360;
	static const uint16 kOldint8seg = 362;
	static const uint16 kOldint8add = 364;
	static const uint16 kOldsoundintseg = 366;
	static const uint16 kOldsoundintadd = 368;
	static const uint16 kSoundbaseadd = 370;
	static const uint16 kDsp_status = 372;
	static const uint16 kDsp_write = 374;
	static const uint16 kDmaaddress = 376;
	static const uint16 kSoundint = 377;
	static const uint16 kSounddmachannel = 378;
	static const uint16 kSampleplaying = 379;
	static const uint16 kTestresult = 380;
	static const uint16 kCurrentirq = 381;
	static const uint16 kSpeechloaded = 382;
	static const uint16 kSpeechlength = 383;
	static const uint16 kVolume = 385;
	static const uint16 kVolumeto = 386;
	static const uint16 kVolumedirection = 387;
	static const uint16 kVolumecount = 388;
	static const uint16 kPlayblock = 389;
	static const uint16 kWongame = 390;
	static const uint16 kLasthardkey = 391;
	static const uint16 kBufferin = 392;
	static const uint16 kBufferout = 394;
	static const uint16 kExtras = 396;
	static const uint16 kWorkspace = 398;
	static const uint16 kMapstore = 400;
	static const uint16 kCharset1 = 402;
	static const uint16 kTempcharset = 404;
	static const uint16 kIcons1 = 406;
	static const uint16 kIcons2 = 408;
	static const uint16 kBuffers = 410;
	static const uint16 kMainsprites = 412;
	static const uint16 kBackdrop = 414;
	static const uint16 kMapdata = 416;
	static const uint16 kSounddata = 418;
	static const uint16 kSounddata2 = 420;
	static const uint16 kRecordspace = 422;
	static const uint16 kFreedat = 424;
	static const uint16 kSetdat = 426;
	static const uint16 kReel1 = 428;
	static const uint16 kReel2 = 430;
	static const uint16 kReel3 = 432;
	static const uint16 kRoomdesc = 434;
	static const uint16 kFreedesc = 436;
	static const uint16 kSetdesc = 438;
	static const uint16 kBlockdesc = 440;
	static const uint16 kSetframes = 442;
	static const uint16 kFreeframes = 444;
	static const uint16 kPeople = 446;
	static const uint16 kReels = 448;
	static const uint16 kCommandtext = 450;
	static const uint16 kPuzzletext = 452;
	static const uint16 kTraveltext = 454;
	static const uint16 kTempgraphics = 456;
	static const uint16 kTempgraphics2 = 458;
	static const uint16 kTempgraphics3 = 460;
	static const uint16 kTempsprites = 462;
	static const uint16 kTextfile1 = 464;
	static const uint16 kTextfile2 = 466;
	static const uint16 kTextfile3 = 468;
	static const uint16 kBlinkframe = 470;
	static const uint16 kBlinkcount = 471;
	static const uint16 kReasseschanges = 472;
	static const uint16 kPointerspath = 473;
	static const uint16 kManspath = 474;
	static const uint16 kPointerfirstpath = 475;
	static const uint16 kFinaldest = 476;
	static const uint16 kDestination = 477;
	static const uint16 kLinestartx = 478;
	static const uint16 kLinestarty = 480;
	static const uint16 kLineendx = 482;
	static const uint16 kLineendy = 484;
	static const uint16 kIncrement1 = 486;
	static const uint16 kIncrement2 = 488;
	static const uint16 kLineroutine = 490;
	static const uint16 kLinepointer = 491;
	static const uint16 kLinedirection = 492;
	static const uint16 kLinelength = 493;
	static const uint16 kLiftsoundcount = 494;
	static const uint16 kEmmhandle = 495;
	static const uint16 kEmmpageframe = 497;
	static const uint16 kEmmhardwarepage = 499;
	static const uint16 kCh0emmpage = 500;
	static const uint16 kCh0offset = 502;
	static const uint16 kCh0blockstocopy = 504;
	static const uint16 kCh0playing = 506;
	static const uint16 kCh0repeat = 507;
	static const uint16 kCh0oldemmpage = 508;
	static const uint16 kCh0oldoffset = 510;
	static const uint16 kCh0oldblockstocopy = 512;
	static const uint16 kCh1playing = 514;
	static const uint16 kCh1emmpage = 515;
	static const uint16 kCh1offset = 517;
	static const uint16 kCh1blockstocopy = 519;
	static const uint16 kCh1blocksplayed = 521;
	static const uint16 kSoundbufferwrite = 523;
	static const uint16 kSoundemmpage = 525;
	static const uint16 kSpeechemmpage = 527;
	static const uint16 kCurrentsample = 529;
	static const uint16 kRoomssample = 530;
	static const uint16 kGameerror = 531;
	static const uint16 kHowmuchalloc = 532;
	static const uint16 kReelroutines = 534;
	static const uint16 kReelcalls = 991;
	static const uint16 kRoombyroom = 1214;
	static const uint16 kR0 = 1326;
	static const uint16 kR1 = 1327;
	static const uint16 kR2 = 1331;
	static const uint16 kR6 = 1350;
	static const uint16 kR8 = 1357;
	static const uint16 kR9 = 1373;
	static const uint16 kR10 = 1380;
	static const uint16 kR11 = 1384;
	static const uint16 kR12 = 1388;
	static const uint16 kR13 = 1392;
	static const uint16 kR14 = 1405;
	static const uint16 kR20 = 1439;
	static const uint16 kR22 = 1461;
	static const uint16 kR23 = 1492;
	static const uint16 kR25 = 1505;
	static const uint16 kR26 = 1527;
	static const uint16 kR27 = 1549;
	static const uint16 kR28 = 1574;
	static const uint16 kR29 = 1593;
	static const uint16 kR45 = 1609;
	static const uint16 kR46 = 1616;
	static const uint16 kR47 = 1653;
	static const uint16 kR52 = 1666;
	static const uint16 kR53 = 1670;
	static const uint16 kR55 = 1677;
	static const uint16 kSpritename1 = 1819;
	static const uint16 kSpritename3 = 1832;
	static const uint16 kIdname = 1845;
	static const uint16 kCharacterset1 = 1857;
	static const uint16 kCharacterset2 = 1870;
	static const uint16 kCharacterset3 = 1883;
	static const uint16 kSamplename = 1896;
	static const uint16 kBasicsample = 1909;
	static const uint16 kIcongraphics0 = 1922;
	static const uint16 kIcongraphics1 = 1935;
	static const uint16 kExtragraphics1 = 1948;
	static const uint16 kIcongraphics8 = 1961;
	static const uint16 kMongraphicname = 1974;
	static const uint16 kMongraphics2 = 1987;
	static const uint16 kCityname = 2000;
	static const uint16 kTravelgraphic1 = 2013;
	static const uint16 kTravelgraphic2 = 2026;
	static const uint16 kDiarygraphic = 2039;
	static const uint16 kMonitorfile1 = 2052;
	static const uint16 kMonitorfile2 = 2065;
	static const uint16 kMonitorfile10 = 2078;
	static const uint16 kMonitorfile11 = 2091;
	static const uint16 kMonitorfile12 = 2104;
	static const uint16 kMonitorfile13 = 2117;
	static const uint16 kMonitorfile20 = 2130;
	static const uint16 kMonitorfile21 = 2143;
	static const uint16 kMonitorfile22 = 2156;
	static const uint16 kMonitorfile23 = 2169;
	static const uint16 kMonitorfile24 = 2182;
	static const uint16 kFoldertext = 2195;
	static const uint16 kDiarytext = 2208;
	static const uint16 kPuzzletextname = 2221;
	static const uint16 kTraveltextname = 2234;
	static const uint16 kIntrotextname = 2247;
	static const uint16 kEndtextname = 2260;
	static const uint16 kCommandtextname = 2273;
	static const uint16 kVolumetabname = 2286;
	static const uint16 kFoldergraphic1 = 2299;
	static const uint16 kFoldergraphic2 = 2312;
	static const uint16 kFoldergraphic3 = 2325;
	static const uint16 kSymbolgraphic = 2338;
	static const uint16 kGungraphic = 2351;
	static const uint16 kMonkface = 2364;
	static const uint16 kTitle0graphics = 2377;
	static const uint16 kTitle1graphics = 2390;
	static const uint16 kTitle2graphics = 2403;
	static const uint16 kTitle3graphics = 2416;
	static const uint16 kTitle4graphics = 2429;
	static const uint16 kTitle5graphics = 2442;
	static const uint16 kTitle6graphics = 2455;
	static const uint16 kTitle7graphics = 2468;
	static const uint16 kPalettescreen = 2481;
	static const uint16 kCurrentfile = 2970;
	static const uint16 kDmaaddresses = 5118;
	static const uint16 kFileheader = 6091;
	static const uint16 kFiledata = 6141;
	static const uint16 kExtradata = 6181;
	static const uint16 kRoomdata = 6187;
	static const uint16 kMadeuproomdat = 7979;
	static const uint16 kRoomscango = 8011;
	static const uint16 kRoompics = 8027;
	static const uint16 kOplist = 8042;
	static const uint16 kInputline = 8045;
	static const uint16 kLinedata = 8173;
	static const uint16 kPresslist = 8573;
	static const uint16 kSavenames = 8579;
	static const uint16 kSavefiles = 8698;
	static const uint16 kRecname = 8789;
	static const uint16 kQuitrequested = 8802;
	static const uint16 kSubtitles = 8803;
	static const uint16 kForeignrelease = 8804;
	static const uint16 kStak = 8805;
	static const uint16 kBlocktextdat = (0);
	static const uint16 kPersonframes = (0);
	static const uint16 kDebuglevel1 = (0);
	static const uint16 kDebuglevel2 = (0);
	static const uint16 kPlayback = (0);
	static const uint16 kMap = (0);
	static const uint16 kSettextdat = (0);
	static const uint16 kSpanish = (0);
	static const uint16 kFramedata = (0);
	static const uint16 kRecording = (0);
	static const uint16 kFlags = (0);
	static const uint16 kGerman = (0);
	static const uint16 kTextunder = (0);
	static const uint16 kPathdata = (0);
	static const uint16 kDemo = (0);
	static const uint16 kExframedata = (0);
	static const uint16 kIntextdat = (0);
	static const uint16 kFreetextdat = (0);
	static const uint16 kFrframedata = (0);
	static const uint16 kSettext = (0+(130*2));
	static const uint16 kOpeninvlist = (0+(228*13));
	static const uint16 kRyaninvlist = (0+(228*13)+32);
	static const uint16 kPointerback = (0+(228*13)+32+60);
	static const uint16 kMapflags = (0+(228*13)+32+60+(32*32));
	static const uint16 kStartpal = (0+(228*13)+32+60+(32*32)+(11*10*3));
	static const uint16 kEndpal = (0+(228*13)+32+60+(32*32)+(11*10*3)+768);
	static const uint16 kMaingamepal = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768);
	static const uint16 kSpritetable = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768+768);
	static const uint16 kSetlist = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768+768+(32*32));
	static const uint16 kFreelist = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768+768+(32*32)+(128*5));
	static const uint16 kExlist = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768+768+(32*32)+(128*5)+(80*5));
	static const uint16 kPeoplelist = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768+768+(32*32)+(128*5)+(80*5)+(100*5));
	static const uint16 kZoomspace = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768+768+(32*32)+(128*5)+(80*5)+(100*5)+(12*5));
	static const uint16 kPrintedlist = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768+768+(32*32)+(128*5)+(80*5)+(100*5)+(12*5)+(46*40));
	static const uint16 kListofchanges = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768+768+(32*32)+(128*5)+(80*5)+(100*5)+(12*5)+(46*40)+(5*80));
	static const uint16 kUndertimedtext = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768+768+(32*32)+(128*5)+(80*5)+(100*5)+(12*5)+(46*40)+(5*80)+(250*4));
	static const uint16 kRainlist = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768+768+(32*32)+(128*5)+(80*5)+(100*5)+(12*5)+(46*40)+(5*80)+(250*4)+(256*30));
	static const uint16 kInitialreelrouts = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768+768+(32*32)+(128*5)+(80*5)+(100*5)+(12*5)+(46*40)+(5*80)+(250*4)+(256*30)+(6*64));
	static const uint16 kInitialvars = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768+768+(32*32)+(128*5)+(80*5)+(100*5)+(12*5)+(46*40)+(5*80)+(250*4)+(256*30)+(6*64)+991-534);
	static const uint16 kLengthofbuffer = (0+(228*13)+32+60+(32*32)+(11*10*3)+768+768+768+(32*32)+(128*5)+(80*5)+(100*5)+(12*5)+(46*40)+(5*80)+(250*4)+(256*30)+(6*64)+991-534+68-0);
	static const uint16 kReellist = (0+(36*144));
	static const uint16 kIntext = (0+(38*2));
	static const uint16 kLengthofmap = (0+(66*60));
	static const uint16 kFreetext = (0+(82*2));
	static const uint16 kBlocktext = (0+(98*2));
	static const uint16 kBlocks = (0+192);
	static const uint16 kFrframes = (0+2080);
	static const uint16 kExframes = (0+2080);
	static const uint16 kFrames = (0+2080);
	static const uint16 kExdata = (0+2080+30000);
	static const uint16 kExtextdat = (0+2080+30000+(16*114));
	static const uint16 kExtext = (0+2080+30000+(16*114)+((114+2)*2));
	static const uint16 kLengthofextra = (0+2080+30000+(16*114)+((114+2)*2)+18000);
	static const uint16 kPersontxtdat = (0+24);
	static const uint16 kPersontext = (0+24+(1026*2));
	static const uint16 kInputport = (0x63);
	static const uint16 kForeign = (1);
	static const uint16 kCd = (1);
	static const uint16 kNumexobjects = (114);
	static const uint16 kUndertextsizey = (13);
	static const uint16 kZoomy = (132);
	static const uint16 kFreedatlen = (16*80);
	static const uint16 kExtextlen = (18000);
	static const uint16 kLenofmapstore = (22*8*20*8);
	static const uint16 kUndertextsizex = (228);
	static const uint16 kNumchanges = (250);
	static const uint16 kUndertimedysize = (30);
	static const uint16 kExframeslen = (30000);
	static const uint16 kTablesize = (32);
	static const uint16 kScreenwidth = (320);
	static const uint16 kKeypadx = (36+112);
	static const uint16 kItempicsize = (44);
	static const uint16 kDiaryy = (48+12);
	static const uint16 kOpsy = (52);
	static const uint16 kSymboly = (56);
	static const uint16 kInventy = (58);
	static const uint16 kMenuy = (60);
	static const uint16 kOpsx = (60);
	static const uint16 kMaplength = (60);
	static const uint16 kHeaderlen = (6187-6091);
	static const uint16 kSymbolx = (64);
	static const uint16 kSetdatlen = (64*128);
	static const uint16 kMapwidth = (66);
	static const uint16 kTextstart = (66*2);
	static const uint16 kMaplen = (66*60);
	static const uint16 kDiaryx = (68+24);
	static const uint16 kLengthofvars = (68-0);
	static const uint16 kKeypady = (72);
	static const uint16 kZoomx = (8);
	static const uint16 kInventx = (80);
	static const uint16 kMenux = (80+40);
	static const uint16 kLenofreelrouts = (991-534);

	void useWire();
	void getNamePos();
	void femaleFan();
	void identifyOb();
	void useLighter();
	void showMenu();
	void usePoolReader();
	void useOpenBox();
	void clearBuffers();
	void showSymbol();
	void getObTextStart();
	void dumpDiaryKeys();
	void getRidOfReels();
	void readKey();
	void louis();
	void entryTexts();
	void buttonEnter();
	void checkInput();
	void setMode();
	void getBackFromOps();
	void openSarters();
	void putUnderCentre();
	void checkObjectSize();
	void titles();
	void deallocateMem();
	void mainScreen();
	void watchReel();
	void showSlots();
	void openFileFromC();
	void getTime();
	void candles1();
	void fadeDOS();
	void runEndSeq();
	void loadKeypad();
	void findText1();
	void isRyanHolding();
	void interruptTest();
	void useCashCard();
	void useWall();
	void openTomb();
	void buttonFour();
	void doSomeTalk();
	void getAnyAdDir();
	void showSaveOps();
	void introMonks1();
	void resetLocation();
	void introMonks2();
	void advisor();
	void additionalText();
	void doFade();
	void useElevator5();
	void useElevator4();
	void useElevator1();
	void useElevator3();
	void useElevator2();
	void buttonOne();
	void keyboardRead();
	void getOpenedSize();
	void doShake();
	void resetKeyboard();
	void soundStartup();
	void sLabDoorA();
	void sLabDoorC();
	void sLabDoorB();
	void sLabDoorE();
	void sLabDoorD();
	void adjustUp();
	void sLabDoorF();
	void loadIntroRoom();
	void mouseCall();
	void train();
	void fadeDownMon();
	void loadCart();
	void bartender();
	void showDiary();
	void outOfOpen();
	void dirCom();
	void dumpKeypad();
	void dumpZoom();
	void endGameSeq();
	void setBotLeft();
	void findFirstPath();
	void loadOld();
	void useSLab();
	void useAltar();
	void manAsleep2();
	void moreTalk();
	void startTalk();
	void delChar();
	void getAnyAd();
	void endGame();
	void usePipe();
	void getUnderZoom();
	void candles();
	void backObject();
	void rollEndCredits2();
	void reminders();
	void selectSlot2();
	void runTap();
	void talk();
	void getRidOfTemp2();
	void useBalcony();
	void decide();
	void disableSoundInt();
	void priestText();
	void openPoolBoss();
	void buttonTwo();
	void fadeScreenDownHalf();
	void usePlate();
	void lookInInterface();
	void manAsleep();
	void hotelBell();
	void loadSpeech();
	void adjustLeft();
	void callEdensLift();
	void useClearBox();
	void entryAnims();
	void getFreeAd();
	void showArrows();
	void walkIntoRoom();
	void useHatch();
	void printOuterMon();
	void setupPit();
	void showPCX();
	void showDecisions();
	void removeObFromInv();
	void useCoveredBox();
	void openYourNeighbour();
	void fadeScreenUpHalf();
	void getRidOfTempCharset();
	void heavy();
	void useKey();
	void lockLightOn();
	void useLadderB();
	void discOps();
	void middlePanel();
	void monitorLogo();
	void enterSymbol();
	void dirFile();
	void pickupConts();
	void lockLightOff();
	void wearWatch();
	void runIntroSeq();
	void nextColon();
	void attendant();
	void nextSymbol();
	void monks2text();
	void clearPalette();
	void cantDrop();
	void getRidOfAll();
	void copper();
	void openHotelDoor();
	void blank();
	void drinker();
	void placeFreeObject();
	void allPalette();
	void rockstar();
	void adjustRight();
	void putUnderZoom();
	void vSync();
	void findInvPos();
	void dumpMenu();
	void liftNoise();
	void workoutFrames();
	void dumpSymBox();
	void loadGame();
	void getRidOfTemp();
	void dumpSymbol();
	void buttonSix();
	void intro2Text();
	void showOuterPad();
	void getKeyAndLogo();
	void selectOb();
	void usePlinth();
	void useCooker();
	void loadMenu();
	void checkForEMM();
	void receptionist();
	void selectSlot();
	void openFileNoCheck();
	void fadeUpMon();
	void fadeToWhite();
	void loadSaveBox();
	void soundEnd();
	void redes();
	void errorMessage1();
	void errorMessage2();
	void errorMessage3();
	void introMagic2();
	void introMagic3();
	void edenInBath();
	void introMagic1();
	void showDiaryPage();
	void useShield();
	void getBackToOps();
	void rollEndCredits();
	void intro1Text();
	void transferToEx();
	void reExFromInv();
	void examineInventory();
	void getRidOfTemp3();
	void useDryer();
	void outOfInv();
	void diaryKeyP();
	void reExFromOpen();
	void manSatStill();
	void transferMap();
	void showMonk();
	void diaryKeyN();
	void set16ColPalette();
	void interviewer();
	void purgeAnItem();
	void madman();
	void enableSoundInt();
	void madmansTelly();
	void purgeALocation();
	void getRidOfPit();
	void notHeldError();
	void getSetAd();
	void soldier1();
	void getUnderCentre();
	void checkForExit();
	void loadSeg();
	void showKeys();
	void setKeyboardInt();
	void priest();
	void printmessage2();
	void loadNews();
	void rollEm();
	void hangOnPQ();
	void saveGame();
	void findOpenPos();
	void describeOb();
	void deleteExFrame();
	void bossMan();
	void DOSReturn();
	void wheelSound();
	void playGuitar();
	void searchForSame();
	void chewy();
	void getBack1();
	void fadeFromWhite();
	void useWindow();
	void wearShades();
	void delEverything();
	void fadeScreenDown();
	void poolGuard();
	void openInv();
	void lookAtPlace();
	void useAxe();
	void buttonNought();
	void useElvDoor();
	void putBackObStuff();
	void useLadder();
	void realCredits();
	void handClap();
	void smokeBloke();
	void afterIntroRoom();
	void buttonNine();
	void findAllOpen();
	void readFromFile();
	void initialInv();
	void quitSymbol();
	void setTopRight();
	void findSetObject();
	void hangOne();
	void carParkDrip();
	void useDiary();
	void deleteExObject();
	void moneyPoke();
	void destSelect();
	void lastDest();
	void removeFreeObject();
	void trapDoor();
	void openLouis();
	void buttonThree();
	void lookAtCard();
	void helicopter();
	void setSoundOff();
	void setPickup();
	void dropObject();
	void isItRight();
	void openOb();
	void drawItAll();
	void useStereo();
	void candles2();
	void pickupOb();
	void error();
	void showOpBox();
	void clearBeforeLoad();
	void bibleQuote();
	void doLoad();
	void showExit();
	void useTrainer();
	void addToPressList();
	void dumpCurrent();
	void showDiaryKeys();
	void dontLoadSeg();
	void intro3Text();
	void allocateMem();
	void useOpened();
	void inventory();
	void fillOpen();
	void signOn();
	void deleteExText();
	void foghornSound();
	void showLoadOps();
	void examIcon();
	void showGun();
	void louisChair();
	void locationPic();
	void openTVDoor();
	void triggerMessage();
	void smallCandle();
	void swapWithOpen();
	void dreamweb();
	void dropError();
	void edensCDPlayer();
	void callEdensDLift();
	void checkInside();
	void gates();
	void newGame();
	void setWalk();
	void findPathOfPoint();
	void isSetObOnMap();
	void getDestInfo();
	void drunk();
	void getRidOfTempText();
	void setupTimedUse();
	void grafittiDoor();
	void nextDest();
	void makeCaps();
	void read();
	void fadeScreenUps();
	void hotelControl();
	void mugger();
	void atmospheres();
	void loadPersonal();
	void gettingShot();
	void setTopLeft();
	void searchForString();
	void selectOpenOb();
	void security();
	void buttonFive();
	void soundOnReels();
	void useGun();
	void autoAppear();
	void openRyan();
	void callHotelLift();
	void showMan();
	void useFullCart();
	void newPlace();
	void loadSample();
	void useCardReader1();
	void useCardReader2();
	void useCardReader3();
	void tattooMan();
	void useHandle();
	void openFile();
	void showPuzText();
	void incRyanPage();
	void greyscaleSum();
	void buttonEight();
	void findExObject();
	void clearChanges();
	void useChurchHole();
	void searchForFiles();
	void monkSpeaking();
	void clearRest();
	void madmanRun();
	void randomNum1();
	void keeper();
	void afterNewRoom();
	void getExAd();
	void closeFile();
	void initialMonCols();
	void checkForShake();
	void useButtonA();
	void fadeScreenUp();
	void generalError();
	void mode640x480();
	void openEden();
	void execCommand();
	void obsThatDoThings();
	void updateSymbolBot();
	void findPuzText();
	void useChurchGate();
	void monkAndRyan();
	void swapWithInv();
	void useControl();
	void buttonSeven();
	void redrawMainScrn();
	void showGroup();
	void buttonPress();
	void makeMainScreen();
	void useWinch();
	void setBotRight();
	void mainMan();
	void aide();
	void getEitherAd();
	void zoomOnOff();
	void updateSymbolTop();
	void allPointer();
	void checkSoundInt();
	void clearReels();
	void maleFan();
	void doSaveLoad();
	void createName();
	void readCityPic();
	void getPersonText();
	void inToInv();
	void parser();
	void setMouse();
	void intro();
	void fadeScreenDowns();
	void openHotelDoor2();
	void getRidOfTempsP();
	void scanForNames();
	void selectLocation();
	void underTextLine();
	void sitDownInBar();
	void showNames();
	void saveFileRead();
	void emergencyPurge();
	void useMenu();
	void alleyBarkSound();
	void useCart();
	void introMusic();
	void quitKey();
	void processTrigger();
	void volumeAdjust();
	void randomNum2();
	void loadSecondSample();
	void transferConToEx();
	void businessMan();
	void panelIcons1();
	void adjustDown();
	void withWhat();
	void createFile();
	void useRailing();
	void useHole();
	void useObject();
	void readDestIcon();
};
}

#endif
