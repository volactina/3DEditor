#ifndef DRAW_H
#define DRAW_H

#include <time.h>  
#include <stdlib.h>
#include "textures.h"

static void init_real_map();
static void calculate_map();
static void draw_map();
static void draw_face(vertex a, vertex b, vertex c, vertex d, int texture_num);
static void draw_cube(vertex ori, GLfloat size, int texture_num);
static void draw_tree(vertex p);

static void init_real_map() {
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			real_map[i][j].ori_x = -100 + j * REAL_UNIT_SIZE;
			real_map[i][j].ori_z = -100 + i * REAL_UNIT_SIZE;
		}
	}
	return;
}

static void calculate_map() {
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			real_map[i][j].form = map_form[i][j];
			switch (real_map[i][j].form) {
			case MOUNTAINS: {
				real_map[i][j].texture.push_back(FORM_MOUNTAIN);
				srand((unsigned)time(NULL));
				int a = 5, b = 10;
				int h = (rand() % (b - a + 1)) + a;
				point p = { real_map[i][j].ori_x + REAL_UNIT_SIZE / 2,h,real_map[i][j].ori_z + REAL_UNIT_SIZE / 2 };
				real_map[i][j].critical_point.push_back(p);
				break;
			}
			case GRASSLAND: {
				//real_map[i][j].texture.push_back(FORM_GRASS);
				break;
			}
			case RIVER: {
				//real_map[i][j].texture.push_back(FORM_WATER);
				break;
			}
			}
		}
	}
	return;
}

static void draw_tree(vertex p) {
	const int height = 6;
	for (int i = 0; i < height; i++) {
		vertex nowp = { p[0],p[1]+i,p[2] };
		glRotatef(sceneupdown, 1.0f, 0, 0);
		glRotatef(sceneroty, 0, 1.0f, 0);
		glTranslatef(xtrans, ytrans, ztrans);
		draw_cube(nowp, 1, FORM_WOOD);
		glLoadIdentity();
	}
	for (int i = -1; i < 2; i++) {
		for (int j = 0; j < 2; j++) {
			vertex nowp = {p[0]+j,p[1]+height+i+1,p[2]-1};
			glRotatef(sceneupdown, 1.0f, 0, 0);
			glRotatef(sceneroty, 0, 1.0f, 0);
			glTranslatef(xtrans, ytrans, ztrans);
			draw_cube(nowp, 1, FORM_LEAF);
			glLoadIdentity();
		}
		for (int j = 0; j < 2; j++) {
			vertex nowp = {p[0]+1,p[1]+height+i+1,p[2]+j};
			glRotatef(sceneupdown, 1.0f, 0, 0);
			glRotatef(sceneroty, 0, 1.0f, 0);
			glTranslatef(xtrans, ytrans, ztrans);
			draw_cube(nowp, 1, FORM_LEAF);
			glLoadIdentity();
		}
		for (int j = 0; j >=-1; j--) {
			vertex nowp = {p[0]+j,p[1]+height+i+1,p[2]+1};
			glRotatef(sceneupdown, 1.0f, 0, 0);
			glRotatef(sceneroty, 0, 1.0f, 0);
			glTranslatef(xtrans, ytrans, ztrans);
			draw_cube(nowp, 1, FORM_LEAF);
			glLoadIdentity();
		}
		for (int j = 0; j >=-1; j--) {
			vertex nowp = {p[0]-1,p[1]+height+i+1,p[2]+j};
			glRotatef(sceneupdown, 1.0f, 0, 0);
			glRotatef(sceneroty, 0, 1.0f, 0);
			glTranslatef(xtrans, ytrans, ztrans);
			draw_cube(nowp, 1, FORM_LEAF);
			glLoadIdentity();
		}
	}
	return;
}

static void draw_map() {
	for (int i = 0; i < MAP_SIZE; i++) {
		for (int j = 0; j < MAP_SIZE; j++) {
			switch (real_map[i][j].form) {
			case MOUNTAINS: {

				for (int k = 0; k < 10; k++) {
					for (int m = 0; m < 10; m++) {
						vertex p = { real_map[i][j].ori_x+k,0,real_map[i][j].ori_z+m };

						//vertex a = { real_map[i][j].ori_x+k,1,real_map[i][j].ori_z+m };
						//vertex b = { real_map[i][j].ori_x+k + 1,1,real_map[i][j].ori_z+m };
						//vertex c = { real_map[i][j].ori_x+k + 1,1,real_map[i][j].ori_z+m + 1 };
						//vertex d = { real_map[i][j].ori_x+k,1,real_map[i][j].ori_z+m + 1 };

						glRotatef(sceneupdown, 1.0f, 0, 0);
						glRotatef(sceneroty, 0, 1.0f, 0);
						glTranslatef(xtrans, ytrans, ztrans);
						//draw_face(a, b, c, d, FORM_GRASS);
						draw_cube(p,1, FORM_GRASS);
						glLoadIdentity();
					}
				}

				GLint nowh = real_map[i][j].critical_point[0].y;
				int layer = 0;
				vertex p = { real_map[i][j].critical_point[0].x,real_map[i][j].critical_point[0].y,real_map[i][j].critical_point[0].z };
				glRotatef(sceneupdown, 1.0f, 0, 0);
				glRotatef(sceneroty, 0, 1.0f, 0);
				glTranslatef(xtrans, ytrans, ztrans);
				draw_cube(p, MOUNTAIN_SIZE, FORM_MOUNTAIN);
				glLoadIdentity();
				while (nowh >= 0) {
					layer++;
					nowh -= MOUNTAIN_SIZE;
					GLfloat orix = real_map[i][j].critical_point[0].x - layer * 0.1;
					GLfloat oriz = real_map[i][j].critical_point[0].z - layer * 0.1;
					GLfloat oriy = nowh;
					for (int k = 0; k < 2 * layer + 1; k++) {
						vertex p = { orix,oriy,oriz };
						glRotatef(sceneupdown, 1.0f, 0, 0);
						glRotatef(sceneroty, 0, 1.0f, 0);
						glTranslatef(xtrans, ytrans, ztrans);
						draw_cube(p, MOUNTAIN_SIZE, FORM_MOUNTAIN);
						glLoadIdentity();
						orix += MOUNTAIN_SIZE;
					}
					orix -= MOUNTAIN_SIZE;
					for (int k = 0; k < 2 * layer; k++) {
						oriz += MOUNTAIN_SIZE;
						vertex p = { orix,oriy,oriz };
						glRotatef(sceneupdown, 1.0f, 0, 0);
						glRotatef(sceneroty, 0, 1.0f, 0);
						glTranslatef(xtrans, ytrans, ztrans);
						draw_cube(p, MOUNTAIN_SIZE, FORM_MOUNTAIN);
						glLoadIdentity();
					}
					for (int k = 0; k < 2 * layer; k++) {
						orix -= MOUNTAIN_SIZE;
						vertex p = { orix,oriy,oriz };
						glRotatef(sceneupdown, 1.0f, 0, 0);
						glRotatef(sceneroty, 0, 1.0f, 0);
						glTranslatef(xtrans, ytrans, ztrans);
						draw_cube(p, MOUNTAIN_SIZE, FORM_MOUNTAIN);
						glLoadIdentity();
					}
					for (int k = 0; k < 2 * layer - 1; k++) {
						oriz -= MOUNTAIN_SIZE;
						vertex p = { orix,oriy,oriz };
						glRotatef(sceneupdown, 1.0f, 0, 0);
						glRotatef(sceneroty, 0, 1.0f, 0);
						glTranslatef(xtrans, ytrans, ztrans);
						draw_cube(p, MOUNTAIN_SIZE, FORM_MOUNTAIN);
						glLoadIdentity();
					}
				}
				break;
			}
			case GRASSLAND: {
				/*
				vertex a = { real_map[i][j].ori_x,1,real_map[i][j].ori_z };
				vertex b = { real_map[i][j].ori_x + REAL_UNIT_SIZE,1,real_map[i][j].ori_z };
				vertex c = { real_map[i][j].ori_x + REAL_UNIT_SIZE,1,real_map[i][j].ori_z + REAL_UNIT_SIZE };
				vertex d = { real_map[i][j].ori_x,1,real_map[i][j].ori_z + REAL_UNIT_SIZE };
				glRotatef(sceneupdown, 1.0f, 0, 0);
				glRotatef(sceneroty, 0, 1.0f, 0);
				glTranslatef(xtrans, ytrans, ztrans);
				draw_face(a, b, c, d, FORM_GRASS);
				glLoadIdentity();
				*/
				for (int k = 0; k < 10; k++) {
					for (int m = 0; m < 10; m++) {
						vertex p = { real_map[i][j].ori_x+k,0,real_map[i][j].ori_z+m };

						//vertex a = { real_map[i][j].ori_x+k,1,real_map[i][j].ori_z+m };
						//vertex b = { real_map[i][j].ori_x+k + 1,1,real_map[i][j].ori_z+m };
						//vertex c = { real_map[i][j].ori_x+k + 1,1,real_map[i][j].ori_z+m + 1 };
						//vertex d = { real_map[i][j].ori_x+k,1,real_map[i][j].ori_z+m + 1 };

						glRotatef(sceneupdown, 1.0f, 0, 0);
						glRotatef(sceneroty, 0, 1.0f, 0);
						glTranslatef(xtrans, ytrans, ztrans);
						//draw_face(a, b, c, d, FORM_GRASS);
						draw_cube(p,1, FORM_GRASS);
						glLoadIdentity();
					}
				}
				break;
			}
			case RIVER: {
				for (int k = 0; k < 10; k++) {
					for (int m = 0; m < 10; m++) {
						vertex a = { real_map[i][j].ori_x+k,0,real_map[i][j].ori_z+m };
						vertex b = { real_map[i][j].ori_x+k + 1,0,real_map[i][j].ori_z+m };
						vertex c = { real_map[i][j].ori_x+k + 1,0,real_map[i][j].ori_z+m + 1 };
						vertex d = { real_map[i][j].ori_x+k,0,real_map[i][j].ori_z+m + 1 };
						glRotatef(sceneupdown, 1.0f, 0, 0);
						glRotatef(sceneroty, 0, 1.0f, 0);
						glTranslatef(xtrans, ytrans, ztrans);
						draw_face(a, b, c, d, FORM_WATER);
						glLoadIdentity();
					}
				}
				break;
			}
			case FOREST: {

				for (int k = 0; k < 10; k++) {
					for (int m = 0; m < 10; m++) {
						vertex p = { real_map[i][j].ori_x+k,0,real_map[i][j].ori_z+m };

						//vertex a = { real_map[i][j].ori_x+k,1,real_map[i][j].ori_z+m };
						//vertex b = { real_map[i][j].ori_x+k + 1,1,real_map[i][j].ori_z+m };
						//vertex c = { real_map[i][j].ori_x+k + 1,1,real_map[i][j].ori_z+m + 1 };
						//vertex d = { real_map[i][j].ori_x+k,1,real_map[i][j].ori_z+m + 1 };

						glRotatef(sceneupdown, 1.0f, 0, 0);
						glRotatef(sceneroty, 0, 1.0f, 0);
						glTranslatef(xtrans, ytrans, ztrans);
						//draw_face(a, b, c, d, FORM_GRASS);
						draw_cube(p,1, FORM_FORESTLAND);
						glLoadIdentity();
					}
				}

				for (int k = 0; k < 2; k++) {
					for (int m = 0; m < 2; m++) {
						vertex p{real_map[i][j].ori_x+2+4*m,1,real_map[i][j].ori_z+2+4*k};
						draw_tree(p);
					}
				}

				break;
			}
			default: {
				vertex a = { real_map[i][j].ori_x,1,real_map[i][j].ori_z };
				vertex b = { real_map[i][j].ori_x + REAL_UNIT_SIZE,1,real_map[i][j].ori_z };
				vertex c = { real_map[i][j].ori_x + REAL_UNIT_SIZE,1,real_map[i][j].ori_z + REAL_UNIT_SIZE };
				vertex d = { real_map[i][j].ori_x,1,real_map[i][j].ori_z + REAL_UNIT_SIZE };
				glRotatef(sceneupdown, 1.0f, 0, 0);
				glRotatef(sceneroty, 0, 1.0f, 0);
				glTranslatef(xtrans, ytrans, ztrans);
				draw_face(a, b, c, d, TEXTURE_FLOOR);
				glLoadIdentity();
				break;
			}
			}
		}
	}
	return;
}

static void draw_face(vertex a, vertex b, vertex c, vertex d, int texture_num)
{
	if (texture_num >= TEXTURE_COUNT) {
		printf_s("texture %d not existed!draw failed!\n", texture_num);
		return;
	}
	glBindTexture(GL_TEXTURE_2D, textures[texture_num]);
    glBegin(GL_POLYGON);  
	glTexCoord2f(0.0f, 0.0f);
	glVertex3fv(a);
	glTexCoord2f(1.0f, 0.0f);
	glVertex3fv(b);
	glTexCoord2f(1.0f, 1.0f);
	glVertex3fv(c);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3fv(d);
	glEnd();
}

static void draw_cube(vertex ori,GLfloat size,int texture_num )
{
	vertex v[8] = { {ori[0],ori[1],ori[2]},{ori[0] + size,ori[1],ori[2]},
	                {ori[0] + size,ori[1],ori[2] + size},{ori[0],ori[1],ori[2] + size},
	                {ori[0],ori[1] + size,ori[2]},{ori[0] + size,ori[1] + size,ori[2]},
	                {ori[0] + size,ori[1]+size,ori[2]+size},{ori[0],ori[1]+size,ori[2]+size} };
	draw_face(v[0],v[1],v[2],v[3],texture_num);
	draw_face(v[4],v[5],v[6],v[7],texture_num);
	draw_face(v[6],v[5],v[1],v[2],texture_num);
	draw_face(v[4],v[7],v[3],v[0],texture_num);
	draw_face(v[7],v[6],v[2],v[3],texture_num);
	draw_face(v[5],v[4],v[0],v[1],texture_num);
}

//total thing num
//each thing unit num ori_pos(x,t,z)
//type(0 draw_cube 1 draw_face) ... texturenum
static void read_and_draw() {
	for (int i = 0; i < tot_things; i++) {
		for (int j = 0; j < tot_unit[i]; j++) {
			switch (u[i][j].type) {
			case 0: {
				vertex a = { u[i][j].x,u[i][j].y,u[i][j].z };
				glRotatef(sceneupdown,1.0f,0,0);
	            glRotatef(sceneroty,0,1.0f,0);
	            glTranslatef(xtrans+ori_x[i],ytrans+ori_y[i],ztrans+ori_z[i]);
				draw_cube(a, (GLfloat)u[i][j].size, u[i][j].texture_num);
				glLoadIdentity();
				break;
			}
			case 1: {
				glRotatef(sceneupdown,1.0f,0,0);
	            glRotatef(sceneroty+ori_dir[i],0,1.0f,0);
	            glTranslatef(xtrans+ori_x[i],ytrans+ori_y[i],ztrans+ori_z[i]);
				vertex a = {u[i][j].p1x,u[i][j].p1y,u[i][j].p1z};
				vertex b = {u[i][j].p2x,u[i][j].p2y,u[i][j].p2z};
				vertex c = {u[i][j].p3x,u[i][j].p3y,u[i][j].p3z};
				vertex d = {u[i][j].p4x,u[i][j].p4y,u[i][j].p4z};
				draw_face(a, b, c, d, u[i][j].texture_num);
				glLoadIdentity();
				break;
			}
			default:
				printf("no such type!\n");
				return;
			}
		}
	}
}
#endif
