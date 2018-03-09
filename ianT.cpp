//
//Name: Ian Thomas
//My source file
//Date modified: 03/09/2018
//

#include "ianT.h"
#include <math.h>

extern double timeDiff(struct timespec *start, struct timespec *end);

void renderText()
{
    timespec startTime, endTime;
    static double t = 0.0;
    clock_gettime(CLOCK_REALTIME, &startTime);
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
    clock_gettime(CLOCK_REALTIME, &endTime);
    t += timeDiff(&startTime, &endTime);
    r.bot = 490;
    r.left = 420;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff0000, "Timer 1: %.5f", t);
}
