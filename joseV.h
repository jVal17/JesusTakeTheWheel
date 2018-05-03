// Jose Valenzuela
// Header file

#ifndef JOSE_V
#define JOSE_V
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
#include "guillermoR.h"
//#include "timers.cpp"
using namespace std;


//-----------------------------------------------------------------------------
//Setup timers
extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
//-----------------------------------------------------------------------------
extern float scrSpd;
extern float xres;
extern float yres;
void moveCrate(float src);
void spawnCrate();
void colWithPowerUP();
void renderPlowOnCar();

void renderCrate();
void generatePowerUpTextures();
void initPowerUpImages();
void pauseGame(float y[]); 
int clock_gettime(clockid_t clk_id, struct timespect *tp);
void example();
#endif
