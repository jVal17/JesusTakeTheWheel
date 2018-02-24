// Jorge Zuniga
// My changes

#include "jorgeZ.h"

void screenPrint() {
	Rect r;
	r.bot = 500;
	r.left = 10;
	r.center = 0;
	ggprint8b(&r, 16, 0x00ff0000, "Changes made");
	ggprint8b(&r, 16, 0x00ff0000, "by Jorge Zuniga");
	glEnd();
}
