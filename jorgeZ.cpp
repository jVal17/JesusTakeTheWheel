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

void pauseTimer(bool &inPauseMenu)
{
    static struct timespec ftimeStart, ftimeEnd, s;
    if(inPauseMenu)
    {
	//durationPaused = 0.0;
	clock_gettime(CLOCK_REALTIME, &ftimeStart);
	clock_gettime(CLOCK_REALTIME, &s);
	s.tv_sec = ftimeStart.tv_sec;
    }
	

    if(!inPauseMenu)
    {
	clock_gettime(CLOCK_REALTIME, &ftimeEnd);
	durationPaused = timeDiff(&ftimeStart, &ftimeEnd);
	cout << "Paused Time: " << durationPaused << endl;
	//cout <<  "ftimeEnd:" << ftimeEnd.tv_sec << endl; 
    }


    //return durationPaused;
}

int checkpoint (float &scrSpd)
{
    int i;
    static int level = 0;
    static double inGameTimer = 0.0;
    static struct timespec ftimeStart, ftimeEnd;
    static double t2 = 10.0;//, setSpd = 0.01125;

    if(inGameTimer == 0)
	clock_gettime(CLOCK_REALTIME, &ftimeStart);

    clock_gettime(CLOCK_REALTIME, &ftimeEnd);
    inGameTimer = timeDiff(&ftimeStart, &ftimeEnd);

    if(inGameTimer > t2){
	t2 += 10;
	//setSpd += 0.0025;
	//scrSpd += 0.000025; //added 3 more 0's
	scrSpd += 0.0025; //added 3 more 0's
	cout << "scrSpd: " << scrSpd << endl;
    }/*
	if(inGameTimer > t2){
	if(scrSpd < setSpd){
	scrSpd += 0.000025; //added 3 more 0's
	}
	}*/

    //cout << "duration paused:" << durationPaused << endl;
    cout << "in game timer(before): " << inGameTimer << endl;

    inGameTimer = inGameTimer - durationPaused;
    cout << "duration paused:" << durationPaused << endl;
    durationPaused = 0;

    cout << "in game timer(after): " << inGameTimer << endl;

    //cout << "scrSpd: " << scrSpd << endl;
    //cout << "In game timer: " << inGameTimer << endl;
    return level++;
    //ggprint8b(&r, 16, 0x00ff0000, "%f", t);
}

void timeDifference()
{


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
