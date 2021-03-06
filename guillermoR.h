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
#include "time.h"
#include "iostream"
#include "img.h"
#include "joseV.h"
using namespace std;

#define X_MIN 140
#define X_MAX 370 

class Car {
	public:
		Vec pos;
		bool invinc;
		bool powerUp;
		bool carHit;
		Car() {
			invinc = false;
			powerUp = false;
			carHit = false;
		}
};

//extern Image image;
//-----------------------------------------------------------------------------
//Setup of timers
//const double OOBILLION = 1.0 / 1e9;
extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
//-----------------------------------------------------------------------------

typedef float Flt;
typedef float Vec[3];

//Setup timers
extern struct timespec timeStart, timeCurrent;
extern double timeDiff(struct timespec *start, struct timespec *end);
extern void timeCopy(struct timespec *dest, struct timespec *source);
unsigned char *buildAlphaData(Image *img);

extern bool gameOver;
void getEnemyCars(struct Car (&eCar)[3]);
void getfyres(float y);
void getfxres(float x);
void makeCar();
void drawBox(float x, float y, int s); 
void moveBox(float x, float y); 
void moveEnemyCars(float scr);
int checkCollisions(float scr, bool &, bool &);
void carInvincibility();
void blink();
void checkInvincOutside();
bool spawnEnemyCars(float yres);
void wMovement();
void dMovement();
void aMovement();
void sMovement();
void fixCarBoundaries();
void renderMainCar(bool, bool);
void renderAudi();
void renderTaxi();
void makeCar();
void renderMiniVan();
void renderHeart();
void renderLives();
void renderLivesFrame();
void renderMainMenu();
void renderGameOver();
void generateTextures();
void initImages();
void totalTimeFunction();
void getMainCarCoords(float (&M)[2]);
void fireAnimation();
void startFireTime();
void renderFire();
void startCountDownTimer();
void renderCountDown(bool &);
void countDownSetTrue(bool &);

//void increaseCarSpeedY(float enemy, float scr);
void resetGame(float &scr);
#endif
