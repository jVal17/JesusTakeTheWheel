#include "jorgeZ.h"
#include "guillermoR.h"
#include "ianT.h"
#include <ctime>
#include <iostream>

using namespace std;
double durationPaused = 0.0;
int Score = 0;
int lvl = 1;
float speed = .01;
float fyres2 = 1024;
int levelUp = 100;
int finalCollision = 50;
int fScore = 0;

Image level = "./Sprites/level.png";
Image scoreboard = "./Sprites/scoreboard.png";
Image FinalScore = "./Sprites/FinalScore.PNG";
Image FinalLevel = "./Sprites/FinalLevel.PNG";

GLuint scoreTexture;
GLuint silhouetteScoreTexture;
GLuint levelTexture;
GLuint silhouetteLevelTexture;
GLuint FinalScoreTexture;
GLuint silhouetteFinalScoreTexture;
GLuint FinalLevelTexture;
GLuint silhouetteFinalLevelTexture;


void createTextures()
{
    glGenTextures(1, &scoreTexture);
    glGenTextures(1, &silhouetteScoreTexture);
    glGenTextures(1, &levelTexture);
    glGenTextures(1, &silhouetteLevelTexture);
    glGenTextures(1, &FinalScoreTexture);
    glGenTextures(1, &silhouetteFinalScoreTexture);
    glGenTextures(1, &FinalLevelTexture);
    glGenTextures(1, &silhouetteFinalLevelTexture);
}

void screenPrint () 
{
    Rect r;
    r.bot = 686;
    r.left = 45;
    if(Score >= 100)
	r.left = 42;
    if(Score >= 1000)
	r.left = 39;
    r.center = 0;
    ggprint8b(&r, 16, 0xffffffff, "%li", Score);

    Rect r2;
    r2.bot = 787;
    r2.left = 45;
    r2.center = 0;
    ggprint8b(&r2, 16, 0xffffffff, "%li", lvl);

    glEnd();
}

void GameOverLevel()
{
    Rect r;
    r.bot = 468;
    r.left = 252;
    r.center = 0;
    ggprint8b(&r, 16, 0xffffffff, "%li", lvl);
}

void GameOverScore()
{
    Rect r;
    r.bot = 418;
    r.left = 252;
    r.center = 0;
    fScore = (Score - finalCollision);
    if(fScore >= 100)
	r.left = 249;
    if(fScore >= 1000)
	r.left = 246;
    if(fScore < 0)
	fScore = 0;
    ggprint8b(&r, 16, 0xffffffff, "%li", fScore);
}

void clearScore(int newScore)
{
        Score = newScore;
}

void clearLevel(int newLevel)
{
        lvl = newLevel;
}

void checkpoint (int Score, int &Lev)
{
    if(Score >= levelUp){
	levelUp += 100;
	Lev += 1;
    }
}

void velocityMod(float fyres2, float &scrolling, bool &countDownBool, bool &firstCountDownBool)
{
    checkpoint(Score, lvl);
    //cout << "Scrolling = " << scrolling << endl;

    int cc = checkCollisions(scrolling, countDownBool, firstCountDownBool);
    if(cc){
	if(cc==1){
	    scrolling *= .3;
	    Score -= 50;
	    //.015 is a bit too fast
	    //cout << "Score: " << Score << endl;
	    screenPrint();
	}
	/*if(cc==2){
	  Score = 0;
	  }*/
    }
    if(spawnEnemyCars(fyres2)){
	Score += 10;
	scrolling = scrolling + Score*.000001;
	/*if(gameOver == true)
	  Score;*/
	if(Score < 1000 && scrolling >= .03125)
	    scrolling = .03125;
	else if(Score >= 1000 && Score < 2000)
	    scrolling = .03425;
	else if(Score >= 2000 && Score < 3000)
	    scrolling = .03725;
	//cout << "Score: " << Score << endl;
    }

    if(scrolling <=.01125)
	scrolling = .01125;

    if(Score <= 0)
	Score = 0;

}

void imageTexturing()
{
    //Score Texturing
    int w = scoreboard.width;
    int h = scoreboard.height;

    glBindTexture(GL_TEXTURE_2D, scoreTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
	    GL_RGB, GL_UNSIGNED_BYTE, scoreboard.data);

    //score silhouette
    glBindTexture(GL_TEXTURE_2D, silhouetteScoreTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *silhouetteScore = buildAlphaData(&scoreboard);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, silhouetteScore);
    free(silhouetteScore);

    //Level Texturing
    w = level.width;
    h = level.height;

    glBindTexture(GL_TEXTURE_2D, levelTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
	    GL_RGB, GL_UNSIGNED_BYTE, level.data);

    //level silhouette
    glBindTexture(GL_TEXTURE_2D, silhouetteLevelTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *silhouetteLevel = buildAlphaData(&level);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, silhouetteLevel);
    free(silhouetteLevel);

    //Final Score Texturing
    w = FinalScore.width;
    h = FinalScore.height;

    glBindTexture(GL_TEXTURE_2D, FinalScoreTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
	    GL_RGB, GL_UNSIGNED_BYTE, FinalScore.data);

    //Final Score silhouette
    glBindTexture(GL_TEXTURE_2D, silhouetteFinalScoreTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *silhouetteFinalScore = buildAlphaData(&FinalScore);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, silhouetteFinalScore);
    free(silhouetteFinalScore);

    //Final Level Texturing
    w = FinalLevel.width;
    h = FinalLevel.height;

    glBindTexture(GL_TEXTURE_2D, FinalLevelTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
	    GL_RGB, GL_UNSIGNED_BYTE, FinalLevel.data);

    //Final Level silhouette
    glBindTexture(GL_TEXTURE_2D, silhouetteFinalLevelTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *silhouetteFinalLevel = buildAlphaData(&FinalLevel);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
	    GL_RGBA, GL_UNSIGNED_BYTE, silhouetteFinalLevel);
    free(silhouetteFinalLevel);

}

void pointTracker() 
{
    int sy = 20;
    int sx = 2.43902439*sy;
    float x = (50);
    float y = (700);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, silhouetteScoreTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-sx,-sy);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-sx, sy);
    glTexCoord2f(1.0f, 0.0f); glVertex2f( sx, sy);
    glTexCoord2f(1.0f, 1.0f); glVertex2f( sx,-sy);
    glEnd();
    glPopMatrix();
}

void levelTracker()
{
    int sy = 20;
    int sx = 2.43902439*sy;
    float x = (50);
    float y = (800);
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, silhouetteLevelTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-sx,-sy);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-sx, sy);
    glTexCoord2f(1.0f, 0.0f); glVertex2f( sx, sy);
    glTexCoord2f(1.0f, 1.0f); glVertex2f( sx,-sy);
    glEnd();
    glPopMatrix();
}

void finalLevelTracker()
{
    int sy = 20;
    int sx = 3.1463414*sy;
    float x = 256;
    float y = 480;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, silhouetteFinalLevelTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-sx,-sy);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-sx, sy);
    glTexCoord2f(1.0f, 0.0f); glVertex2f( sx, sy);
    glTexCoord2f(1.0f, 1.0f); glVertex2f( sx,-sy);
    glEnd();
    glPopMatrix();
}

void finalScoreTracker()
{
    int sy = 20;
    int sx = 3.1463414*sy;
    float x = 256;
    float y = 430;
    glPushMatrix();
    glTranslatef(x, y, 0);
    glBindTexture(GL_TEXTURE_2D, silhouetteFinalScoreTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2f(-sx,-sy);
    glTexCoord2f(0.0f, 0.0f); glVertex2f(-sx, sy);
    glTexCoord2f(1.0f, 0.0f); glVertex2f( sx, sy);
    glTexCoord2f(1.0f, 1.0f); glVertex2f( sx,-sy);
    glEnd();
    glPopMatrix();
}
