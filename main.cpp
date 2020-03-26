//#include "stdafx.h"

#include "lib.h"
#include "ObjLoader.h"
#include "parameters.h"
#include "draw.h"
#include "skybox.h"
#include "tga.h"
#include "readfile.h"
#include "savefile.h"

//string filePath = "monkey.obj";
//ObjLoader objModel = ObjLoader(filePath);

void init_pos();

void setLightRes() {
    GLfloat lightPosition[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);
    glEnable(GL_LIGHTING); //启用光源
    glEnable(GL_LIGHT0);   //使用指定灯光
}

void display(){ 
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	glLoadIdentity();
	xtrans = -xpos;
	ztrans = -zpos;
	ytrans = -ypos;
	sceneroty = 360.0f - now_dir_xz;
	sceneupdown = -lookupdown;
	
	//第一人称模拟重力
	if (usermode == TRAVEL_MODE_FIRST&&ypos>=4) {
		ypos -= 1;
	}

	if (usermode == TRAVEL_MODE_THIRD||usermode==SAVE_MODEL_MODE||usermode == TRAVEL_MODE_FIRST) {
		
		
		draw_map();

		read_and_draw();

		/*
		glRotatef(sceneupdown,1.0f,0,0);
		glRotatef(sceneroty,0,1.0f,0);
		glTranslatef(5.0+xtrans,0.1+ytrans+2,-10+ztrans+15);
		draw_pyramid();
		glLoadIdentity();
		*/

		/*
		glRotatef(sceneupdown, 1.0f, 0, 0);
		glRotatef(sceneroty, 0, 1.0f, 0);
		glTranslatef(xtrans, ytrans, ztrans);
		setLightRes();
		objModel.Draw();//绘制obj模型
		glLoadIdentity();
		*/


		if (usermode!=MAP_MADE_MODE) draw_skybox();
		

		printf_s("%lf %lf %lf %lf %lf\n", xpos, ypos, zpos, now_dir_xz, lookupdown);
	}
	if (usermode == MAP_MADE_MODE) {
		//绘制纹理地图
		for (int i = 0; i < MAP_SIZE; i++) {
			for (int j = 0; j < MAP_SIZE; j++) {
				GLint mapshowx = -10 + j * MAP_SHOW_SIZE, mapshowz = -10 + i * MAP_SHOW_SIZE;
				vertex a = { mapshowx,0,mapshowz };
				vertex b = { mapshowx+MAP_SHOW_SIZE,0,mapshowz };
				vertex c = { mapshowx+MAP_SHOW_SIZE,0,mapshowz+MAP_SHOW_SIZE };
				vertex d = { mapshowx,0,mapshowz+MAP_SHOW_SIZE };
				glRotatef(sceneupdown, 1.0f, 0, 0);
				glRotatef(sceneroty, 0, 1.0f, 0);
				glTranslatef(xtrans, ytrans, ztrans);
				draw_face(a,b,c,d, formtga[map_form[i][j]]);
				glLoadIdentity();
				if (nowi == i && nowj == j) {
					vertex a = { mapshowx,1,mapshowz };
					vertex b = { mapshowx+0.5,1,mapshowz };
					vertex c = { mapshowx+0.5,1,mapshowz+0.5 };
					vertex d = { mapshowx,1,mapshowz+0.5 };
					glRotatef(sceneupdown, 1.0f, 0, 0);
					glRotatef(sceneroty, 0, 1.0f, 0);
					glTranslatef(xtrans, ytrans, ztrans);
					draw_face(a,b,c,d, SKYBOX_DOWN);
					glLoadIdentity();
				}
			}
		}
		}
	if (usermode == CREATING_MODE||usermode==SAVE_MODEL_MODE) {
		glRotatef(sceneupdown, 1.0f, 0, 0);
		glRotatef(sceneroty, 0, 1.0f, 0);
		glTranslatef(xtrans, ytrans, ztrans);
		if (usermode == SAVE_MODEL_MODE) {
			glRotatef(save_dir, 0, 1.0f, 0);
			glTranslatef(save_x, save_y, save_z);
		}
		for (int i = 0; i < totcube; i++) {
			if (creating_cube[i].exist) {
				vertex ori = { creating_cube[i].x,creating_cube[i].y,creating_cube[i].z };
				if (now_creating_mode == SELECT_MODE && nowcube == i) {
					draw_cube(ori, creating_cube[i].size, SKYBOX_DOWN);
				}
				else {
					draw_cube(ori, creating_cube[i].size, creating_cube[i].texture_num);
				}
			}
		}
		glLoadIdentity();
	}

	glutSwapBuffers();
}

void mouse(int btn, int state, int x, int y)
{ 
    display();
}

int check(int check_dir,GLint x,GLint y,GLint z) {
	map<point, int>::iterator key;
	//front
	if (check_dir == 0) {
		point newp = { x,y,z - CREATING_CUBE_SIZE };
		key = index.find(newp);
		if (key != index.end()) {
			return key->second;
		}
	}
	//back
	if (check_dir == 1) {
		point newp = { x,y,z + CREATING_CUBE_SIZE };
		key = index.find(newp);
		if (key != index.end()) {
			return key->second;
		}
	}
	//up
	if (check_dir == 2) {
		point newp = { x,y+CREATING_CUBE_SIZE,z };
		key = index.find(newp);
		if (key != index.end()) {
			return key->second;
		}
	}
	//down
	if (check_dir == 3) {
		point newp = { x,y-CREATING_CUBE_SIZE,z };
		key = index.find(newp);
		if (key != index.end()) {
			return key->second;
		}
	}
	//left
	if (check_dir == 4) {
		point newp = { x-CREATING_CUBE_SIZE,y,z };
		key = index.find(newp);
		if (key != index.end()) {
			return key->second;
		}
	}
	//right
	if (check_dir == 5) {
		point newp = { x+CREATING_CUBE_SIZE,y,z };
		key = index.find(newp);
		if (key != index.end()) {
			return key->second;
		}
	}
	return -1;
}

void update_creating_cube() {
	creating_cube[totcube].size = CREATING_CUBE_SIZE;
	creating_cube[totcube].texture_num = nowtexture;

	int id;
	creating_cube[totcube].front_num = -1;
	creating_cube[totcube].back_num = -1;
	creating_cube[totcube].up_num = -1;
	creating_cube[totcube].down_num = -1;
	creating_cube[totcube].left_num = -1;
	creating_cube[totcube].right_num = -1;
	if ((id = check(0, creating_cube[totcube].x, creating_cube[totcube].y, creating_cube[totcube].z)) != -1) {
	    creating_cube[totcube].front_num = id;
		creating_cube[id].back_num = totcube;
	}
	if ((id = check(1, creating_cube[totcube].x, creating_cube[totcube].y, creating_cube[totcube].z)) != -1) {
		creating_cube[totcube].back_num = id;
		creating_cube[id].front_num = totcube;
	}
	if ((id = check(2, creating_cube[totcube].x, creating_cube[totcube].y, creating_cube[totcube].z)) != -1) {
		creating_cube[totcube].up_num = id;
		creating_cube[id].down_num = totcube;
	}
	if ((id = check(3, creating_cube[totcube].x, creating_cube[totcube].y, creating_cube[totcube].z)) != -1) {
		creating_cube[totcube].down_num = id;
		creating_cube[id].up_num = totcube;
	}
	if ((id = check(4, creating_cube[totcube].x, creating_cube[totcube].y, creating_cube[totcube].z)) != -1) {
		creating_cube[totcube].left_num = id;
		creating_cube[id].right_num = totcube;
	}
	if ((id = check(5, creating_cube[totcube].x, creating_cube[totcube].y, creating_cube[totcube].z)) != -1) {
		creating_cube[totcube].right_num = id;
		creating_cube[id].left_num = totcube;
	}

	creating_cube[totcube].exist = true;
	point newp = { creating_cube[totcube].x,creating_cube[totcube].y,creating_cube[totcube].z };
	index.insert(pair<point, int>(newp, totcube));
	nowcube = totcube;
	totcube++;
	return;
}

void keys(unsigned char key, int x, int y)
{ 
	if (usermode == SAVE_MODEL_MODE) {
		if (key == 'g') {
			save_x -= 1;
		}
		if (key == 'j') {
			save_x += 1;
		}
		if (key == 'y') {
			save_z -= 1;
		}
		if (key == 'h') {
			save_z += 1;
		}
		if (key == 't') {
			save_y += 1;
		}
		if (key == 'u') {
			save_y -= 1;
		}
		if (key == 'b') {
			save_dir += 5;
			if (save_dir > 360) save_dir -= 360;
		}
		if (key == 'n') {
			save_dir -= 5;
			if (save_dir < 0) save_dir += 360;
		}
	}
	if (usermode == TRAVEL_MODE_THIRD||(usermode==CREATING_MODE&&now_creating_mode==VIEW_MODE)||usermode==SAVE_MODEL_MODE||usermode == TRAVEL_MODE_FIRST) {
		if (key == 's')
		{
			//if (!capture[(int)(ceil(xpos + (float)sin(now_dir_xz*piover180)*speed))][(int)ceil(ypos)][(int)ceil(zpos + (float)cos(now_dir_xz*piover180)*speed)]) {
				xpos += (float)sin(now_dir_xz*piover180)*speed;
				zpos += (float)cos(now_dir_xz*piover180)*speed;
			//}
		}
		if (key == 'w')
		{
			//if (!capture[(int)(ceil(xpos - (float)sin(now_dir_xz*piover180)*speed))][(int)ceil(ypos)][(int)ceil(zpos - (float)cos(now_dir_xz*piover180)*speed)]) {
				xpos -= (float)sin(now_dir_xz*piover180)*speed;
				zpos -= (float)cos(now_dir_xz*piover180)*speed;
			//}
		}
		if (key == 'a')
		{
			//if (!capture[(int)(ceil(xpos - (float)cos(now_dir_xz*piover180)*speed))][(int)ceil(ypos)][(int)ceil(zpos + (float)sin(now_dir_xz*piover180)*speed)]) {
				xpos -= (float)cos(now_dir_xz*piover180)*speed;
				zpos += (float)sin(now_dir_xz*piover180)*speed;
			//}
		}
		if (key == 'd')
		{
			//if (!capture[(int)(ceil(xpos + (float)cos(now_dir_xz*piover180)*speed))][(int)ceil(ypos)][(int)ceil(zpos - (float)sin(now_dir_xz*piover180)*speed)]) {
				xpos += (float)cos(now_dir_xz*piover180)*speed;
				zpos -= (float)sin(now_dir_xz*piover180)*speed;
			//}
		}
		if (key == 'q')
		{
			//if (!capture[(int)ceil(xpos)][(int)ceil(ypos + 1)][(int)ceil(zpos)]) {
				ypos += 1;
			//}
		}
		if (key == 'e')
		{
			if (usermode == CREATING_MODE) {
				ypos -= 1;
			}
			else {
				if (!capture[(int)ceil(xpos)][(int)ceil(ypos - 1)][(int)ceil(zpos)]) {
					ypos -= 1;
				}
			}
		}
		if (usermode == TRAVEL_MODE_THIRD) {
			if (xpos > WORLD_MAX_X) xpos = WORLD_MAX_X;
			if (xpos < WORLD_MIN_X) xpos = WORLD_MIN_X;
			if (ypos > WORLD_MAX_Y) ypos = WORLD_MAX_Y;
			if (ypos < WORLD_MIN_Y) ypos = WORLD_MIN_Y;
			if (zpos > WORLD_MAX_Z) zpos = WORLD_MAX_Z;
			if (zpos < WORLD_MIN_Z) zpos = WORLD_MIN_Z;
		}
	}
	if (usermode == CREATING_MODE) {
		if (key == 'f') {
			creating_cube[totcube].x = CREATING_ORI_X;
			creating_cube[totcube].y = CREATING_ORI_Y;
			creating_cube[totcube].z = CREATING_ORI_Z;
			creating_cube[totcube].size = CREATING_CUBE_SIZE;
			creating_cube[totcube].texture_num =0;
			creating_cube[totcube].front_num =-1;
			creating_cube[totcube].back_num =-1;
			creating_cube[totcube].up_num =-1;
			creating_cube[totcube].down_num =-1;
			creating_cube[totcube].left_num =-1;
			creating_cube[totcube].right_num =-1;
			creating_cube[totcube].exist = true;
			point newp = { creating_cube[totcube].x,creating_cube[totcube].y,creating_cube[totcube].z };
			index.insert(pair<point, int>(newp, totcube));
			nowcube = 0;
			totcube = 1;
		}
		if (key == 'a') {
			if (now_creating_mode == WORK_MODE) {
				if (creating_cube[nowcube].left_num == -1) {
					creating_cube[totcube].x = creating_cube[nowcube].x - CREATING_CUBE_SIZE;
					creating_cube[totcube].y = creating_cube[nowcube].y;
					creating_cube[totcube].z = creating_cube[nowcube].z;

					update_creating_cube();
				}
			}
			if (now_creating_mode == SELECT_MODE) {
				if (creating_cube[nowcube].left_num != -1) {
					nowcube = creating_cube[nowcube].left_num;
				}
			}
		}
		if (key == 'd') {
			if (now_creating_mode == WORK_MODE) {
				if (creating_cube[nowcube].right_num == -1) {
					creating_cube[totcube].x = creating_cube[nowcube].x + CREATING_CUBE_SIZE;
					creating_cube[totcube].y = creating_cube[nowcube].y;
					creating_cube[totcube].z = creating_cube[nowcube].z;

					update_creating_cube();
				}
			}
			if (now_creating_mode == SELECT_MODE) {
				if (creating_cube[nowcube].right_num != -1) {
					nowcube = creating_cube[nowcube].right_num;
				}
			}
		}
		if (key == 'w') {
			if (now_creating_mode == WORK_MODE) {
				if (creating_cube[nowcube].front_num == -1) {
					creating_cube[totcube].x = creating_cube[nowcube].x ;
					creating_cube[totcube].y = creating_cube[nowcube].y;
					creating_cube[totcube].z = creating_cube[nowcube].z- CREATING_CUBE_SIZE;

					update_creating_cube();
				}
			}
			if (now_creating_mode == SELECT_MODE) {
				if (creating_cube[nowcube].front_num != -1) {
					nowcube = creating_cube[nowcube].front_num;
				}
			}
		}
		if (key == 's') {
			if (now_creating_mode == WORK_MODE) {
				if (creating_cube[nowcube].back_num == -1) {
					creating_cube[totcube].x = creating_cube[nowcube].x ;
					creating_cube[totcube].y = creating_cube[nowcube].y;
					creating_cube[totcube].z = creating_cube[nowcube].z + CREATING_CUBE_SIZE;

					update_creating_cube();
				}
			}
			if (now_creating_mode == SELECT_MODE) {
				if (creating_cube[nowcube].back_num != -1) {
					nowcube = creating_cube[nowcube].back_num;
				}
			}
		}
		if (key == 'q') {
			if (now_creating_mode == WORK_MODE) {
				if (creating_cube[nowcube].up_num == -1) {
					creating_cube[totcube].x = creating_cube[nowcube].x;
					creating_cube[totcube].y = creating_cube[nowcube].y + CREATING_CUBE_SIZE;
					creating_cube[totcube].z = creating_cube[nowcube].z;

					update_creating_cube();
				}
			}
			if (now_creating_mode == SELECT_MODE) {
				if (creating_cube[nowcube].up_num != -1) {
					nowcube = creating_cube[nowcube].up_num;
				}
			}
		}
		if (key == 'e') {
			if (now_creating_mode == WORK_MODE) {
				if (creating_cube[nowcube].down_num == -1) {
					creating_cube[totcube].x = creating_cube[nowcube].x;
					creating_cube[totcube].y = creating_cube[nowcube].y - CREATING_CUBE_SIZE;
					creating_cube[totcube].z = creating_cube[nowcube].z;

					update_creating_cube();
				}
			}
			if (now_creating_mode == SELECT_MODE) {
				if (creating_cube[nowcube].down_num != -1) {
					nowcube = creating_cube[nowcube].down_num;
				}
			}
		}
		if (key == 'z') {
			if (now_creating_mode == WORK_MODE) {
				nowtexture=creating_cube[nowcube].texture_num = (creating_cube[nowcube].texture_num + 1) % MAX_TEXTURE_NUM;
			}
		}
		if (key == 'x') {
			if (now_creating_mode == WORK_MODE) {
				nowtexture=creating_cube[nowcube].texture_num = (creating_cube[nowcube].texture_num + MAX_TEXTURE_NUM - 1) % MAX_TEXTURE_NUM;
			}
		}
		if (key == 'r') {
			//这里有一个bug，暂时未修复，在没有方块剩余时再删除会出问题，解决方法是维护一个记录总方块数的变量（非tot_cube)
			if (now_creating_mode == WORK_MODE) {
				creating_cube[nowcube].exist = false;
				point newp = { creating_cube[totcube].x,creating_cube[totcube].y,creating_cube[totcube].z };
				index.erase(newp);
				int nextcube = -1;
				if (creating_cube[nowcube].front_num != -1) {
					if (nextcube == -1) nextcube = creating_cube[nowcube].front_num;
					creating_cube[creating_cube[nowcube].front_num].back_num = -1;
					creating_cube[nowcube].front_num = -1;
				}
				if (creating_cube[nowcube].back_num != -1) {
					if (nextcube == -1) nextcube = creating_cube[nowcube].back_num;
					creating_cube[creating_cube[nowcube].back_num].front_num = -1;
					creating_cube[nowcube].back_num = -1;
				}
				if (creating_cube[nowcube].up_num != -1) {
					if (nextcube == -1) nextcube = creating_cube[nowcube].up_num;
					creating_cube[creating_cube[nowcube].up_num].down_num = -1;
					creating_cube[nowcube].up_num = -1;
				}
				if (creating_cube[nowcube].down_num != -1) {
					if (nextcube == -1) nextcube = creating_cube[nowcube].down_num;
					creating_cube[creating_cube[nowcube].down_num].up_num = -1;
					creating_cube[nowcube].down_num = -1;
				}
				if (creating_cube[nowcube].left_num != -1) {
					if (nextcube == -1) nextcube = creating_cube[nowcube].left_num;
					creating_cube[creating_cube[nowcube].left_num].right_num = -1;
					creating_cube[nowcube].left_num = -1;
				}
				if (creating_cube[nowcube].right_num != -1) {
					if (nextcube == -1) nextcube = creating_cube[nowcube].right_num;
					creating_cube[creating_cube[nowcube].right_num].left_num = -1;
					creating_cube[nowcube].right_num = -1;
				}
				nowcube = nextcube;
			}
		}
		if (key == 'c') {
			if (now_creating_mode == WORK_MODE && totcube == 1) {
				CREATING_CUBE_SIZE += 1;
				creating_cube[0].size = CREATING_CUBE_SIZE;
			}
		}
		if (key == 'v') {
			if (now_creating_mode == WORK_MODE && totcube == 1) {
				CREATING_CUBE_SIZE -= 1;
				creating_cube[0].size = CREATING_CUBE_SIZE;
			}
		}
	}
	if (usermode == MAP_MADE_MODE) {
		if (key == 'z') {
			map_form[nowi][nowj] = (map_form[nowi][nowj] + 1) % FORMNUM;
		}
		if (key == 'w') {
			if (nowi > 0) nowi--;
		}
		if (key == 's') {
			if (nowi < MAP_SIZE-1) nowi++;
		}
		if (key == 'a') {
			if (nowj > 0) nowj--;
		}
		if (key == 'd') {
			if (nowj < MAP_SIZE-1) nowj++;
		}
	}
	display();
}

void myReshape(int w, int h)
{ 
	printf_s("%d %d\n", GLUT_WINDOW_X, GLUT_WINDOW_Y);
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	/*
	if(w<=h) glFrustum(-2.0, 2.0, -2.0 * (GLfloat) h/ (GLfloat) w,2.0* (GLfloat) h / (GLfloat) w, 2.0, 20.0); 
	else glFrustum(-2.0, 2.0, -2.0 * (GLfloat) w/ (GLfloat) h,2.0* (GLfloat) w / (GLfloat) h, 2.0, 20.0);
	*/
	gluPerspective(45.0, w/h, 1.0, 1000.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

int last_x=250, last_y=250;
void FixMouse(int& x, int& y)  
{  
    if (x < winwidth / 4)  
    {  
        last_x += winwidth / 4;  
        x += winwidth / 4;  
        SetCursorPos(x,y);  
    }  
    if (x > winwidth / 4 * 3)  
    {  
        last_x -= winwidth / 4;  
        x -= winwidth / 4;  
        SetCursorPos(x,y);  
    }  
    if (y < winheight / 4)  
    {  
        last_y += winheight / 4;  
        y += winheight / 4;  
        SetCursorPos(x,y);  
    }  
    if (y > winheight / 4 * 3)  
    {  
        last_y -= winheight / 4;  
        y -= winheight / 4;  
        SetCursorPos(x,y);  
    }  
}  


void passivemouse(int x, int y)
{
	if (usermode == TRAVEL_MODE_THIRD||(usermode==CREATING_MODE&&now_creating_mode==VIEW_MODE)||usermode==SAVE_MODEL_MODE||usermode == TRAVEL_MODE_FIRST) {
		if (x > last_x) {
			now_dir_xz -= 1;
		}
		else if (x < last_x) {
			now_dir_xz += 1;
		}
		last_x = x;
		if (y > last_y) {
			lookupdown -= 1.0f;
		}
		else if (y < last_y) {
			lookupdown += 1.0f;
		}
		while (now_dir_xz > 360) now_dir_xz -= 360;
		while (now_dir_xz < 0) now_dir_xz += 360;
		last_y = y;
		//glutSetCursor(GLUT_CURSOR_NONE);
		glutSetCursor(GLUT_CURSOR_CROSSHAIR);
		FixMouse(x, y);
	}
	display();
}




void SetupRC()
    {
    GLubyte *pBytes;
    GLint iWidth, iHeight, iComponents;
    GLenum eFormat;
    GLint iLoop;
    
	// Black background
	glClearColor(0.0f, 0.0f, 0.0f,1.0f);

    // Textures applied as decals, no lighting or coloring effects
	glEnable(GL_TEXTURE_2D);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);

    // Load textures
    glGenTextures(TEXTURE_COUNT, textures);
    for(iLoop = 0; iLoop < TEXTURE_COUNT; iLoop++)
        {
        // Bind to next texture object
        glBindTexture(GL_TEXTURE_2D, textures[iLoop]);

        // Load texture, set filter and wrap modes
        pBytes =(GLubyte*)gltLoadTGA(szTextureFiles[iLoop],&iWidth, &iHeight, &iComponents, &eFormat);
        gluBuild2DMipmaps(GL_TEXTURE_2D, iComponents, iWidth, iHeight, eFormat, GL_UNSIGNED_BYTE, pBytes);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        
        // Don't need original texture data any more
        free(pBytes);
        }
	readfile();
	glShadeModel(GL_SMOOTH);
    setLightRes();
	init_real_map();
	memset(capture, false, sizeof(capture));
	for (int i = 0; i < 200; i++) {
		for (int j = 0; j < 200; j++) {
			capture[i][0][j] = true;
		}
	}
	usermode == TRAVEL_MODE_FIRST;
	init_pos();
    }

void init_pos() {
	if (usermode == TRAVEL_MODE_THIRD) {
		xpos = 0;
		zpos = 0;
		ypos = 200;
		speed = 1;
		now_dir_xz = 0;
		lookupdown = -90;
		save_x = 0;
		save_y = 0;
		save_z = 0;
		save_dir = 0;
	}
	else if (usermode == TRAVEL_MODE_FIRST||CREATING_MODE) {
		xpos = 0;
		zpos = 0;
		ypos = 0;
		speed = 1;
		now_dir_xz = 0;
		lookupdown = 0.0f;
	}
}

void ProcessMenu(int value)
    {
    // Projection plane
    GLfloat zPlane[] = { 0.0f, 0.0f, 1.0f, 0.0f };
    
    // Store render mode
    
    // Set up textgen based on menu selection
    switch(value)
        {
        case 1:
            // Object Linear
			usermode = TRAVEL_MODE_THIRD;
			init_pos();
			//glutCreateSubWindow(glutGetWindow(),0,0,winwidth,winheight);
            break;
		case 2:
			usermode = TRAVEL_MODE_FIRST;
			init_pos();
			break;
		case 3:
			usermode = CREATING_MODE;
			init_pos();
			break;
		case 4:
			if (usermode == CREATING_MODE) {
				now_creating_mode = WORK_MODE;
			}
			break;
		case 5:
			if (usermode == CREATING_MODE) {
				now_creating_mode = VIEW_MODE;
			}
			break;
		case 6:
			if (usermode == CREATING_MODE) {
				now_creating_mode = SELECT_MODE;
			}
			break;
		case 7:
			usermode = SAVE_MODEL_MODE;
			init_pos();
			break;
		case 8:
			if (usermode == SAVE_MODEL_MODE) {
				savefile();
			}
			break;
		case 9:
			usermode = MAP_MADE_MODE;
			xpos = 0;
            zpos = 0;
            ypos = 30;
			now_dir_xz = 0;
			lookupdown = -90;
			break;
		case 10:
			if (usermode == MAP_MADE_MODE) {
				calculate_map();
				usermode = TRAVEL_MODE_THIRD;
				init_pos();
			}
			break;
		case 11: {
			glutFullScreen();
			break;
		}
		case 12: {
			glutReshapeWindow(winwidth,winheight);
			break;
		}

        default:
			usermode = TRAVEL_MODE_THIRD;
            // Sphere Map

            break;
		}

    display();    // Redisplay
    }


int main(int argc, char **argv)
{ 
	glutInit(&argc, argv); 
	//glutInitDisplayMode( GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH); 
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH | GLUT_STENCIL);
	glutInitWindowSize(winwidth, winheight); 
	glutCreateWindow("graphics_final");
	glutReshapeFunc(myReshape); 
	glutDisplayFunc(display); 
	glutMouseFunc(mouse); 
	glutKeyboardFunc(keys);
	glutPassiveMotionFunc(passivemouse);
	glEnable(GL_DEPTH_TEST); 
	SetupRC();
	glutCreateMenu(ProcessMenu);
	glutAddMenuEntry("travel at third", 1);
	glutAddMenuEntry("travel at first", 2);
	glutAddMenuEntry("3D model making mode", 3);
	glutAddMenuEntry("3D model making mode->work mode", 4);
	glutAddMenuEntry("3D model making mode->view mode", 5);
	glutAddMenuEntry("3D model making mode->select mode", 6);
	glutAddMenuEntry("3D model making mode->save model into the world", 7);
	glutAddMenuEntry("confirm to save", 8);
	glutAddMenuEntry("map make mode", 9);
	glutAddMenuEntry("map make mode->generate map", 10);
	glutAddMenuEntry("full screen", 11);
	glutAddMenuEntry("not full screen", 12);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
	glutMainLoop();
}