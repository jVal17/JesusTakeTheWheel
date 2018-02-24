//Guillermo Ramirez
//Seperate file for Guillermo Ramirez

#include "guillermoR.h"

void drawBox()
{
	Rect r;
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(-206.0,512.0,0.0);
	glBegin(GL_QUADS);

	glVertex2i( 412,  -50);
	glVertex2i( 412,   50);
	glVertex2i( 512,   50);
	glVertex2i( 512,  -50);

	glEnd();
	glPopMatrix();

	r.bot = 520;
	r.left = 215;
	r.center = 0;
	ggprint8b(&r, 16, 0x00ff0000, "Black Box &");
	ggprint8b(&r, 16, 0x00ff0000, "Text From");
	ggprint8b(&r, 16, 0x00ff0000, "guillermoR.cpp");
	glEnd();
}

