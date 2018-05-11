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
#include "log.h"
#include "fonts.h"
#include "guillermoR.h"
#include "ianT.h"
#include "jorgeZ.h"
#include "joseV.h"

using namespace std;

GLuint backTexture;

Image img[1] = {
    "./Sprites/GameMapComplete3.jpg"
};

class Texture {
    public:
	Image *backImage;
	//GLuint backTexture;
	float xc[2];
	float yc[2];
};




class Global {
    public:
	int xres, yres, level;
	float fyres, fxres;
	bool pause;
	bool firstPause;
	GLuint carTexture;
	GLuint silhouetteTexture;
	Texture tex;
	float scrSpd, strSpd;
	bool forward, backwards, left, right;
	char keys[65536];

	Global() {
	    xres=256, yres=1024, fyres = yres, fxres = xres;
	    getfxres(fxres);
	    getfyres(fyres);
	    forward = 
		backwards = 
		left = 
		right = 
		pause=false;
	    firstPause = true;
	    scrSpd = .01125;
	    level = 0;
	    memset(keys, 0, sizeof(keys));
	}
} g;

//bool inMainMenu = true;
bool inMainMenu = true;
bool inGame = false;
bool inPauseMenu = false;
bool countDown = true;
bool gameOver = false;
bool inAudio = false;
bool inAudio2 = false;
bool inAudio3 = false;
bool inTutorial = false;
bool inTutorial2 = false;
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

bool audio_on = true;
#ifdef USE_OPENAL_SOUND
extern void initSounds();
extern void cleanSounds();
extern void playMain();
extern void stopMain();
extern void resumeMain();
extern void playPause();
extern void stopPause();
extern void resumePause();
extern void playMenuSelect();
extern void carExplodeOne();
extern void carExplodeTwo();
extern void carExplodeThree();
extern void carExplodeFour();
extern void carExplodeFive();
extern void healthLossOne();
extern void healthLossTwo();
extern void healthLossThree();
extern void healthLossFour();
extern void healthLossFive();
extern void playGameOver();
extern void playInGame();
extern void stopInGame();
extern void resumeInGame();
extern void carRevOne();
extern void carRevTwo();
extern void carRevThree();
extern void startGame();
extern void playBrake();
extern void playAccellOne();
extern void playAccellTwo();
extern void stopHoly();
#endif

//===========================================================================
//===========================================================================
int main()
{
#ifdef USE_OPENAL_SOUND
    initSounds();	
#endif

    init_opengl();

#ifdef USE_OPENAL_SOUND
    if (audio_on){
	startGame();
	playMain();
    }
#endif
    //makeCar();
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
    //if(inGame)
    generateTextures(); 
    generatePowerUpTextures();
    createTextures();

    //glGenTextures(1, &g.carTexture);
    //glGenTextures(1, &g.silhouetteTexture);
    //-----------------------------------------------------------------------------------
    int w =  g.tex.backImage->width; //grabs a set number of pixels and scales them-----------------
    int h =  g.tex.backImage->height; //grabs a set number of pixels and scales them----------------------
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
    initPowerUpImages();
    imageTexturing();
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


bool firstPause = true;
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
	if ((key == XK_w || key == XK_Up) && !g.pause) {
	    g.forward = true;
	}
	if ((key == XK_a || key == XK_Left) && !g.pause) {
	    g.left = true;
	}
	if ((key == XK_s || key == XK_Down) && !g.pause) {
	    g.backwards = true;
	}
	if ((key == XK_d || key == XK_Right) && !g.pause) {
	    g.right = true;
	}
	if (inMainMenu) {
	    if (key == XK_Return) {
		if (menuPosition == 1){
#ifdef USE_OPENAL_SOUND
		    playInGame();
		    stopMain();
		    stopHoly();		
#endif
		    inMainMenu = false;
		    inGame = true;
		} else if (menuPosition == 2) {
		    inMainMenu = false;
		    inAudio = true;
		    menuPosition = 0;
		} else if (menuPosition == 3) {
		    inMainMenu = false;
		    inTutorial = true;
		}
	    } else if (key == XK_Down || key == XK_s) {
		if (menuPosition != 3) {
#ifdef USE_OPENAL_SOUND
		    playMenuSelect();	
#endif
		    menuPosition++;
		}
	    } else if (key == XK_Up || key == XK_w) {
		if (menuPosition != 1) {
#ifdef USE_OPENAL_SOUND
		    playMenuSelect();	
#endif
		    menuPosition--;
		}
	    }
	}
	if (inPauseMenu) {
#ifdef USE_OPENAL_SOUND
	    if (firstPause){
		firstPause = false;
		playPause();
	    }
	    stopInGame();	
#endif
	    if(g.firstPause)
	    {
		g.firstPause = false;
	    }
	    if (key == XK_Return) {
		if (menuPosition == 1) {
#ifdef USE_OPENAL_SOUND
		    firstPause = true;
		    stopPause();
		    resumeInGame();

#endif
		    inPauseMenu = false;
		    inGame = true;
		} else if (menuPosition == 2) {
		    inPauseMenu = false;
		    inAudio2 = true;
		    menuPosition = 0;
		} else if (menuPosition == 3) {
		    inPauseMenu = false;
		    inTutorial2 = true;
		} else if (menuPosition == 4) {
		    return 1;
		}
	    } else if (key == XK_Down || key == XK_s) {
		if (menuPosition != 4) {
#ifdef USE_OPENAL_SOUND
		    playMenuSelect();
#endif
		    menuPosition++;
		}
	    } else if (key == XK_Up || key == XK_w) {
		if (menuPosition != 1) {
#ifdef USE_OPENAL_SOUND
		    playMenuSelect();
#endif
		    menuPosition--;
		}
	    }
	}
	if (gameOver) { 		
	    if (key == XK_Return) {
		if (menuPosition == 1) {
#ifdef USE_OPENAL_SOUND
		    playInGame();
#endif 
		    gameOver = false;

		    g.pause = false;
		    inGame = true;
		    clearScore(0);
		    clearLevel(1);
		} else if (menuPosition == 2) {
		    gameOver = false;
		    inMainMenu = true;
		} else if (menuPosition == 3) {
		    gameOver = false;
		    inAudio3 = true;
		    menuPosition = 0;
		} else if (menuPosition == 4) {
		    return 1;
		}
	    } else if (key == XK_Down || key == XK_s) {
		if (menuPosition != 4){
#ifdef USE_OPENAL_SOUND
		    playMenuSelect();
#endif
		    menuPosition++;
		}
	    } else if (key == XK_Up || key == XK_w) {
		if (menuPosition != 1) {
#ifdef USE_OPENAL_SOUND
		    playMenuSelect();
#endif
		    menuPosition--;
		}
	    }
	}
	if (inAudio) {
	    if (key == XK_Return) {
		if (menuPosition == 1) {
		    audio_on = true;
		} else if (menuPosition == 2) {
		    audio_on = false;
		} 
	    } else if (key == XK_Down || key == XK_s) {
		if (menuPosition != 2){
#ifdef USE_OPENAL_SOUND
		    playMenuSelect();
#endif
		    menuPosition++;
		}
	    } else if (key == XK_Up || key == XK_w) {
		if (menuPosition != 1) {
#ifdef USE_OPENAL_SOUND
		    playMenuSelect();
#endif
		    menuPosition--;
		}
	    } else if (key == XK_q) {
		inAudio = false;
		inMainMenu = true;
		menuPosition = 2;
	    }
	}
	if (inAudio2) {
	    if (key == XK_Return) {
		if (menuPosition == 1) {
		    audio_on = true;
		} else if (menuPosition == 2) {
		    audio_on = false;
		} 
	    } else if (key == XK_Down || key == XK_s) {
		if (menuPosition != 2){
#ifdef USE_OPENAL_SOUND
		    playMenuSelect();
#endif
		    menuPosition++;
		}
	    } else if (key == XK_Up || key == XK_w) {
		if (menuPosition != 1) {
#ifdef USE_OPENAL_SOUND
		    playMenuSelect();
#endif
		    menuPosition--;
		}
	    } else if (key == XK_q) {
		inAudio2 = false;
		inPauseMenu = true;
		menuPosition = 2;
	    }
	}
	if (inAudio3) {
	    if (key == XK_Return) {
		if (menuPosition == 1) {
		    audio_on = true;
		} else if (menuPosition == 2) {
		    audio_on = false;
		} 
	    } else if (key == XK_Down || key == XK_s) {
		if (menuPosition != 2){
#ifdef USE_OPENAL_SOUND
		    playMenuSelect();
#endif
		    menuPosition++;
		}
	    } else if (key == XK_Up || key == XK_w) {
		if (menuPosition != 1) {
#ifdef USE_OPENAL_SOUND
		    playMenuSelect();
#endif
		    menuPosition--;
		}
	    } else if (key == XK_q) {
		inAudio3 = false;
		gameOver = true;
		menuPosition = 3;
	    }
	}
	if (inTutorial) {
	    if (key == XK_q) {
		inTutorial = false;
		inMainMenu = true;
	    }
	}
	if (inTutorial2) {
	    if (key == XK_q) {
		inTutorial2 = false;
		inPauseMenu = true;
	    }
	}
    }
    if (e->type == KeyRelease) {
	if ((key == XK_w || key == XK_Up))  {
	    g.forward = false;
	}
	if (key == XK_a || key == XK_Left) {
	    g.left = false;
	}
	if (key == XK_s || key == XK_Down) {
	    g.backwards = false;
	}
	if (key == XK_d || key  == XK_Right) {
	    g.right = false;
	}
	return 0;
    }
    return 0;
}
int Points = 0;
float spd = .01;
bool firstCountDown = true;
void physics()
{
    if (inGame) {
	if (gameOver)
	    g.pause = true;

	if (g.pause && g.scrSpd != 0)
	    g.strSpd = g.scrSpd;

	if (g.pause)
	    g.scrSpd = 0.0;

	if (!g.pause && g.scrSpd == 0)
	    g.scrSpd = g.strSpd;
	//move the background
	if(countDown && !gameOver) {	
	    if (firstCountDown){
		startCountDownTimer();
		firstCountDown = false;
	    }
	    return;
	}

	g.tex.yc[0] -= g.scrSpd;
	g.tex.yc[1] -= g.scrSpd;

	//g.level = checkpoint();
	//checkpoint(g.level);
	moveLife(g.scrSpd);
	moveCrate(g.scrSpd);	
	moveEnemyCars(g.scrSpd);
	colWithPowerUP();

	velocityMod(g.fyres, g.scrSpd, countDown, firstCountDown);

	//moves main car using w,a,s,d keys
	if (g.forward) {
	    wMovement();
	}
	if (g.right) {
	    dMovement();
	}
	if (g.left) {
	    aMovement();
	}
	if (g.backwards) {
	    sMovement();
	}
	fixCarBoundaries();
    }
}
bool firstGameOver = true;
void render()
{
    powerUpHandler();
    glClearColor(0.9294, 0.788, 0.686, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    if (inMainMenu) {
	renderMainMenu();
	mainMenu(g.xres, g.yres);
    } else if (inPauseMenu) {
	pauseMenu(g.xres, g.yres);
    } else if (inAudio || inAudio2 || inAudio3) {
	audioMenu(g.xres, g.yres);
    } else if (inTutorial || inTutorial2) {
	tutorial(g.xres, g.yres);
    } else if (inGame) {
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, backTexture);
	glBegin(GL_QUADS);
	glTexCoord2f(g.tex.xc[0], g.tex.yc[1]); glVertex2i(0, 0);
	glTexCoord2f(g.tex.xc[0], g.tex.yc[0]); glVertex2i(0, g.yres);
	glTexCoord2f(g.tex.xc[1], g.tex.yc[0]); glVertex2i(g.xres, g.yres);
	glTexCoord2f(g.tex.xc[1], g.tex.yc[1]); glVertex2i(g.xres, 0);
	glEnd();		

	if (gameOver) {
#ifdef USE_OPENAL_SOUND
	    stopInGame();
	    if (firstGameOver){
		playGameOver();
		firstGameOver = false;
	    }
#endif
	    renderGameOver();
	    gameOverMenu(g.xres, g.yres);
	    finalScoreTracker();
	    GameOverScore();
	    finalLevelTracker();
	    GameOverLevel();
	    return;
	}

	if (countDown && !gameOver) {
	    renderMainCar(g.left, g.right);
	    renderLivesFrame();
	    renderLives();
	    renderHeart();
	    pointTracker();
	    levelTracker();
	    renderCountDown(countDown);
	}
	if (!countDown)
	    initTime();
	pointTracker();
	levelTracker();
	renderMainCar(g.left, g.right);
	renderLivesFrame();
	renderLives();
	renderHeart();
	renderCrate();
	renderPlowOnCar(g.left, g.right);
	//---------------------------------------------------------------------------- 
	//car texture
	//
	renderAudi();
	renderTaxi();
	renderMiniVan();
	screenPrint();	
    }
}
