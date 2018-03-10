//Jose Valenzuela 
//lab05
//Source code

#include "joseV.h"

//Game is paused when the p key is pressed.
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