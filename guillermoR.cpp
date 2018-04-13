//Guillermo Ramirez
//Seperate file for Guillermo Ramirez

#include "guillermoR.h"

//Function is found in the bottom of render() in our main file, "srcfile.cpp".

Image mainCarImage = "./Sprites/Car.png";
Image enemyCarImage = "./Sprites/Audi.png";

GLuint mainCarTexture;
GLuint enemyCarTexture;
GLuint silhouetteMainCarTexture;
GLuint silhouetteEnemyCarTexture;

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
	glGenTextures(1, &enemyCarTexture);
	glGenTextures(1, &silhouetteMainCarTexture);
	glGenTextures(1, &silhouetteEnemyCarTexture);
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

	//Init enemy car Image
	w = enemyCarImage.width;
        h = enemyCarImage.height;

	glBindTexture(GL_TEXTURE_2D, enemyCarTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, enemyCarImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteEnemyCarTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        unsigned char *silhouetteData2 = buildAlphaData(&enemyCarImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData2);
	free(silhouetteData2);		
}

void renderMainCar(int s, float x, float y) {
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

void renderEnemyCar(int s, float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glBindTexture(GL_TEXTURE_2D, silhouetteEnemyCarTexture);
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

