#ifndef PARAMETERS_H
#define PARAMETERS_H

#define maxn 1000
#define WORLD_MAX_X 200
#define WORLD_MIN_X -200
#define WORLD_MAX_Y 200
#define WORLD_MIN_Y -200
#define WORLD_MAX_Z 200
#define WORLD_MIN_Z -200
#define SKYBOX_SIZE 500

#include "textures.h"

const char r[100] = "things.txt";
FILE *f;
int tot_things;
int tot_unit[maxn];
double ori_x[maxn], ori_y[maxn], ori_z[maxn], ori_dir[maxn];
struct unit {
	int type;
	double x, y, z, size;
	double p1x, p1y, p1z, p2x, p2y, p2z, p3x, p3y, p3z, p4x, p4y, p4z;
	int texture_num;
};
typedef struct unit unit;
unit u[maxn][maxn];

int winwidth=500, winheight=500;

const float piover180 = 0.0174532925f;
float xpos = 0;
float zpos = 0;
float ypos = 0;
float speed = 1;

GLfloat	now_dir_xz = 0;
GLfloat lookupdown = 0.0f;

GLfloat xtrans;
GLfloat ztrans;
GLfloat ytrans;
GLfloat sceneroty;
GLfloat sceneupdown;

/*
GLfloat vertices[][3] = {{-2.0,-2.0,-2.0},{2.0,-2.0,-2.0},{-2.0,2,-2.0},{2.0,2,-2.0},
                           {-2.0,-2.0,2.0},{2.0,-2.0,2.0},{2.0,2,2.0}, {-2.0,2,2.0}};

GLfloat vertices2[][3]={{-3.05,-2,-2},{3.05,-2,-2},{0,-2,3.29},{0,3.1,0.6}};

GLfloat colors[][3] = {{1.0,0.0,0.0},{0.0,1.0,0.0},{0.0,0.0,1.0},{1.0,1.0,0.0},
                    {0.0,1.0,1.0},{1.0,0.0,1.0}, {0.0,0.0,0.0}, {0.0,1.0,1.0}};
*/
typedef GLfloat vertex[3];

#define TRAVEL_MODE_THIRD 0
#define TRAVEL_MODE_FIRST 1
#define CREATING_MODE 2
#define SAVE_MODEL_MODE 3
#define MAP_MADE_MODE 4
GLfloat save_x, save_y, save_z,save_dir;

int usermode=0;

//CREATING MODE PARAMETERS
#define MAX_CREATING 10000
#define CREATING_ORI_X 0
#define CREATING_ORI_Y 0
#define CREATING_ORI_Z -10
#define WORK_MODE 0
#define VIEW_MODE 1
#define SELECT_MODE 2

int now_creating_mode = WORK_MODE;
int nowcube = -1;
int totcube = 0;
int nowtexture = 0;
struct create_cube {
	int front_num, back_num, left_num, right_num, up_num, down_num, texture_num;
	GLfloat x, y, z, size;
	bool exist;
};
typedef struct create_cube create_cube;
create_cube creating_cube[MAX_CREATING];
GLint CREATING_CUBE_SIZE = 3;

struct point {
	GLint x, y, z;
	bool operator<(const point &a) const {
		if (a.x == x) {
			if (a.y == y) {
				return a.z < z;
			}
			else {
				return a.y < y;
			}
		}
		else {
			return a.x < x;
		}
	}
};
typedef struct point point;
map< point, int > index;


//制作地图需要的变量
//20格*20格的地图
#define MAP_SIZE 20
#define MAP_SHOW_SIZE 1
#define REAL_UNIT_SIZE 10
#define MOUNTAIN_SIZE 1
//当前地形
#define GROUND 0
#define MOUNTAINS 1
#define GRASSLAND 2
#define FOREST 3
#define RIVER 4
#define FORMNUM 5
//指定地形绘制提示纹理
int formtga[FORMNUM] = { 1,FORM_MOUNTAIN,FORM_GRASS,FORM_LEAF,FORM_WATER };
int nowi=0,nowj=0;


//记录map各位置的地形,默认为-1
int map_form[MAP_SIZE][MAP_SIZE];

struct map_unit {
	GLint ori_x, ori_z;
	int form;
	vector<point> critical_point;
	vector<int> texture;
};
typedef map_unit map_unit;
map_unit real_map[MAP_SIZE][MAP_SIZE];


//第一人称视角，重力模拟
//对整个每个1*1*1的方格维护一个当前方格是否被占用
bool capture[200][200][200];

#endif 

