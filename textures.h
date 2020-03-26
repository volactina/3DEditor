#ifndef TEXTURES_H
#define TEXTURES_H

#include "lib.h"

#define MAX_TEXTURE_NUM 27
//建筑纹理
#define TEXTURE_BRICK  0
#define TEXTURE_FLOOR  1
#define TEXTURE_CEILING 2

#define EX_1 3
#define EX_2 4
#define EX_3 5
#define EX_4 6
#define EX_5 7
#define EX_6 8
#define EX_7 9
#define EX_8 10
#define EX_9 11
#define EX_10 12
#define EX_11 13
#define EX_12 14
#define EX_13 15
#define EX_14 16
#define EX_15 17
#define EX_16 18
#define EX_17 19
#define EX_18 20
#define EX_19 21
#define EX_20 22
#define EX_21 23
#define EX_22 24
#define EX_23 25
#define EX_24 26



//地形
#define FORM_LEAF 27
#define FORM_MOUNTAIN 28
#define FORM_GRASS 29
#define FORM_WATER 30
#define FORM_WOOD 31
#define FORM_FORESTLAND 32

//天空盒
#define SKYBOX_UP 33
#define SKYBOX_DOWN 34
#define SKYBOX_BACK 35
#define SKYBOX_FRONT 36
#define SKYBOX_LEFT 37
#define SKYBOX_RIGHT 38


#define TEXTURE_COUNT  39

GLuint  textures[TEXTURE_COUNT];
const char *szTextureFiles[TEXTURE_COUNT] = { "brick.tga",
											  "floor.tga",
											  "ceiling.tga",
"1.tga",
"2.tga",
"3.tga",
"4.tga",
"5.tga",
"6.tga",
"7.tga",
"8.tga",
"9.tga",
"10.tga",
"11.tga",
"12.tga",
"13.tga",
"14.tga",
"15.tga",
"16.tga",
"17.tga",
"18.tga",
"19.tga",
"20.tga",
"21.tga",
"22.tga",
"23.tga",
"24.tga",


											  "leaf.tga",
											  "mountain.tga",
											  "grass.tga",
	                                          "water.tga",
	                                          "wood.tga",
	                                          "forestland.tga",


											  "redsunset_up.tga",
											  "redsunset_dn.tga",
											  "redsunset_bk.tga",
											  "redsunset_ft.tga",
											  "redsunset_lf.tga",
											  "redsunset_rt.tga" };
#endif