#ifndef SKYBOX_H
#define SKYBOX_H

#include "lib.h"
#include "parameters.h"
#include "textures.h"

static void draw_skybox()
{
	glRotatef(sceneupdown,1.0f,0,0);
	glRotatef(sceneroty,0,1.0f,0);
	glTranslatef(xtrans, ytrans, ztrans);
	glBindTexture(GL_TEXTURE_2D, textures[SKYBOX_DOWN]);
    glBegin(GL_POLYGON);  
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE); 
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(SKYBOX_SIZE,-SKYBOX_SIZE,SKYBOX_SIZE); 
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-SKYBOX_SIZE,-SKYBOX_SIZE,SKYBOX_SIZE);
	glEnd();
	glLoadIdentity();

	glRotatef(sceneupdown,1.0f,0,0);
	glRotatef(sceneroty,0,1.0f,0);
	//glTranslatef(xtrans, ytrans, ztrans);
	glBindTexture(GL_TEXTURE_2D, textures[SKYBOX_UP]);
    glBegin(GL_POLYGON);  
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-SKYBOX_SIZE,SKYBOX_SIZE,SKYBOX_SIZE); 
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(SKYBOX_SIZE,SKYBOX_SIZE,SKYBOX_SIZE);
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(SKYBOX_SIZE,SKYBOX_SIZE,-SKYBOX_SIZE); 
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-SKYBOX_SIZE,SKYBOX_SIZE,-SKYBOX_SIZE);
	glEnd();
	glLoadIdentity();

	glRotatef(sceneupdown,1.0f,0,0);
	glRotatef(sceneroty,0,1.0f,0);
	//glTranslatef(xtrans, ytrans, ztrans);
	glBindTexture(GL_TEXTURE_2D, textures[SKYBOX_FRONT]);
    glBegin(GL_POLYGON);  
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-SKYBOX_SIZE,SKYBOX_SIZE,-SKYBOX_SIZE); 
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(SKYBOX_SIZE,SKYBOX_SIZE,-SKYBOX_SIZE);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE); 
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE);
	glEnd();
	glLoadIdentity();

	glRotatef(sceneupdown,1.0f,0,0);
	glRotatef(sceneroty,0,1.0f,0);
	//glTranslatef(xtrans, ytrans, ztrans);
	glBindTexture(GL_TEXTURE_2D, textures[SKYBOX_BACK]);
    glBegin(GL_POLYGON);  
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(SKYBOX_SIZE,SKYBOX_SIZE,SKYBOX_SIZE); 
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-SKYBOX_SIZE,SKYBOX_SIZE,SKYBOX_SIZE);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-SKYBOX_SIZE,-SKYBOX_SIZE,SKYBOX_SIZE); 
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(SKYBOX_SIZE,-SKYBOX_SIZE,SKYBOX_SIZE);
	glEnd();
	glLoadIdentity();

	glRotatef(sceneupdown,1.0f,0,0);
	glRotatef(sceneroty,0,1.0f,0);
	//glTranslatef(xtrans, ytrans, ztrans);
	glBindTexture(GL_TEXTURE_2D, textures[SKYBOX_RIGHT]);
    glBegin(GL_POLYGON);  
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(SKYBOX_SIZE,SKYBOX_SIZE,-SKYBOX_SIZE); 
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(SKYBOX_SIZE,SKYBOX_SIZE,SKYBOX_SIZE);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(SKYBOX_SIZE,-SKYBOX_SIZE,SKYBOX_SIZE); 
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE);
	glEnd();
	glLoadIdentity();

	glRotatef(sceneupdown,1.0f,0,0);
	glRotatef(sceneroty,0,1.0f,0);
	//glTranslatef(xtrans, ytrans, ztrans);
	glBindTexture(GL_TEXTURE_2D, textures[SKYBOX_LEFT]);
    glBegin(GL_POLYGON);  
	glTexCoord2f(1.0f, 1.0f);
	glVertex3f(-SKYBOX_SIZE,SKYBOX_SIZE,SKYBOX_SIZE); 
	glTexCoord2f(0.0f, 1.0f);
	glVertex3f(-SKYBOX_SIZE,SKYBOX_SIZE,-SKYBOX_SIZE);
	glTexCoord2f(0.0f, 0.0f);
	glVertex3f(-SKYBOX_SIZE,-SKYBOX_SIZE,-SKYBOX_SIZE); 
	glTexCoord2f(1.0f, 0.0f);
	glVertex3f(-SKYBOX_SIZE,-SKYBOX_SIZE,SKYBOX_SIZE);
	glEnd();
	glLoadIdentity();
}
#endif
