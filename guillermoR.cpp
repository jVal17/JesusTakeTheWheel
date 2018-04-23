//Guillermo Ramirez
//Seperate file for Guillermo Ramirez

#include "guillermoR.h"

float fxres, fyres;

Image mainCarImage = "./Sprites/Car.png";
Image audiImage = "./Sprites/Audi.png";
Image miniVanImage = "./Sprites/Mini_van.png";

GLuint mainCarTexture;
GLuint audiTexture;
GLuint miniVanTexture;
GLuint silhouetteMainCarTexture;
GLuint silhouetteAudiTexture;
GLuint silhouetteMiniVanTexture;


class Car {
	public:
		Vec pos;
		int dir[4];
	public:
		Car() {
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

		int carSize;
		int totalEnemyCars;
		int carSpawnPos;
	public:
		Game() {
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
		}

} ga;

//Function is found in the bottom of render() in our main file, "srcfile.cpp".
void moveEnemyCars(float scr){
	ga.enemyCar[0].pos[1] -= (scr*600.0);
	ga.enemyCar[1].pos[1] -= (scr*600.0);	
}

void checkCollisions(float scr){
	for(int i = 0; i < ga.totalEnemyCars; i++){
		if (ga.enemyCar[i].pos[1]-75.0 < ga.mainCar.pos[1] && 
				ga.enemyCar[i].pos[1]+75.0 > ga.mainCar.pos[1] &&
				ga.enemyCar[i].pos[0]-30.0 < ga.mainCar.pos[0] &&
				ga.enemyCar[i].pos[0]+30.0 > ga.mainCar.pos[0]
		   ){ 
			cout << "You have crashed. Game has reset" << endl;
			resetGame(scr, ga.mainCar.pos[0],	ga.mainCar.pos[1],	
					ga.enemyCar[0].pos[0], ga.enemyCar[0].pos[1], ga.enemyCar[1].pos[1],
					ga.enemyCar[1].pos[0], fxres, fyres);	
		}
	}

}

void spawnEnemyCars(float yres){
	if (ga.enemyCar[0].pos[1] < 0.0) {
		ga.carSpawnPos = rand() % (X_MAX-X_MIN) + X_MIN;
		ga.enemyCar[0].pos[0] = ga.carSpawnPos;
		ga.enemyCar[0].pos[1] = yres+40.0;

		/*	if (ga.enemySideSpawn)
			ga.enemyCar[0].pos[0] = 180.0;
			else
			ga.enemyCar[0].pos[0] = 340.0;
		 */
	}
	if (ga.enemyCar[1].pos[1] < 0.0) {
		ga.enemyCar[1].pos[1] = ga.enemyCar[0].pos[1]+(yres/2.0);
		ga.carSpawnPos = rand() % (X_MAX-X_MIN) + X_MIN;
		ga.enemyCar[1].pos[0] = ga.carSpawnPos;
		/*	if (ga.enemySideSpawn)
			ga.enemyCar[1].pos[0] = 180.0;
			else
			ga.enemyCar[1].pos[0] = 340.0;
		 */
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
}

void renderMainCar() {
	int s = ga.carSize;
	int x = ga.mainCar.pos[0];
	int y = ga.mainCar.pos[1];
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

void renderAudi() {
	int s = ga.carSize;
	int x = ga.enemyCar[0].pos[0];
	int y = ga.enemyCar[0].pos[1];
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
	int x = ga.enemyCar[1].pos[0];
	int y = ga.enemyCar[1].pos[1];
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
	for(int i = 0; i < 10000; i++){
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

