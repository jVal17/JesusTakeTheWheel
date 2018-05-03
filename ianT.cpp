//
// Name: Ian Thomas
// My source file
// Date modified: 04/20/2018
// Current goals: Add a fully functioning menu system, add graphics to the menus
//

#include "ianT.h"


void renderText()
{
	Rect r;
	r.bot = 984;
	r.left = 50;
	r.center = 1;
	ggprint8b(&r, 16, 0x00ff0000, "Jesus Take");
	ggprint8b(&r, 16, 0x00ff0000, "the Wheel");
	ggprint8b(&r, 16, 0x00ff0000, "- Controls -");
	ggprint8b(&r, 16, 0x00ff0000, "ESC to pause");
	ggprint8b(&r, 16, 0x00ff0000, "W,S,A,D to move");
	glEnd();
	r.bot = 500;
	r.left = 430;
	r.center = 0;
	ggprint8b(&r, 16, 0x00ff0000, "Ian Thomas");
	glEnd();
}

void mainMenu(const int xres, const int yres)
{
	Rect m;
	m.bot = yres - 650;
	m.left = xres/2 - 55;
	m.center = 0;
	ggprint12(&m, 16, 0xee6666, "Play Game");
	ggprint12(&m, 16, 0x000000, "Settings **IN PROGRESS**");

	int pointerX;
	int pointerY;

	if (menuPosition == 1) {
		pointerX = xres/2 - 73;
		pointerY = yres - 640;
	} else if (menuPosition == 2) {
		pointerX = xres/2 - 73;
		pointerY = yres - 657;
	}

	float w = 5.0;
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(pointerX, pointerY, 0);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i( w, w);
	glTexCoord2f(1.0f, 1.0f); glVertex2i( w,-w);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(-w,-w);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-w, w);
	glEnd();
	glPopMatrix();

	/*if (inMainMenu) {
		if (key == XK_Return) {
			if (menuPosition == 1) {
				inMainMenu = 0;
				inGame = 1;
			}
		}
	}*/ // try to implement this after menu is finished.
}

void pauseMenu(const int xres, const int yres)
{
	unsigned int white = 0xffffff;

	Rect m;
	m.bot = yres - 200;
	m.left = xres/2 -55;
	m.center = 0;
	ggprint12(&m, 16, white, "Resume Game");
	ggprint12(&m, 16, 0x000000, "Settings **IN PROGRESS**");
	ggprint12(&m, 16, 0x000000, "Controls **IN PROGRESS**");
	ggprint12(&m, 16, white, "Exit Game");

	int pointerX;
	int pointerY;

	if (menuPosition == 1) {
		pointerX = xres/2 - 73;
		pointerY = yres - 190;
	} else if (menuPosition == 2) {
		pointerX = xres/2 - 73;
		pointerY = yres - 207;
	} else if (menuPosition == 3) {
		pointerX = xres/2 - 73;
		pointerY = yres - 224;
	} else if (menuPosition == 4) {
		pointerX = xres/2 -73;
		pointerY = yres - 241;
	}

	float w = 5.0;
	glColor3f(1.0f, 1.0f, 1.0f);
	glPushMatrix();
	glTranslatef(pointerX, pointerY, 0);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i( w, w);
	glTexCoord2f(1.0f, 1.0f); glVertex2i( w,-w);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(-w,-w);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-w, w);
	glEnd();
	glPopMatrix();
}

void gameOverMenu(const int xres, const int yres)
{
    Rect m;
    m.bot = yres - 600;
    m.left = xres/2 - 30;
    m.center = 0;
    ggprint12(&m, 16, 0xffffff, "Start Again");
    ggprint12(&m, 16, 0x000000, "Main Menu");
    ggprint12(&m, 16, 0x000000, "Change Game Mode");
    ggprint12(&m, 16, 0xffffff, "Exit Game");

    int pointerX;
    int pointerY;

    if (menuPosition == 1) {
	pointerX = xres/2 - 73;
	pointerY = yres - 590;
    } else if (menuPosition == 2) {
	pointerX = xres/2 - 73;
	pointerY = yres - 607;
    } else if (menuPosition == 3) {
	pointerX = xres/2 - 73;
	pointerY = yres - 624;
    } else if (menuPosition == 4) {
	pointerX = xres/2 - 73;
	pointerY = yres - 641;
    }

    float w = 5.0;
    glColor3f(1.0f, 1.0f, 1.0f);
    glPushMatrix();
    glTranslatef(pointerX, pointerY, 0);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i( w, w);
    glTexCoord2f(1.0f, 1.0f); glVertex2i( w,-w);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(-w,-w);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-w, w);
    glEnd();
    glPopMatrix();
}

