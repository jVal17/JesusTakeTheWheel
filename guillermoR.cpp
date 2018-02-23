//Guillermo Ramirez
//Seperate file for Guillermo Ramirez
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "fonts.h"

const int NUM_BOXES = 1;
const int yres = 1024;
//typedef double Vec[3];
//static float wid = 120.0f;
struct Vec {
	float x, y, z;
};

struct Shape {
float width, height;
int bot, left, cen;
Vec center;
int r,g,b;
};

class Global {
public:
    Shape box[NUM_BOXES];
    Global() {
	for(int i = 0; i < NUM_BOXES; i++) 
	{ 
	    box[i].width = 70; 
	    box[i].height = 20; 
	    box[i].center.x = 150+(100*i); 
	    box[i].center.y = 500-(80*i); 
	    box[i].r = 100;  
	    box[i].g = 100;  
	    box[i].b = 100;  
	}
    }
}gl;

void showBox(){
    Rect r;
    r.bot = yres-20;
    r.left = 10;
    r.center = 0;	
    Shape *s;
    float w, h;
    const char* text[NUM_BOXES] = {"IN GUILLERMO FUNCTION"};
    for(int k = 0; k < NUM_BOXES; k++)
    {
	    s = &gl.box[k];
	    glColor3ub(s->r, s->g, s->b);
	    glPushMatrix();
	    glTranslatef(s->center.x, s->center.y, s->center.z);
	    w = s->width;
	    h = s->height;
	    //Adjusts position of the words in comparison to the boxes
	    r.bot = s->height - 25;
	    r.left = s->width - 125;
	    glBegin(GL_QUADS);
	    glVertex2i(-w, -h);
	    glVertex2i(-w,  h);
	    glVertex2i( w,  h);
	    glVertex2i( w, -h);
	    glEnd();
	    ggprint16(&r, 16, 0xCEB121, text[k]);
	    glPopMatrix();
    }
}





//class Car {
//public:
//        Vec pos;
//        Vec vel;
//} car;

//void initCar(int w, int h, GLuint texture, unsigned char *data){
//int w = img[0].width;
//int h = img[0].height;
//Gluint carTexture;
//img[0].data
/*glColor3f(1.0, 1.0, 1.0);
glBindTexture(GL_TEXTURE_2D, texture);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
GL_RGB, GL_UNSIGNED_BYTE, data);
*/
//}

//void renderCar(){
// glPushMatrix();
/*  glTranslatef(car.pos[0], car.pos[1], car.pos[2]);
if (!g.silhouette) {
glBindTexture(GL_TEXTURE_2D, g.bigfootTexture);
} else {

glBindTexture(GL_TEXTURE_2D, g.silhouetteTexture);
glEnable(GL_ALPHA_TEST);
glAlphaFunc(GL_GREATER, 0.0f);
glColor4ub(255,255,255,255);
//}
*/

//      glBegin(GL_QUADS);
/* if (bigfoot.vel[0] > 0.0) {
glTexCoord2f(0.0f, 1.0f); glVertex2i(-wid,-wid);
glTexCoord2f(0.0f, 0.0f); glVertex2i(-wid, wid);
glTexCoord2f(1.0f, 0.0f); glVertex2i( wid, wid);
glTexCoord2f(1.0f, 1.0f); glVertex2i( wid,-wid);
} else {
*/
/*                    glTexCoord2f(1.0f, 1.0f); glVertex2i(-wid,-wid);
		  glTexCoord2f(1.0f, 0.0f); glVertex2i(-wid, wid);
		  glTexCoord2f(0.0f, 0.0f); glVertex2i( wid, wid);
		  glTexCoord2f(0.0f, 1.0f); glVertex2i( wid,-wid);
//}*/
//  glEnd();
//  glPopMatrix();
//
/*
if (g.trees && g.silhouette) {
glBindTexture(GL_TEXTURE_2D, g.forestTransTexture);
glBegin(GL_QUADS);
glTexCoord2f(0.0f, 1.0f); glVertex2i(0, 0);
glTexCoord2f(0.0f, 0.0f); glVertex2i(0, g.yres);
glTexCoord2f(1.0f, 0.0f); glVertex2i(g.xres, g.yres);
glTexCoord2f(1.0f, 1.0f); glVertex2i(g.xres, 0);
glEnd();
}
*/
// glDisable(GL_ALPHA_TEST);
//}
