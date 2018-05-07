//Jose Valenzuela 
//lab05
//Source code


#include "joseV.h"
Image plowImage = "./Sprites/plow.png"; 
Image crateImage = "./Sprites/crate.png";
GLuint crateTexture;
GLuint silhouetteCrateTexture;
GLuint plowTexture;
GLuint silhouettePlowTexture;
bool plowPowerUp = false;

class powerUp 
{
	public:
		int pos[3];
		int vel;
		int size;
		powerUp() {
			size = 26;
		};
};

class gameObjects{
	public:
		powerUp plow;
		powerUp crate;
		int size;
		bool contactCrate;
		bool plowPowerUp = false;
		gameObjects() {
			plow.size = 50;
			crate.size = 35;
			plow.pos[0] = 256.0f;
			plow.pos[1] = 512.0f;
			plow.pos[2] = 0.0f;
			crate.pos[0] = 256.0f;
			crate.pos[1] = 512.0f+600.0f;
			crate.pos[2] = 0.0f;
			contactCrate=false;
		}
}go;

void moveCrate(float src){
	int chance = 100 - rand()%100;
	//cout << chance << endl;
	if(chance == 1){
		if(go.crate.pos[1] < 0){
			go.contactCrate = false;
			spawnCrate();	
		}
	}
	go.crate.pos[1] -= (src*600.0);
}

void colWithPowerUP(){
	float MC[2];
	getMainCarCoords(MC);
	if(go.crate.pos[1]-35.0 < MC[1] && 
			go.crate.pos[1]+35.0 > MC[1] &&
			go.crate.pos[0]-35.0 < MC[0] &&
			go.crate.pos[0]+35.0 > MC[0]
	  ){
		plowPowerUp = true;
		go.contactCrate = true;
		cout << "Crate Contact with main Car" << endl;
	}
	//draw plow
	//make car invinc
	//if car collision with enmy make enmy spin
	//}
}
bool getPowerUp(){
	return go.plowPowerUp;
}
void renderPlowOnCar(bool l, bool r){
	if(go.contactCrate){
		float MC[2];
		getMainCarCoords(MC);
		go.plow.pos[0] = MC[0];
		go.plow.pos[1] = MC[1] + 30;
		int s = go.plow.size;
		GLfloat color[3];
		color[0]=color[1]=color[2]=1.0;
		glPushMatrix();
		glColor3f(1.0,1.0,1.0);
		glTranslatef(go.plow.pos[0], go.plow.pos[1], 0.0f);
		if(l) {
			glRotatef( 10.0, 0.0, 0.0, 1.0);
		}
		if(r) {
			glRotatef(-10.0, 0.0, 0.0, 1.0);
		}
		glBindTexture(GL_TEXTURE_2D, silhouettePlowTexture);
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
}

void spawnCrate(){
	cout << "spawned crate" <<endl;
	go.crate.pos[0] = rand()%(X_MAX - X_MIN) + X_MIN;
	go.crate.pos[1] = 1024;
}

void generatePowerUpTextures(){
	glGenTextures(1, &plowTexture);
	glGenTextures(1, &silhouettePlowTexture);
	glGenTextures(1, &crateTexture);
	glGenTextures(1, &silhouetteCrateTexture);
}

void initPowerUpImages(){
	//initialize plow image

	int w = plowImage.width;
	int h = plowImage.height;
	glBindTexture(GL_TEXTURE_2D, plowTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE
			, plowImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouettePlowTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData0 = buildAlphaData(&plowImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE
			, silhouetteData0);
	free(silhouetteData0);


	//initial crate image
	w = crateImage.width;
	h = crateImage.height;
	glBindTexture(GL_TEXTURE_2D, crateTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE
			, crateImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteCrateTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData1 = buildAlphaData(&crateImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE
			, silhouetteData1);
	free(silhouetteData1);

}

void renderCrate()
{
	if(go.contactCrate) {
		cout << go.crate.pos[0] << " " << go.crate.pos[1] << endl;
		return;
	}
	int s = go.crate.size;
	GLfloat color[3];
	color[0]=color[1]=color[2]=1.0;
	glPushMatrix();
	glColor3f(1.0,1.0,1.0);
	glTranslatef(go.crate.pos[0], go.crate.pos[1], 0.0f);
	glBindTexture(GL_TEXTURE_2D, silhouetteCrateTexture);
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
