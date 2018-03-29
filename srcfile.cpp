//Edited by: Guillermo, Alec, Jorge Z, Ian and Jose V. 
//program: srcfile.cpp
//author:  Gordon Griesel
//date:    2017 - 2018
//
//The position of the background QUAD does not change.
//Just the texture coordinates change.
//In this example, only the x coordinates change.
//
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

typedef float Flt;
typedef float Vec[3];

class Image {
    public:
	int width, height;
	unsigned char *data;
	~Image() { delete [] data; }
	Image(const char *fname) {
	    if (fname[0] == '\0')
		return;
	    //printf("fname **%s**\n", fname);
	    char name[40];
	    strcpy(name, fname);
	    int slen = strlen(name);
	    name[slen-4] = '\0';
	    //printf("name **%s**\n", name);
	    char ppmname[80];
	    sprintf(ppmname,"%s.ppm", name);
	    //printf("ppmname **%s**\n", ppmname);
	    char ts[100];
	    //system("convert eball.jpg eball.ppm");
	    sprintf(ts, "convert %s %s", fname, ppmname);
	    system(ts);
	    //sprintf(ts, "%s", name);
	    FILE *fpi = fopen(ppmname, "r");
	    if (fpi) {
		char line[200];
		fgets(line, 200, fpi);
		fgets(line, 200, fpi);
		while (line[0] == '#')
		    fgets(line, 200, fpi);
		sscanf(line, "%i %i", &width, &height);
		fgets(line, 200, fpi);
		//get pixel data
		int n = width * height * 3;			
		data = new unsigned char[n];			
		for (int i=0; i<n; i++)
		    data[i] = fgetc(fpi);
		fclose(fpi);
	    } else {
		printf("ERROR opening image: %s\n",ppmname);
		exit(0);
	    }
	    unlink(ppmname);
	}
};
Image img[2] = {
	"./Sprites/road2.jpeg", 
	"./Sprites/Car.png"
};

class Texture {
    public:
	Image *backImage;
	GLuint backTexture;
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
	bool pause;
	GLuint carTexture;
	GLuint silhouetteTexture;
	Texture tex;
	float scrSpd;
	char keys[65536];

	Global() {
	    xres=256, yres=1024;
	    pause=false;
	    scrSpd = .01;
	    level = 0;
            memset(keys, 0, 10000);
	}
} g;

class Game {
    public:
	Car car;
	int ncars;
	int carSize;
    public:
	Game() {
	    car.pos[0]= 206.0;
	    car.pos[1]= 512.0;
	    carSize = 50;
	    ncars = 1;
	}

} ga;

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
    glGenTextures(1, &g.tex.backTexture);
    glGenTextures(1, &g.carTexture);
    glGenTextures(1, &g.silhouetteTexture);
    //-----------------------------------------------------------------------------------
    int w =  g.tex.backImage->width; //grabs a set number of pixels and scales them---------------------------------
    int h =  g.tex.backImage->height; //grabs a set number of pixels and scales them-----------------------------------
    glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
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
    //car
    w = img[1].width;
    h = img[1].height;

    glBindTexture(GL_TEXTURE_2D, g.carTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
	    GL_RGB, GL_UNSIGNED_BYTE, img[1].data);

    //silhouette
        //
        glBindTexture(GL_TEXTURE_2D, g.silhouetteTexture);
        //
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
        //
        //must build a new set of data...
        unsigned char *silhouetteData = buildAlphaData(&img[1]);
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
                                                        GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
        free(silhouetteData); 
    
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
	if (key == XK_Escape) {
	    return 1;
	}
	if (key == XK_p) {
	    if (g.pause)
		g.pause = false;
	    else
		g.pause = true;
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
    if(g.pause){		
	main();
    }
    //move the background
    g.tex.yc[0] -= g.scrSpd;
    g.tex.yc[1] -= g.scrSpd;

    g.level = checkpoint(g.scrSpd);

    //moves main car using w,a,s,d keys
    if (g.keys[XK_w])
	ga.car.pos[1] += 8;
    if (g.keys[XK_d]) 
	ga.car.pos[0] += 8;
    if (g.keys[XK_a]) 
	ga.car.pos[0] -= 8;
    if (g.keys[XK_s])
	ga.car.pos[1] -= 8;

}


void render()
{
    int s = ga.carSize;
    glClearColor(0.9294, 0.788, 0.686, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glBindTexture(GL_TEXTURE_2D, g.tex.backTexture);
    glBegin(GL_QUADS);
    glTexCoord2f(g.tex.xc[0], g.tex.yc[1]); glVertex2i(100, 0);
    glTexCoord2f(g.tex.xc[0], g.tex.yc[0]); glVertex2i(100, g.yres);
    glTexCoord2f(g.tex.xc[1], g.tex.yc[0]); glVertex2i(g.xres - 100, g.yres);
    glTexCoord2f(g.tex.xc[1], g.tex.yc[1]); glVertex2i(g.xres - 100, 0);
    glEnd();  
     
    //car texture
     glPushMatrix();
                glTranslatef(ga.car.pos[0], ga.car.pos[1], 0);
                //if (!g.silhouette) {
                //        glBindTexture(GL_TEXTURE_2D, g.bigfootTexture);
                //} else {
                    //    glBindTexture(GL_TEXTURE_2D, g.carTexture);
                        glBindTexture(GL_TEXTURE_2D, g.silhouetteTexture);
                        glEnable(GL_ALPHA_TEST);
                        glAlphaFunc(GL_GREATER, 0.0f);
                        glColor4ub(255,255,255,255);
                //}
                glBegin(GL_QUADS);
                       // if (bigfoot.vel[0] > 0.0) {
                                glTexCoord2f(0.0f, 1.0f); glVertex2i(-s,-s);
                                glTexCoord2f(0.0f, 0.0f); glVertex2i(-s, s);
                                glTexCoord2f(1.0f, 0.0f); glVertex2i( s, s);
                                glTexCoord2f(1.0f, 1.0f); glVertex2i( s,-s);
                      //  } else {
                       //         glTexCoord2f(1.0f, 1.0f); glVertex2i(-wid,-wid);
                       //         glTexCoord2f(1.0f, 0.0f); glVertex2i(-wid, wid);
                       //         glTexCoord2f(0.0f, 0.0f); glVertex2i( wid, wid);
                       //         glTexCoord2f(0.0f, 1.0f); glVertex2i( wid,-wid);
                       // }
    glEnd();
    glPopMatrix();
    
    drawBox(ga.car.pos[0], ga.car.pos[1], ga.carSize);
    //screenPrint();	
    renderText();
    //printText();
    function1();
    //function2();
    //drawDatBox1();
    //drawDatBox2();
    //totalTimeFunction();
}














