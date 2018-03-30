// Jorge Zuniga
// My changes

#include "jorgeZ.h"
#include <ctime>
#include <iostream>

using namespace std;
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

//double pauseTimer()
//{

//}

int checkpoint (float &scrSpd)
{
    int i;
    static int level = 0;
    static double t = 0.0;
    static struct timespec ftimeStart, ftimeEnd;
    static double t2 = 10.0, setSpd = 0.01125;
    if(t == 0)
	clock_gettime(CLOCK_REALTIME, &ftimeStart);
    for ( i = 1; i < 100; i++){ 
	pow(i,2);
    }
    clock_gettime(CLOCK_REALTIME, &ftimeEnd);
    t = timeDiff(&ftimeStart, &ftimeEnd);

    if(t > t2 + 10){
	t2 += 10;
	setSpd += 0.0025;
    }
    if(t > t2){
	if(scrSpd < setSpd){
	    scrSpd += 0.000025;
	}
    }

//    cout << "scrSpd: " << scrSpd << endl;
    return level++;
    //ggprint8b(&r, 16, 0x00ff0000, "%f", t);
}

void function1 ()
{
    int i;
    static double t = 0.0;
    struct timespec ftimeStart, ftimeEnd;
    clock_gettime(CLOCK_REALTIME, &ftimeStart);

    for ( i = 1; i < 100; i++) 
	pow(i,2);

    Rect r;
    r.bot = 468;
    r.left = 10;
    r.center = 0;

    clock_gettime(CLOCK_REALTIME, &ftimeEnd);
    t += timeDiff(&ftimeStart, &ftimeEnd);

    ggprint8b(&r, 16, 0x00ff0000, "pow function");
    ggprint8b(&r, 16, 0x00ff0000, "%f", t);
}

void function2 ()
{
    int i;
    static double t = 0.0;
    struct timespec ftimeStart, ftimeEnd;
    clock_gettime(CLOCK_REALTIME, &ftimeStart);

    for ( i = 1; i < 100; i++) 
	sqrt(i); 


    Rect r;
    r.bot = 436;
    r.left = 10;
    r.center = 0;

    clock_gettime(CLOCK_REALTIME, &ftimeEnd);
    t += timeDiff(&ftimeStart, &ftimeEnd);

    ggprint8b(&r, 16, 0x00ff0000, "sqrt function");
    ggprint8b(&r, 16, 0x00ff0000, "%f", t);
}
