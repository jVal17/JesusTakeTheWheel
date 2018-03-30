//Guillermo Ramirez
//Seperate file for Guillermo Ramirez

#include "guillermoR.h"

//Function is found in the bottom of render() in our main file, "srcfile.cpp".

Image car[1] = {
	"./Sprites/Car.png"
};

class carTexture {
	public: 
		GLuint carTexture;
		GLuint silhouetteTexture;
} ct;

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


void initCar() {
	glGenTextures(1, &ct.carTexture);
        glGenTextures(1, &ct.silhouetteTexture);
	//car
	int w = car[0].width;
	int h = car[0].height;

	glBindTexture(GL_TEXTURE_2D, ct.carTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, car[0].data);

	//silhouette
	//
	glBindTexture(GL_TEXTURE_2D, ct.silhouetteTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	unsigned char *silhouetteData = buildAlphaData(&car[0]);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	free(silhouetteData);	
}

void renderCar(int s, float x, float y) {
	glPushMatrix();
	glTranslatef(x, y, 0);
	glBindTexture(GL_TEXTURE_2D, ct.silhouetteTexture);
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

