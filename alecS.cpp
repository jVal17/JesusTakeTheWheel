// Alec Sherlock
// This is muh file.
// Soft Eng 2018

#include "alecS.h"

void printText()
{
    Rect r;
    r.bot = 200;
    r.left = 100;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff0000, "Text");
    ggprint8b(&r, 16, 0x00ff0000, "by Alec Sherlock");
    glEnd();
}

void drawDatBox1() 
{
    static double t = 0.0;
    struct timespec ftimeStart, ftimeEnd;
    clock_gettime(CLOCK_REALTIME, &ftimeStart);
//------^^ setting up the clock time


    glColor3f(0.25, 0.0, 0.25);
    glPushMatrix();
    glTranslatef(-(pow(14.0, 2.0)), pow(20.0,2.0), 0.0);
//Start the box
    glBegin(GL_QUADS);
    glVertex2i(pow(19.0,2.0), pow(7.0,2.0));
    glVertex2i(pow(19.0,2.0),-(pow(7.0, 2.0)));
    glVertex2i(pow(23.0,2.0),-(pow(7.0, 2.0)));
    glVertex2i(pow(23.0,2.0),pow(7.0,2.0 ));
    glEnd();
    glPopMatrix();



    Rect r;
    r.bot = pow(20.0,2.0);
    r.left = pow(13.0,2.0);
    r.center = 0.0;

    clock_gettime(CLOCK_REALTIME, &ftimeEnd);
    t += timeDiff(&ftimeStart, &ftimeEnd);
    ggprint8b(&r, 16, 0x00ff0000, "Box with pow");
    ggprint8b(&r, 16, 0x00ff0000, "%lf",  t );
}

void drawDatBox2()
{
    static double t = 0.0;
    struct timespec ftimeStart, ftimeEnd;
    clock_gettime(CLOCK_REALTIME, &ftimeStart);
// -------^^ setting up clock time again ^^ ---------
    glColor3f(0.5, 0.01, 0.01);
    glPushMatrix();
    glTranslatef(-(14*14), (18*18), 0.0);
//Start the box
    glBegin(GL_QUADS);
    glVertex2i((17*17), (7*7));
    glVertex2i((17*17),-(7*7));
    glVertex2i((21*21),-(7*7));
    glVertex2i((21*21), (7*7));
    glEnd();
    glPopMatrix();

    Rect r;
    r.bot = (18*18);
    r.left = (13*13);
    r.center = 0.0;

    clock_gettime(CLOCK_REALTIME, &ftimeEnd);
    t+= timeDiff(&ftimeStart, &ftimeEnd);
// increment the total time and display
    ggprint8b(&r, 16, 0x00aa00aa, "%lf", t);
    ggprint8b(&r, 16, 0x00aa00aa, "Box w/o pow");


}
