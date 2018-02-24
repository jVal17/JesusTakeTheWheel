//
//Name: Ian Thomas
//My source file
//Date: 2/23/2018
//

#include "ianT.h"

void renderText()
{
    Rect r;
    r.bot = 984;
    r.left = 50;
    r.center = 1;
    ggprint8b(&r, 16, 0x00ff0000, "Jesus");
    ggprint8b(&r, 16, 0x00ff0000, "Take");
    ggprint8b(&r, 16, 0x00ff0000, "the");
    ggprint8b(&r, 16, 0x00ff0000, "Wheel");
    ggprint8b(&r, 10, 0x00ff0000, "- rendered by");
    ggprint8b(&r, 16, 0x00ff0000, "Ian Thomas");
    glEnd();
}
