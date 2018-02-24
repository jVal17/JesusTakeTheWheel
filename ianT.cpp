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
    r.left = 20;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff0000, "Jesus Take");
    ggprint8b(&r, 16, 0x00ff0000, "the Wheel");
    ggprint8b(&r, 16, 0x00ff0000, "- Controls -");
    ggprint8b(&r, 16, 0x00ff0000, "p to pause");
    glEnd();
    r.bot = 500;
    r.left = 430;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff0000, "Ian Thomas");
    glEnd();
}
