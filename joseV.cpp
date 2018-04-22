//Jose Valenzuela 
//lab05
//Source code

#include "joseV.h"


struct Plow 
{
	int pos[3];
	int vel = scrSpd;
}
void initPlow() 
{
	stuct Plow *plow;
	plow->pos[0] = xres/2;
	plow->pos[1] = yres;
	plor->pos[2] = 0.0f;
	renderPlow(plow);
}
void renderPlow(struct Plow *plow)
{

 
  	//glColor3fv(g.ship.color);
	glPushMatrix();
	glTranslatef(plow->pos[0], plow->pos[1], plow->pos[2]);
	glBegin(GL_TRIANGLES);
		glVertex2f(-12.0f, -10.0f);
		glVertex2f(  0.0f, 20.0f);
		glVertex2f(  0.0f, -6.0f);
		glVertex2f(  0.0f, -6.0f);
		glVertex2f(  0.0f, 20.0f);
		glVertex2f( 12.0f, -10.0f);
	glEnd();
	glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
		glVertex2f(0.0f, 0.0f);
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