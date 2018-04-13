//Edited by: Guillermo, Alec, Jorge Z, Ian and Jose V. 
//program: srcfile.cpp
//author:  Gordon Griesel
//date:    2017 - 2018
//
//The position of the background QUAD does not change.
//Just the texture coordinates change.
//In this example, only the x coordinates change.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <math.h>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include </usr/include/AL/alut.h>
#include "fonts.h"
#include "guillermoR.h"
#include "ianT.h"
#include "jorgeZ.h"
#include "joseV.h"
#include "alecS.h"
using namespace std;

GLuint backTexture;


Image img[1] = {
	"./Sprites/road2.jpeg"
};

class Texture {
	public:
		Image *backImage;
		//GLuint backTexture;
		float xc[2];
		float yc[2];
};

class Car {
	public:
		Vec pos;
		int dir[4];
	public:
		Car() {
		}
};


class Global {
	public:
		int xres, yres, level;
		float fyres;
		bool pause;
		GLuint carTexture;
		GLuint silhouetteTexture;
		Texture tex;
		float scrSpd;
		char keys[65536];

		Global() {
			xres=256, yres=1024, fyres = yres;
			pause=false;
			scrSpd = .01;
			level = 0;
			memset(keys, 0, 10000);
		}
} g;

class Game {
	public:
		Car mainCar, enemyCar[2];

		int carSize;
		int totalEnemyCars;
		int enemySideSpawn;
	public:
		Game() {
			mainCar.pos[0]= 206.0;
			mainCar.pos[1]= 512.0;
			for(int i=0; i < 2; i++) {
				enemySideSpawn = rand() % 2;
				if (enemySideSpawn)
					enemyCar[i].pos[0]= 180.0;
				else
					enemyCar[i].pos[0]= 340.0;
			}
			enemyCar[0].pos[1]= g.fyres;
			enemyCar[1].pos[1]= g.fyres+(g.fyres/2.0);
			carSize = 50;
			totalEnemyCars = 2;
		}

} ga;

bool inMainMenu = true;
bool inGame = false;
bool inPauseMenu = false;
int menuPosition = 1;

class X11_wrapper {
	private:
		Display *dpy;
		Window win;
		GLXContext glc;
		//GC gc;
	public:
		X11_wrapper() {
			GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
			//GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, None };
			setup_screen_res(512, 1024);//------------------------------------------------------------------------
			dpy = XOpenDisplay(NULL);
			if(dpy == NULL) {
				printf("\n\tcannot connect to X server\n\n");
				exit(EXIT_FAILURE);
			}
			Window root = DefaultRootWindow(dpy);
			XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
			if(vi == NULL) {
				printf("\n\tno appropriate visual found\n\n");
				exit(EXIT_FAILURE);
			} 
			Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
			XSetWindowAttributes swa;
			swa.colormap = cmap;
			swa.event_mask =
				ExposureMask | KeyPressMask | KeyReleaseMask | PointerMotionMask |
				ButtonPressMask | ButtonReleaseMask |
				StructureNotifyMask | SubstructureNotifyMask;
			win = XCreateWindow(dpy, root, 0, 0, g.xres, g.yres, 0,
					vi->depth, InputOutput, vi->visual,
					CWColormap | CWEventMask, &swa);
			set_title();
			glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
			glXMakeCurrent(dpy, win, glc);
		}
		void cleanupXWindows() {
			XDestroyWindow(dpy, win);
			XCloseDisplay(dpy);
		}
		void setup_screen_res(const int w, const int h) {
			g.xres = w;
			g.yres = h;
		}
		void reshape_window(int width, int height) {
			//window has been resized.
			setup_screen_res(width, height);
			glViewport(0, 0, (GLint)width, (GLint)height);
			glMatrixMode(GL_PROJECTION); glLoadIdentity();
			glMatrixMode(GL_MODELVIEW); glLoadIdentity();
			glOrtho(0, g.xres, 0, g.yres, -1, 1);
			set_title();
		}
		void set_title() {
			//Set the window title bar.
			XMapWindow(dpy, win);
			XStoreName(dpy, win, "scrolling background (seamless)");
		}
		bool getXPending() {
			return XPending(dpy);
		}
		XEvent getXNextEvent() {
			XEvent e;
			XNextEvent(dpy, &e);
			return e;
		}
		void swapBuffers() {
			glXSwapBuffers(dpy, win);
		}
		/*
		   void drawString(int x, int y, const char *text) {	//------------------------------------------------------------------
		   XDrawString(dpy, win, gc, x, y, text, strlen(text));
		   }
		 */
		void check_resize(XEvent *e) {
			//The ConfigureNotify is sent by the
			//server if the window is resized.
			if (e->type != ConfigureNotify)
				return;
			XConfigureEvent xce = e->xconfigure;
			if (xce.width != g.xres || xce.height != g.yres) {
				//Window size did change.
				reshape_window(xce.width, xce.height);
			}
		}
} x11;

void init_opengl(void);
void check_mouse(XEvent *e);
int check_keys(XEvent *e);
void physics(void);
void render(void);


//===========================================================================
//===========================================================================
int main()
{
	init_opengl();
	int done=0;
	while (!done) {
		while (x11.getXPending()) {
			XEvent e = x11.getXNextEvent();
			x11.check_resize(&e);
			check_mouse(&e);
			done = check_keys(&e);
		}
		physics();
		render();
		x11.swapBuffers();
	}
	return 0;
}

void init_opengl(void)
{
	//OpenGL initialization
	glViewport(0, 0, g.xres, g.yres);
	//Initialize matrices
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	//This sets 2D mode (no perspective)
	glOrtho(0, g.xres, 0, g.yres, -1, 1); // g.xres and g.yres-------------------------------------
	//Clear the screen
	glClearColor(1.0, 1.0, 1.0, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT);
	//Do this to allow texture maps
	glEnable(GL_TEXTURE_2D);
	initialize_fonts();
	//
	//load the images file into a ppm structure.
	//
	g.tex.backImage = &img[0];
	//create opengl texture elements
	glGenTextures(1, &backTexture);
	generateTextures(); 


	//glGenTextures(1, &g.carTexture);
	//glGenTextures(1, &g.silhouetteTexture);
	//-----------------------------------------------------------------------------------
	int w =  g.tex.backImage->width; //grabs a set number of pixels and scales them---------------------------------
	int h =  g.tex.backImage->height; //grabs a set number of pixels and scales them-----------------------------------
	glBindTexture(GL_TEXTURE_2D, backTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, g.tex.backImage->data);

	//----------------------------------------------------------
	//----------Messes with image ratios------------------------
	//----------------------------------------------------------
	g.tex.xc[0] = 1.0;
	g.tex.xc[1] = 0.0; //.25
	g.tex.yc[0] = 0.0;
	g.tex.yc[1] = 1.0;
	//----------------------------------------------------------
	initImages();
}

void check_mouse(XEvent *e)
{
	//Did the mouse move?
	//Was a mouse button clicked?
	static int savex = 0;
	static int savey = 0;
	//
	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button is down
		}
		if (e->xbutton.button==3) {
			//Right button is down
		}
	}
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
		//Mouse moved
		savex = e->xbutton.x;
		savey = e->xbutton.y;
	}
}

int check_keys(XEvent *e)
{
	int key = XLookupKeysym(&e->xkey, 0);
	//Was there input from the keyboard?
	if (e->type == KeyPress) {
		if (key == XK_Escape && !inGame) {
			return 1;
		}
		if (key == XK_Escape && inGame) {
			inGame = false;
			inPauseMenu = true;
		}
		if (key == XK_p) {
			if (g.pause)
				g.pause = false;
			else
				g.pause = true;
		}
		if (inMainMenu) {
			if (key == XK_Return) {
				if (menuPosition == 1) {
					inMainMenu = false;
					inGame = true;
				}
			} else if (key == XK_Down || key == XK_s) {
				if (menuPosition != 2) {
					menuPosition++;
				}
			} else if (key == XK_Up || key == XK_w) {
				if (menuPosition != 1) {
					menuPosition--;
				}
			}
		}
		if (inPauseMenu) {
			if (key == XK_Return) {
				if (menuPosition == 1) {
					inPauseMenu = false;
					inGame = true;
				} else if (menuPosition == 4) {
					return 1;
				}
			} else if (key == XK_Down || key == XK_s) {
				if (menuPosition != 4) {
					menuPosition++;
				}
			} else if (key == XK_Up || key == XK_w) {
				if (menuPosition != 1) {
					menuPosition--;
				}
			}
		}

	}
	if (e->type == KeyRelease) {
		g.keys[key]=0;
		return 0;
	}
	g.keys[key]=1;
	return 0;
}

void physics()
{
	if(inGame) {
		if(g.pause){		
			main();
		}
		//move the background
		g.tex.yc[0] -= g.scrSpd;
		g.tex.yc[1] -= g.scrSpd;

		g.level = checkpoint(g.scrSpd);
		ga.enemyCar[0].pos[1] -= (g.scrSpd*600.0);
		ga.enemyCar[1].pos[1] -= (g.scrSpd*600.0);

		for(int i = 0; i < ga.totalEnemyCars; i++){
			if (ga.enemyCar[i].pos[1]-75.0 < ga.mainCar.pos[1] && 
					ga.enemyCar[i].pos[1]+75.0 > ga.mainCar.pos[1] &&
					ga.enemyCar[i].pos[0]-30.0 < ga.mainCar.pos[0] &&
					ga.enemyCar[i].pos[0]+30.0 > ga.mainCar.pos[0]
			){ 
				cout << "You have crashed. Game has reset" << endl;
				resetGame(g.scrSpd, ga.mainCar.pos[0],	ga.mainCar.pos[1],	
				ga.enemyCar[0].pos[0], ga.enemyCar[0].pos[1], ga.enemyCar[1].pos[1],
				ga.enemyCar[1].pos[0], g.fyres);	
			}
		}
		if (ga.enemyCar[0].pos[1] < 0.0) {
			ga.enemyCar[0].pos[1] = g.fyres+40.0;
			ga.enemySideSpawn = rand() % 2;
			if (ga.enemySideSpawn)
				ga.enemyCar[0].pos[0] = 180.0;
			else
				ga.enemyCar[0].pos[0] = 340.0;

		}
		if (ga.enemyCar[1].pos[1] < 0.0) {
			ga.enemyCar[1].pos[1] = ga.enemyCar[0].pos[1]+(g.fyres/2.0);
			ga.enemySideSpawn = rand() % 2;
			if (ga.enemySideSpawn)
				ga.enemyCar[1].pos[0] = 180.0;
			else
				ga.enemyCar[1].pos[0] = 340.0;

		}

		//moves main car using w,a,s,d keys
		if (g.keys[XK_w]) {
			ga.mainCar.pos[1] += 8;
			if (ga.mainCar.pos[1] > g.fyres-40.0)
				ga.mainCar.pos[1] = g.fyres-40.0;
		}
		if (g.keys[XK_d]) {
			ga.mainCar.pos[0] += 8;
			if (ga.mainCar.pos[0] > 395.0)
				ga.mainCar.pos[0] = 395.0;
		}
		if (g.keys[XK_a]) {
			ga.mainCar.pos[0] -= 8;
			if (ga.mainCar.pos[0] < 118.0)
				ga.mainCar.pos[0] = 118.0;
		}
		if (g.keys[XK_s]) {
			ga.mainCar.pos[1] -= 8;
			if (ga.mainCar.pos[1] < 40.0)
				ga.mainCar.pos[1] = 40.0;
		}
	}
}


void render()
{
	glClearColor(0.9294, 0.788, 0.686, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
	if (inMainMenu) {
		mainMenu(g.xres, g.yres);
	} else if (inPauseMenu) {
		pauseMenu(g.xres, g.yres);
	} else if (inGame) {
		glColor3f(1.0, 1.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, backTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(g.tex.xc[0], g.tex.yc[1]); glVertex2i(100, 0);
		glTexCoord2f(g.tex.xc[0], g.tex.yc[0]); glVertex2i(100, g.yres);
		glTexCoord2f(g.tex.xc[1], g.tex.yc[0]); glVertex2i(g.xres - 100, g.yres);
		glTexCoord2f(g.tex.xc[1], g.tex.yc[1]); glVertex2i(g.xres - 100, 0);
		glEnd();  

		//---------------------------------------------------------------------------- 
		//car texture
		renderMainCar(ga.carSize, ga.mainCar.pos[0], ga.mainCar.pos[1]);
		renderAudi(ga.carSize, ga.enemyCar[0].pos[0], ga.enemyCar[0].pos[1]);
		renderMiniVan(ga.carSize, ga.enemyCar[1].pos[0], ga.enemyCar[1].pos[1]);
		//cout << "x: " << ga.car.pos[0] << "y: " << ga.car.pos[1] << endl;
		//screenPrint();	
		renderText();
		//printText();
		function1();
		//function2();
		//drawDatBox1();
		//drawDatBox2();
		//totalTimeFunction();
	}
}














