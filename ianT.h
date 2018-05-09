#ifndef IAN_T
#define IAN_T
#include <fstream>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <X11/Xlib.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glx.h>
#include "fonts.h"
#include <ctime>

using namespace std;

extern double timeDiff(struct timespec *start, struct timespec *end);

extern bool inGame;
extern bool inMainMenu;
extern bool audio_on;
extern int menuPosition;

void renderText();
void mainMenu(const int, const int);
void pauseMenu(const int, const int);
void gameOverMenu(const int, const int);
void audioMenu(const int, const int);
void tutorial(const int, const int);
#endif
