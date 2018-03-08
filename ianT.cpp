//
//Name: Ian Thomas
//My source file
//Date: 2/23/2018
//

#include "ianT.h"

void profileFunction()
{
    int i, sum = 0;
    clock_t startTime = clock();
    float timeElapsed = 0;
    for (i = 0; i < 3000000; i++) {
	i *= i;
        timeElapsed += (float)(clock() - startTime)/CLOCKS_PER_SEC;
    }
    sum += (i / 2 * 3 % 4);
    Rect r;
    r.bot = 490;
    r.left = 430;
    r.center = 0;
    ggprint8b(&r, 16, 0x0000ffff, "%f", timeElapsed);
}
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
