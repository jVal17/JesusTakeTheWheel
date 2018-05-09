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
	m.left = xres/2 - 45;
	m.center = 0;
	ggprint12(&m, 16, 0x000000, "Play Game");
	ggprint12(&m, 16, 0x000000, "Audio");
	ggprint12(&m, 16, 0x000000, "Tutorial");

	int pointerX;
	int pointerY;

	Rect m2;	//selected menu item
	m2.bot = yres - 650;
	m2.left = xres/2 - 45;
	m2.center = 0;

	if (menuPosition == 1) {
		pointerX = xres/2 - 73;
		pointerY = yres - 640;
		ggprint12(&m2, 16, 0x00666eee, "Play Game");
	} else if (menuPosition == 2) {
		pointerX = xres/2 - 73;
		pointerY = yres - 657;
		ggprint12(&m2, 16, 0x00666eee, " ");
		ggprint12(&m2, 16, 0x00666eee, "Audio");
	} else if (menuPosition == 3) {
		pointerX = xres/2 - 73;
		pointerY = yres - 674;
		ggprint12(&m2, 16, 0x00666eee, " ");
		ggprint12(&m2, 16, 0x00666eee, " ");
		ggprint12(&m2, 16, 0x00666eee, "Tutorial");	
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

void pauseMenu(const int xres, const int yres)
{
	unsigned int white = 0xffffff;

	Rect m;
	m.bot = yres - 200;
	m.left = xres/2 - 55;
	m.center = 0;
	ggprint12(&m, 16, white, "Resume Game");
	ggprint12(&m, 16, white, "Audio");
	ggprint12(&m, 16, white, "Tutorial");
	ggprint12(&m, 16, white, "Exit Game");

	int pointerX;
	int pointerY;
	Rect m2;	// Selected menu item
	m2.bot = yres - 200;
	m2.left = xres/2 - 55;
	m2.center = 0;

	if (menuPosition == 1) {
		pointerX = xres/2 - 73;
		pointerY = yres - 190;
		ggprint12(&m2, 16, 0x00eeee00, "Resume Game");
	} else if (menuPosition == 2) {
		pointerX = xres/2 - 73;
		pointerY = yres - 207;
		ggprint12(&m2, 16, 0x00eeee00, " ");
		ggprint12(&m2, 16, 0x00eeee00, "Audio");
	} else if (menuPosition == 3) {
		pointerX = xres/2 - 73;
		pointerY = yres - 224;
		ggprint12(&m2, 16, 0x00eeee00, " ");			
		ggprint12(&m2, 16, 0x00eeee00, " ");
		ggprint12(&m2, 16, 0x00eeee00, "Tutorial");
	} else if (menuPosition == 4) {
		pointerX = xres/2 -73;
		pointerY = yres - 241;
		ggprint12(&m2, 16, 0x00eeee00, " ");
		ggprint12(&m2, 16, 0x00eeee00, " ");
		ggprint12(&m2, 16, 0x00eeee00, " ");
		ggprint12(&m2, 16, 0x00eeee00, "Exit Game");
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
	m.bot = yres - 700;
	m.left = xres/2 - 40;
	m.center = 0;
	ggprint12(&m, 16, 0xffffff, "Start Again");
	ggprint12(&m, 16, 0xffffff, "Main Menu");
	ggprint12(&m, 16, 0xffffff, "Audio");
	ggprint12(&m, 16, 0xffffff, "Exit Game");

	int pointerX;
	int pointerY;

	Rect m2;	// Selected menu item
	m2.bot = yres - 700;
	m2.left = xres/2 - 40;
	m2.center = 0;	

	if (menuPosition == 1) {
		pointerX = xres/2 - 73;
		pointerY = yres - 690;
		ggprint12(&m2, 16, 0x00eeee00, "Start Again");
	} else if (menuPosition == 2) {
		pointerX = xres/2 - 73;
		pointerY = yres - 707;
		ggprint12(&m2, 16, 0xffffff, " ");
		ggprint12(&m2, 16, 0x00eeee00, "Main Menu");
	} else if (menuPosition == 3) {
		pointerX = xres/2 - 73;
		pointerY = yres - 724;
		ggprint12(&m2, 16, 0xffffff, " ");
		ggprint12(&m2, 16, 0xffffff, " ");
		ggprint12(&m2, 16, 0x00eeee00, "Audio");
	} else if (menuPosition == 4) {
		pointerX = xres/2 - 73;
		pointerY = yres - 741;
		ggprint12(&m2, 16, 0xffffff, " ");
		ggprint12(&m2, 16, 0xffffff, " ");
		ggprint12(&m2, 16, 0xffffff, " ");
		ggprint12(&m2, 16, 0x00eeee00, "Exit Game");
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

void audioMenu (const int xres, const int yres)
{
	Rect m;
	m.bot = yres - 200;
	m.left = xres/2 - 55;
	m.center = 0;
	ggprint12(&m, 16, 0x00dddd00, "Enable Audio");
	ggprint12(&m, 16, 0x00dddd00, "Disable Audio");
	ggprint12(&m, 16, 0x000000, " ");

	if (audio_on) {
		ggprint12(&m, 16, 0x00dddd00, "Audio is enabled.");
	} else {
		ggprint12(&m, 16, 0x00dddd00, "Audio is disabled.");
	}

	int pointerX = xres/2 - 73;
	int pointerY = yres - 190;
	Rect m2;	// Selected menu item
	m.bot = yres - 200;
	m.left = xres/2 - 55;
	m.center = 0;

	if (menuPosition == 1) {
		pointerX = xres/2 - 73;
		pointerY = yres - 190;
		ggprint12(&m2, 16, 0x00eeee00, "Enable Audio");
	} else if (menuPosition == 2) {
		pointerX = xres/2 - 73;
		pointerY = yres - 207;
		ggprint12(&m2, 16, 0x000000, " ");
		ggprint12(&m2, 16, 0x00eeee00, "Disable Audio");
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

void tutorial (const int xres, const int yres)
{
	Rect m;
	m.bot = yres - 70;
	m.left = xres/2 - 200;
	m.center = 0;
	ggprint12(&m, 16, 0xffffff, "The main goal of Jesus Take the Wheel is to "
			"avoid the oncoming traffic");
	ggprint12(&m, 16, 0xffffff, "and survive for as long as you can.");
	ggprint12(&m, 16, 0xffffff, "Your car can withstand 3 hits before it breaks. "
			"See how long you can last.");

	Rect m2;
	m2.bot = yres - 130;
	m2.left = xres/10;
	m2.center = 0;
	ggprint12(&m2, 16, 0xffffff, "Controls:");
	ggprint12(&m2, 16, 0xffffff, "w - moves up");
	ggprint12(&m2, 16, 0xffffff, "s - moves down");
	ggprint12(&m2, 16, 0xffffff, "a - moves left");
	ggprint12(&m2, 16, 0xffffff, "d - moves right");
}

