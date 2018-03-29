// Alec Sherlock
// Header file

#ifndef ALEC_S
#define ALEC_S

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include <ctime>
#include <AL/al.h>
#include <AL/alc.h>
#include "fonts.h"

using namespace std;
//-------------------
extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
//-------------------------------------------------------------
void printText();
void drawDatBox1();
void drawDatBox2();
void initSounds();
void clearSounds();
void bringInSounds();
void play_sounds(int soundOption);
void play_sounds(int soundOption, int loop);
void play_sounds(int soundOption, char mute);

#endif
