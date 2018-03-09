//
//Name: Ian Thomas
//My source file
//Date: 2/23/2018
//

#include "ianT.h"

double profileFunction(clock_t start, clock_t end)
{
    start = clock();
    static double timeElapsed = 0.0;
    end = clock();
    timeElapsed += (double)(end - start)/CLOCKS_PER_SEC;
    return timeElapsed;
}
void renderText()
{
    clock_t startTime = clock();
    double timeElapsed;
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
    clock_t endTime = clock();
    timeElapsed = profileFunction(startTime, endTime);
    ggprint8b(&r, 16, 0x00ff0000, "%f", timeElapsed);
    glEnd();
}
