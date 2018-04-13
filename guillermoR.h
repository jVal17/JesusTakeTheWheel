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
#include "img.h"
using namespace std;

typedef float Flt;
typedef float Vec[3];

//-----------------------------------------------------------------------------
//Setup timers
extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
//-----------------------------------------------------------------------------


void drawBox(float x, float y, int s); 
void moveBox(float x, float y); 
void renderMainCar(int s, float x, float y);
void renderEnemyCar(int s, float x, float y);
void generateTextures();
void initImages();
void totalTimeFunction();

#endif
