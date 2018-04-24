//Guillermo Ramirez
//Seperate file for Guillermo Ramirez

#include "guillermoR.h"

float fxres, fyres;
static struct timespec ftimeStart, ftimeEnd;

Image mainCarImage = "./Sprites/Car.png";
Image audiImage = "./Sprites/Audi.png";
Image miniVanImage = "./Sprites/Mini_van.png";
Image heartImage = "./Sprites/heart.png";
//Image transparentImage = "./Sprites/transparent.png";

GLuint mainCarTexture;
GLuint audiTexture;
GLuint miniVanTexture;
GLuint heartTexture;
//GLuint transparentTexture;
GLuint silhouetteMainCarTexture;
GLuint silhouetteAudiTexture;
GLuint silhouetteMiniVanTexture;
GLuint silhouetteHeartTexture;
//GLuint silhouetteTransparentTexture;

class Car {
	public:
		Vec pos;
		bool invinc;
		Car() {
			invinc = false;
		}
};

class Heart {
	public:
		int size;
		Vec pos;
		Heart() {
			size = 15;
		}
};

void getfxres(float x){
	fxres = x;
}

void getfyres(float y){
	fyres = y;
}

class Game {
	public:
		Car mainCar, enemyCar[2];
		Heart heart[3];
		int numHearts;
		int carSize;
		int totalEnemyCars;
		int carSpawnPos;
		bool firstInvinc;
		bool firstBlink;
		bool blinkReset;
		bool blink;
		float t1;
		double invincTimer;
		double invincDurationTimer;
		double blinkTimer;
		Vec tmpMainPos, tmpMainPos2;

		Game() {

			for(int j = 0; j < 3; j++){
				heart[j].pos[0]= (fxres*1.7) + (j*30);
				heart[j].pos[1]= fyres-20.0;
			}
			mainCar.pos[0]= fxres;
			mainCar.pos[1]= 80.0;
			for(int i=0; i < 2; i++) {
				carSpawnPos = rand() % (X_MAX - X_MIN) + X_MIN;
				enemyCar[i].pos[0] = carSpawnPos;
			}
			enemyCar[0].pos[1]= fyres;
			enemyCar[1].pos[1]= fyres+(fyres/2.0);
			carSize = 50;
			totalEnemyCars = 2;
			numHearts = 2;
			firstInvinc = true;
			firstBlink = true;
			invincTimer = 0.0;
			blinkTimer = 0.0;
			blinkReset = true;
			blink = false;
			//isBlinking = false;
			t1=.08;
			invincDurationTimer=1.5;
			tmpMainPos[0]=-500.0;
		}

} ga;

//Function is found in the bottom of render() in our main file, "srcfile.cpp".
void moveEnemyCars(float scr){
	ga.enemyCar[0].pos[1] -= (scr*600.0);
	ga.enemyCar[1].pos[1] -= (scr*600.0);	
}

void checkCollisions(float scr){
	//if (!ga.blinkReset)
	ga.tmpMainPos2[0] = ga.mainCar.pos[0];
	checkInvincOutside();	
	//if (ga.isBlinking)
	//	cout << "Car is in invincibility mode" << endl;
	//if (!ga.mainCar.invinc)
	//	cout << "Not in invincibility mode" << endl;
	for(int i = 0; i < ga.totalEnemyCars; i++){
		if (ga.enemyCar[i].pos[1]-75.0 < ga.mainCar.pos[1] && 
				ga.enemyCar[i].pos[1]+75.0 > ga.mainCar.pos[1] &&
				ga.enemyCar[i].pos[0]-30.0 < ga.mainCar.pos[0] &&
				ga.enemyCar[i].pos[0]+30.0 > ga.mainCar.pos[0]
		   ){
			if(!ga.mainCar.invinc){
				ga.heart[ga.numHearts].pos[0]= -50.0;
				ga.numHearts-=1;
				ga.mainCar.invinc = true;
			}
			//	ga.blinkReset=false;
			carInvincibility();
			//blinkCar();
			//blinkTimer();
			if (ga.numHearts < 0) {
				cout << "You have crashed. Game has reset" << endl;
				resetGame(scr, ga.mainCar.pos[0], ga.mainCar.pos[1],	
						ga.enemyCar[0].pos[0], ga.enemyCar[0].pos[1], ga.enemyCar[1].pos[1],
						ga.enemyCar[1].pos[0], fxres, fyres);	
			}
		}
	}

}


void carInvincibility(){
	if (ga.mainCar.invinc) 
		if (ga.invincTimer == 0.0)
			if (ga.firstInvinc) 
				clock_gettime(CLOCK_REALTIME, &ftimeStart);
	ga.firstInvinc = false;
	clock_gettime(CLOCK_REALTIME, &ftimeEnd);	
	ga.invincTimer = timeDiff(&ftimeStart, &ftimeEnd);

	if (ga.invincTimer > ga.invincDurationTimer && ga.mainCar.invinc) {
		// cout << "invincibility mode has ended" << endl;
		ga.invincTimer = 0.0;
		ga.mainCar.invinc = false;
		ga.firstInvinc=true;
	} 
}

void checkInvincOutside(){
	if (ga.mainCar.invinc && ga.invincTimer > 0.0){
		clock_gettime(CLOCK_REALTIME, &ftimeEnd);	
		ga.invincTimer = timeDiff(&ftimeStart, &ftimeEnd);
		//float t1=0.33;
		if(ga.invincTimer > ga.t1){
			//	ga.isBlinking = true;
			//ga.tmpMainPos2[0] = ga.mainCar.pos[0];
			//cout << ga.tmpMainPos[0] << endl;
			ga.t1 += 0.08;
			blink();
			/*	if (!ga.blink)
				ga.mainCar.pos[0] = -100.0;
				else 
				ga.mainCar.pos[0] = 
			 */		

		}
		//cout << ga.invincTimer << endl;
	}
	if (ga.invincTimer > ga.invincDurationTimer && ga.mainCar.invinc) {
		//cout << "Stopped Blinking" << endl;
		ga.invincTimer = 0.0;
		ga.mainCar.invinc = false;
		ga.firstInvinc=true;
		ga.t1=0.08;
		//ga.isBlinking = false;
	}
}
void blink(){
	if (!ga.blink){
		ga.blink = true;
	}
	else
		ga.blink = false;
}
/*
   void blinkCar(){
   if (ga.firstBlink) 
   clock_gettime(CLOCK_REALTIME, &fblinkStart);
   ga.firstBlink = false;
   clock_gettime(CLOCK_REALTIME, &fblinkEnd);	
   ga.blinkTimer = timeDiff(&fblinkStart, &fblinkEnd);
   cout << ga.blinkTimer << endl;
   if (ga.blinkTimer < ga.invincDurationTimer && ga.mainCar.invinc) {
   cout << "car blinking" << endl;
   }
   if (ga.blinkTimer > ga.invincDurationTimer && ga.mainCar.invinc) {
   ga.blinkTimer = 0.0;
//ga.mainCar.invinc = false;
ga.firstBlink=true;
}
}
 */
/*
   void invincibilityTimer(){
   clock_gettime(CLOCK_REALTIME, &ftimeEnd);	
   ga.timer = timeDiff(&ftimeStart, &ftimeEnd);
   cout << ga.timer << endl;
   if (ga.timer > ga.invincDurationTimer && ga.mainCar.invinc) {
   cout << "invincibility mode has ended" << endl;
   ga.timer = 0.0;
   ga.mainCar.invinc = false;
   ga.firstInvinc=true;
   }
   }
 */

void spawnEnemyCars(float yres){
	if (ga.enemyCar[0].pos[1] < 0.0) {
		ga.carSpawnPos = rand() % (X_MAX-X_MIN) + X_MIN;
		ga.enemyCar[0].pos[0] = ga.carSpawnPos;
		ga.enemyCar[0].pos[1] = yres+40.0;
	}
	if (ga.enemyCar[1].pos[1] < 0.0) {
		ga.enemyCar[1].pos[1] = ga.enemyCar[0].pos[1]+(yres/2.0);
		ga.carSpawnPos = rand() % (X_MAX-X_MIN) + X_MIN;
		ga.enemyCar[1].pos[0] = ga.carSpawnPos;
	}	
}

void wMovement(float yres){
	ga.mainCar.pos[1] += 8;
	if (ga.mainCar.pos[1] > yres-40.0)
		ga.mainCar.pos[1] = yres-40.0;
}

void dMovement(){
	ga.mainCar.pos[0] += 8;
	if (ga.mainCar.pos[0] > 395.0)
		ga.mainCar.pos[0] = 395.0;
}

void aMovement(){
	ga.mainCar.pos[0] -= 8;
	if (ga.mainCar.pos[0] < 118.0)
		ga.mainCar.pos[0] = 118.0;
}

void sMovement(){
	ga.mainCar.pos[1] -= 8;
	if (ga.mainCar.pos[1] < 40.0)
		ga.mainCar.pos[1] = 40.0;

}

void resetGame(float &scr, float &mcX, float &mcY, float &ecX, float &ecY,
		float &ec2X, float &ec2Y, float xres, float yres){
	int randnum = rand() % 2;
	scr = .01;
	mcX = xres;
	mcY = 80.0;
	ecY = yres;
	ec2Y = ecY+(yres/2.0);
	if(randnum)
		ecX = 180.0;
	else 
		ecX = 340.0;
	randnum = rand() % 2;
	if(randnum)
		ec2X = 180.0;
	else 
		ec2X = 340.0;
	for (int j = 0; j < 3; j++) {
		ga.heart[j].pos[0]= (fxres*1.7) + (j*30);
		ga.heart[j].pos[1]= fyres-20.0;
	}
	ga.numHearts = 2;
	//	ga.blinkReset=true;
}

unsigned char *buildAlphaData(Image *img)
{
	//add 4th component to RGB stream...
	int i;
	unsigned char *newdata, *ptr;
	unsigned char *data = (unsigned char *)img->data;
	newdata = (unsigned char *)malloc(img->width * img->height * 4);
	ptr = newdata;
	unsigned char a,b,c;
	//use the first pixel in the image as the transparent color.
	unsigned char t0 = *(data+0);
	unsigned char t1 = *(data+1);
	unsigned char t2 = *(data+2);
	for (i=0; i<img->width * img->height * 3; i+=3) {
		a = *(data+0);
		b = *(data+1);
		c = *(data+2);
		*(ptr+0) = a;
		*(ptr+1) = b;
		*(ptr+2) = c;
		*(ptr+3) = 1;
		if (a==t0 && b==t1 && c==t2)
			*(ptr+3) = 0;
		//-----------------------------------------------
		ptr += 4;
		data += 3;
	}
	return newdata;
}

void generateTextures(){
	glGenTextures(1, &mainCarTexture);
	glGenTextures(1, &audiTexture);
	glGenTextures(1, &miniVanTexture);
	glGenTextures(1, &silhouetteMainCarTexture);
	glGenTextures(1, &silhouetteAudiTexture);
	glGenTextures(1, &silhouetteMiniVanTexture);
}

void initImages() {
	//Initialize main car Image
	int w = mainCarImage.width;
	int h = mainCarImage.height;

	glBindTexture(GL_TEXTURE_2D, mainCarTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, mainCarImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteMainCarTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData = buildAlphaData(&mainCarImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	free(silhouetteData);

	//audi Image
	w = audiImage.width;
	h = audiImage.height;

	glBindTexture(GL_TEXTURE_2D, audiTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, audiImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteAudiTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData2 = buildAlphaData(&audiImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData2);
	free(silhouetteData2);

	//Init enemy mini Van Image
	w = miniVanImage.width;
	h = miniVanImage.height;

	glBindTexture(GL_TEXTURE_2D, miniVanTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, miniVanImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteMiniVanTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData3 = buildAlphaData(&miniVanImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData3);
	free(silhouetteData3);

	//Init Heart
	w = heartImage.width;
	h = heartImage.height;

	glBindTexture(GL_TEXTURE_2D, heartTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, heartImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteHeartTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData4 = buildAlphaData(&heartImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData4);
	free(silhouetteData4);	

	/*
	//Init transparent Image
	w = transparentImage.width;
	h = transparentImage.height;

	glBindTexture(GL_TEXTURE_2D, transparentTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
	GL_RGB, GL_UNSIGNED_BYTE, transparentImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteTransparentTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData5 = buildAlphaData(&transparentImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData5);
	free(silhouetteData5);
	 */

}

void renderMainCar() {
	if (!ga.mainCar.invinc) {
		int s = ga.carSize;
		float x = ga.mainCar.pos[0];
		float y = ga.mainCar.pos[1];
		glPushMatrix();
		glTranslatef(x, y, 0);
		glBindTexture(GL_TEXTURE_2D, silhouetteMainCarTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255,255,255,255);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(-s,-s);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(-s, s);
		glTexCoord2f(1.0f, 0.0f); glVertex2i( s, s);
		glTexCoord2f(1.0f, 1.0f); glVertex2i( s,-s);
		glEnd();
		glPopMatrix();
	}

	if (ga.mainCar.invinc) {
		int s = ga.carSize;
		float x;
		if(ga.blink)
			x = ga.tmpMainPos[0];
		else
			x = ga.tmpMainPos2[0];
		float y = ga.mainCar.pos[1];
		glPushMatrix();
		glTranslatef(x, y, 0);
		glBindTexture(GL_TEXTURE_2D, silhouetteMainCarTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255,255,255,255);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(-s,-s);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(-s, s);
		glTexCoord2f(1.0f, 0.0f); glVertex2i( s, s);
		glTexCoord2f(1.0f, 1.0f); glVertex2i( s,-s);
		glEnd();
		glPopMatrix();
	}

}

void renderAudi() {
	int s = ga.carSize;
	float x = ga.enemyCar[0].pos[0];
	float y = ga.enemyCar[0].pos[1];
	glPushMatrix();
	glTranslatef(x, y, 0);
	glBindTexture(GL_TEXTURE_2D, silhouetteAudiTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(-s,-s);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-s, s);
	glTexCoord2f(1.0f, 0.0f); glVertex2i( s, s);
	glTexCoord2f(1.0f, 1.0f); glVertex2i( s,-s);
	glEnd();
	glPopMatrix();
}

void renderMiniVan() {
	int s = ga.carSize;
	float x = ga.enemyCar[1].pos[0];
	float y = ga.enemyCar[1].pos[1];
	glPushMatrix();
	glTranslatef(x, y, 0);
	glBindTexture(GL_TEXTURE_2D, silhouetteMiniVanTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(-s,-s);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-s, s);
	glTexCoord2f(1.0f, 0.0f); glVertex2i( s, s);
	glTexCoord2f(1.0f, 1.0f); glVertex2i( s,-s);
	glEnd();
	glPopMatrix();
}

void renderHeart() {
	for (int i = 0; i < 3; i++) {
		int s = ga.heart[i].size;
		float x = ga.heart[i].pos[0];
		float y = ga.heart[i].pos[1];
		glPushMatrix();
		glTranslatef(x, y, 0);
		glBindTexture(GL_TEXTURE_2D, silhouetteHeartTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255,255,255,255);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(-s,-s);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(-s, s);
		glTexCoord2f(1.0f, 0.0f); glVertex2i( s, s);
		glTexCoord2f(1.0f, 1.0f); glVertex2i( s,-s);
		glEnd();
		glPopMatrix();
	}
}


void totalTimeFunction()
{
	static double t = 0.0;
	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);
	int total = 0;
	Rect r;
	r.bot = 470;
	r.left = 215;
	r.center = 0;
	for (int i = 0; i < 10000; i++){
		total += i/2;
	}
	clock_gettime(CLOCK_REALTIME, &end);
	t += timeDiff(&start, &end);
	ggprint8b(&r, 16, 0xFFFF00, "%lf", t);
}

void drawBox(float x, float y, int s){
	glColor3f(0.0, 0.0, 0.0);
	glPushMatrix();
	glTranslatef(x, y, 0.0);
	glBegin(GL_QUADS);
	glVertex2i( -s,  -s);
	glVertex2i( -s,   s);
	glVertex2i(  s,   s);
	glVertex2i(  s,  -s);
	glEnd();
	glPopMatrix();
}

