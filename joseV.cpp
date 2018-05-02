//Jose Valenzuela 
//lab05
//Source code

#include "joseV.h"

Image plowImage = "./Sprites/Piskel.png"; 

GLuint plowTexture;
GLuint silhouettePlowTexture;

class Plow 
{
	public:
		int pos[3];
		int vel;
		int size;
		Plow() {
			size = 50;
		};
};

class gameObjects{
	public:
		Plow plow;
		int size;
		gameObjects() {
			plow.pos[0] = 256.0f;
			plow.pos[1] = 512.0f;
			plow.pos[2] = 0.0f;
		}
}go;

void generatePowerUpTextures(){
	glGenTextures(1, &plowTexture);
	glGenTextures(1, &silhouettePlowTexture);
}

void initPowerUpImages(){
	//Initialize main car Image
	int w = plowImage.width;
	int h = plowImage.height;

	glBindTexture(GL_TEXTURE_2D, plowTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, plowImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouettePlowTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData = buildAlphaData(&plowImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	free(silhouetteData);
}

void renderPlow()
{
	/*
	   int s = 50;
	   glColor3f(0.0, 0.0, 0.0);
	   glPushMatrix();
	   glTranslatef(256, 512, 0.0);
	   glBegin(GL_QUADS);
	   glVertex2i( -s,  -s);
	   glVertex2i( -s,   s);
	   glVertex2i(  s,   s);
	   glVertex2i(  s,  -s);
	   glEnd();
	   glPopMatrix();
	 */
	int s = go.plow.size;
	GLfloat color[3];
	color[0]=color[1]=color[2]=1.0;
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glTranslatef(go.plow.pos[0], go.plow.pos[1], 0.0f);
	glBindTexture(GL_TEXTURE_2D, silhouettePlowTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(-s,-s);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-s, s);
	glTexCoord2f(1.0f, 0.0f); glVertex2i( s, s);
	glTexCoord2f(1.0f, 1.0f); glVertex2i( s,-s);		

	/*
	   glRotatef(0.0f,0.0f,0.0f,1.0f);
	   glBegin(GL_TRIANGLES);
	   glVertex2f(-12.0f, -10.0f);
	   glVertex2f(  0.0f, 20.0f);
	   glVertex2f(  0.0f, -6.0f);
	   glVertex2f(  0.0f, -6.0f);
	   glVertex2f(  0.0f, 20.0f);
	   glVertex2f( 12.0f, -10.0f);
	   glEnd();
	   glColor3f(1.0f, 1.0f, 1.0f);
	   glBegin(GL_POINTS);
	   glVertex2f(0.0f, 0.0f);
	 */
	glEnd();
	glPopMatrix();

}

void pauseGame(float y[]){
	y[0]-=0.0;
	y[1]-=0.0;
}

void example() {
	Rect r;
	r.bot = 155;
	r.left = 155;
	r.center = 0;
	struct timespec start, end;
	double temp = 0;
	static double time = 0.0000;

	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &start);
	for (int i = 0; i< 242000000; i++)
		temp+=temp;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &end);

	time += timeDiff(&start, &end);
	ggprint8b(&r, 16, 0xFFFF00, "function-time:%lf", time);
}
