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
#include "iostream"
using namespace std;

#define X_MIN 125
#define X_MAX 390 

typedef float Flt;
typedef float Vec[3];

//Setup timers
extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);


void getfyres(float y);
void getfxres(float x);
void drawBox(float x, float y, int s); 
void moveBox(float x, float y); 
void moveEnemyCars(float scr);
void checkCollisions(float scr);
void spawnEnemyCars(float yres);
void wMovement(float yres);
void dMovement();
void aMovement();
void sMovement();
void renderMainCar();
void renderAudi();
void renderMiniVan();
void renderHeart();
void generateTextures();
void initImages();
void totalTimeFunction();
//void increaseCarSpeedY(float enemy, float scr);
void resetGame(float &scr, float &mcX, float &mcY, float &ecX, float &ecY,
		float &ec2X, float &ec2Y, float xres, float yres);
#endif
