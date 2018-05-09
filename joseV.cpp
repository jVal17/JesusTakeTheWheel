//Jose Valenzuela 
//Source code


#include "joseV.h"
Image plowImage = "./Sprites/plow.png"; 
Image crateImage = "./Sprites/crate.png";
Image liveImage = "./Sprites/cross.jpg";
GLuint liveTexture;
GLuint silhouetteLiveTexture;
GLuint crateTexture;
GLuint silhouetteCrateTexture;
GLuint plowTexture;
GLuint silhouettePlowTexture;
static struct timespec ctimeStart, ctimeEnd, ptimeStart, ptimeEnd, ltimeStart, ltimeEnd;
bool once = true;

void initTime(){
	if(once){
		clock_gettime(CLOCK_REALTIME, &ctimeStart);
		clock_gettime(CLOCK_REALTIME, &ltimeStart);
		once = false;
	}
}

class powerUp {
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
		powerUp live;
		int size;
		bool contactCrate, contactLive;
		bool poweredUp;
		gameObjects() {
			plow.size = 50;
			crate.size = 35;
			plow.pos[0] = 256.0f;
			plow.pos[1] = 512.0f;
			plow.pos[2] = 0.0f;
			live.pos[0] = 256.0f;
			live.pos[1] = 512.0f+600.0f;
			live.pos[2] = 0.0f;
			crate.pos[0] = rand() % (X_MAX-X_MIN) + X_MIN;
			crate.pos[1] = 1124;
			crate.pos[2] = 0.0f;
			contactCrate=false;
			poweredUp=false;
			contactLive=false;
		}
}go;
//-------------------------------Power up physics------
void powerUpHandler(){
	if(go.poweredUp){
		endPower();
	}
}
//-------------------------------POWER UPS -------------
bool getPowerUp(){
	return go.poweredUp; 
}

//if power up timer initiated 
bool already = false;
//checks power up interval
void endPower(){
	//cout << "endpower" <<endl;
	clock_gettime(CLOCK_REALTIME, &ptimeEnd);	
	int diff = timeDiff(&ptimeStart, &ptimeEnd);
	if(diff >= 4){
		already = false;
		go.poweredUp = false;	
		cout << "here" << endl;
	}	
}

void initPTimer(){
	if(go.poweredUp && already==false){
		clock_gettime(CLOCK_REALTIME, &ptimeStart);
		already = true;
	}
}

void colWithPowerUP(){
	float MC[2];
	getMainCarCoords(MC);
	if(go.crate.pos[1]-35.0 < MC[1] && 
			go.crate.pos[1]+35.0 > MC[1] &&
			go.crate.pos[0]-35.0 < MC[0] &&
			go.crate.pos[0]+35.0 > MC[0]
	  ){

		go.poweredUp = true;
		go.contactCrate = true;
		initPTimer();
	}
}

int temp = 5;
void spawnCrate(){
	go.crate.pos[0] = rand()%(X_MAX - X_MIN) + X_MIN;
	go.crate.pos[1] = 1124;
}

void moveCrate(float src){
	clock_gettime(CLOCK_REALTIME, &ctimeEnd);	
	int diff = timeDiff(&ctimeStart, &ctimeEnd);
	if(diff > temp){
		temp+=7;
		go.contactCrate = false;
		spawnCrate();	
	}
	go.crate.pos[1] -= (src*600.0);
}
int inter = 20;
void spawnLive(){
	//go.live.pos[0] = rand()%(X_MAX - X_MIN) + X_MIN;
	//go.live.pos[1] = 1024;
}
void moveLife(float src){
	clock_gettime(CLOCK_REALTIME, &ltimeEnd);
	//int diff = timeDiff(&ltimeStart, &ltimeEnd);
	//if(diff > inter){
		//inter+=20;
		//go.contactLive = false;
		//spawnLive();
	//}
	go.live.pos[1] -=(src*600.0);
}
//---------------------------------RENDERING-----------------------------------
void renderCrate()
{
	if(go.contactCrate == false){
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
	/*
	if(go.contactLive == false){
		int s = go.live.size;
		GLfloat color[3];
		color[0]=color[1]=color[2]=1.0;
		glPushMatrix();
		glColor3f(1.0,1.0,1.0);
		glTranslatef(go.live.pos[0], go.live.pos[1], 0.0f);
		glBindTexture(GL_TEXTURE_2D, silhouetteLiveTexture);
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
*/
}

void generatePowerUpTextures(){
	glGenTextures(1, &plowTexture);
	glGenTextures(1, &silhouettePlowTexture);
	glGenTextures(1, &crateTexture);
	glGenTextures(1, &silhouetteCrateTexture);
	glGenTextures(1, &liveTexture);
	glGenTextures(1, &silhouetteLiveTexture);
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
	
	w = liveImage.width;
	h = liveImage.height;
	glBindTexture(GL_TEXTURE_2D, liveTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0, GL_RGB, GL_UNSIGNED_BYTE
			, liveImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteLiveTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData2 = buildAlphaData(&liveImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE
			, silhouetteData2);
	free(silhouetteData2);

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
void renderPlowOnCar(bool l, bool r){
	if(go.poweredUp){
		float MC[2];
		getMainCarCoords(MC);
		go.plow.pos[0] = MC[0];
		go.plow.pos[1] = MC[1] + 55;
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


