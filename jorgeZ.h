// Jorge Zuniga
// Header file

#ifndef JORGE_Z
#define JORGE_Z

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "fonts.h"
#include <ctime> //-----
#include "guillermoR.h" //-----

//-----------------------------------------------------------------------------
//Setup of timers
const double OOBILLION = 1.0 / 1e9;
extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
//-----------------------------------------------------------------------------


using namespace std;

void screenPrint();
void GameOverScore();
void GameOverLevel();
void checkpoint(int, int &);
void createTextures();
void imageTexturing();
void pointTracker();
void levelTracker();
void finalScoreTracker();
void finalLevelTracker();
void velocityMod(float, float &, bool &, bool &);
void clearScore(int );
void clearLevel(int );

//void pauseTimer(bool&);
//void function1();
//void function2();


#endif
