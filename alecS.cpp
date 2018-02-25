// Alec Sherlock
// This is muh file.
// Soft Eng 2018

#include "alecS.h"

void printText() {
	Rect r;
	r.bot = 200;
	r.left = 100;
	r.center = 0;
	ggprint8b(&r, 16, 0x00ff0000, "Text");
	ggprint8b(&r, 16, 0x00ff0000, "by Alec Sherlock");
	glEnd();
}
