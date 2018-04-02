//
//Name: Ian Thomas
//My source file
//Date modified: 03/09/2018
//

#include "ianT.h"


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

void mainMenu (const int xres, const int yres)
{
    unsigned int white = 0xffffff;

    Rect m;
    m.bot = yres - 200;
    m.left = xres/2 - 55;
    m.center = 0;
    ggprint12(&m, 16, white, "Play Game");
    ggprint12(&m, 16, 0x000000, "Settings **IN PROGRESS**");

    int pointerX;
    int pointerY;

    if (menuPosition == 1) {
        pointerX = xres/2 - 73;
        pointerY = yres - 190;
    } else if (menuPosition == 2) {
        pointerX = xres/2 - 73;
        pointerY = yres - 207;
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

   /* if (keys[XK_Return]) {
        if (menuPosition == 1) {
            inMainMenu = 0;
            inGame = 1;
        }
    }*/ //try to link this properly later
}
