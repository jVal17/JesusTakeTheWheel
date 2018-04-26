// Jorge Zuniga
// My changes

#include "jorgeZ.h"
//#include "ianT.h"
#include <ctime>
#include <iostream>

using namespace std;
double durationPaused = 0.0;

void screenPrint () 
{
    Rect r;
    r.bot = 500;
    r.left = 10;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff0000, "Changes made");
    ggprint8b(&r, 16, 0x00ff0000, "by Jorge Zuniga");
    glEnd();
}


int checkpoint ()
{
    static int level = 0;
    return level++;
}




