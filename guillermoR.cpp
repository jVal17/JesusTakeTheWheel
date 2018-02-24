//Guillermo Ramirez
//Seperate file for Guillermo Ramirez

#include "guillermoR.h"

//Function is found in the bottom of render() in our main file, "srcfile.cpp".
void drawBox(){
	glColor3f(0.0, 0.0, 0.0);
	// Translates the black box beforehand
	glPushMatrix();
	glTranslatef(-206.0,512.0,0.0);
	// Creates the black square in the middle of the screen
	glBegin(GL_QUADS);
	glVertex2i( 412,  -50);
	glVertex2i( 412,   50);
	glVertex2i( 512,   50);
	glVertex2i( 512,  -50);
	glEnd();
	glPopMatrix();

	// Aligns and draws the text 
	Rect r;
	r.bot = 520;
	r.left = 215;
	r.center = 0;
	ggprint8b(&r, 16, 0x00ff0000, "Black Box &");
	ggprint8b(&r, 16, 0x00ff0000, "Text From");
	ggprint8b(&r, 16, 0x00ff0000, "guillermoR.cpp");
	glEnd();
}

