// Guillermo Ramirez
// Header file

#ifndef GUILLERMO_R
#define GUILLERMO_R

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <cmath>
#include <ctime>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "fonts.h"
using namespace std;

//-----------------------------------------------------------------------------
//Setup timers
extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
//-----------------------------------------------------------------------------


void drawBox(float x, float y, float x2, float y2); 
void moveBox(float x, float y); 
void totalTimeFunction();

#endif
