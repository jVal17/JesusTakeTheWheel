//Guillermo Ramirez
//Seperate file for Guillermo Ramirez

#include "guillermoR.h"
#include "joseV.h"
float fxres, fyres;
static struct timespec ftimeStart, ftimeEnd, fireTime, currentCountTime, countDownTime;

Image mainCarImage = "./Sprites/Audi.png";
Image audiImage = "./Sprites/Car.png";
Image taxiImage = "./Sprites/taxi2.jpg";
Image miniVanImage = "./Sprites/Mini_van.png";
Image heartImage = "./Sprites/cross.jpg";
Image mainMenuImage = "./Sprites/mainMenu.png";
Image gameOverImage = "./Sprites/gameOver.png";
Image livesImage = "./Sprites/Lives.png";
Image fireImage = "./Sprites/fire.png";
Image livesFrameImage = "./Sprites/livesFrame.png";
Image countDownImage[4] = {"./Sprites/3.png",
	"./Sprites/2.png",
	"./Sprites/1.png",
	"./Sprites/GO.png"
};
GLuint countDownTexture[4];
GLuint mainCarTexture;
GLuint gameOverTexture;
GLuint mainMenuTexture;
GLuint audiTexture;
GLuint taxiTexture;
GLuint miniVanTexture;
GLuint heartTexture;
GLuint livesTexture;
GLuint fireTexture;
GLuint livesFrameTexture;
GLuint silhouetteMainCarTexture;
GLuint silhouetteAudiTexture;
GLuint silhouetteTaxiTexture;
GLuint silhouetteMiniVanTexture;
GLuint silhouetteHeartTexture;
GLuint silhouetteMainMenuTexture;
GLuint silhouetteLivesTexture;
GLuint silhouetteLivesFrameTexture;

class Heart {
	public:
		int size;
		Vec pos;
		Heart() {
			size = 15;
		}
};

void getfxres(float x){
	fxres = x;
}

void getfyres(float y){
	fyres = y;
}

class Game {
	public:
		Car mainCar, enemyCar[3];
		Heart heart[3];
		int numHearts;
		int carSize;
		int totalEnemyCars;
		int carSpawnPos;
		bool firstInvinc;
		bool firstBlink;
		bool blinkReset;
		bool blink;
		float t1;
		double invincTimer;
		double invincDurationTimer;
		double blinkTimer;
		Vec tmpMainPos, tmpMainPos2;

		Game() {
			for(int j = 0; j < 3; j++){
				heart[j].pos[0]= (fxres*1.66) + (j*30);
				heart[j].pos[1]= 774;
			}
			mainCar.pos[0]= fxres;
			mainCar.pos[1]= 80.0;
			for(int i=0; i < 3; i++) {
				carSpawnPos = rand() % (X_MAX - X_MIN) + X_MIN;
				enemyCar[i].pos[0] = carSpawnPos;
			}
			enemyCar[0].pos[1]= fyres+100;
			enemyCar[1].pos[1]= fyres+((fyres*.35)+100);
			enemyCar[2].pos[1]= fyres+((fyres*.7)+100);
			carSize = 50;
			totalEnemyCars = 3;
			numHearts = 2;
			firstInvinc = true;
			firstBlink = true;
			invincTimer = 0.0;
			blinkTimer = 0.0;
			blinkReset = true;
			blink = false;
			t1=.08;
			invincDurationTimer=1.5;
			tmpMainPos[0]=-500.0;
		}

} ga;

unsigned char *buildAlphaData(Image *img)
{
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
		ptr += 4;
		data += 3;
	}
	return newdata;
}


void moveEnemyCars(float scr){
	ga.enemyCar[0].pos[1] -= (scr*600.0);
	ga.enemyCar[1].pos[1] -= (scr*600.0);	
	ga.enemyCar[2].pos[1] -= (scr*600.0);	
}

//void countDownSetTrue (bool &countBool)
//	countBool = true;
int carHit = -1;
int checkCollisions(float scr, bool &countDownBool, bool &firstCountDown){
	ga.mainCar.powerUp = getPowerUp();
	int doesHit = 0;
	ga.tmpMainPos2[0] = ga.mainCar.pos[0];
	checkInvincOutside();	
	for(int i = 0; i < ga.totalEnemyCars; i++){
		if (ga.enemyCar[i].pos[1]-75.0 < ga.mainCar.pos[1] && 
				ga.enemyCar[i].pos[1]+75.0 > ga.mainCar.pos[1] &&
				ga.enemyCar[i].pos[0]-30.0 < ga.mainCar.pos[0] &&
				ga.enemyCar[i].pos[0]+30.0 > ga.mainCar.pos[0]
		   ){
			if(ga.mainCar.powerUp) {
				ga.enemyCar[i].carHit = 1;
			} else if(!ga.mainCar.invinc) {
				ga.heart[ga.numHearts].pos[0] = -50;
				ga.numHearts-=1;
				ga.mainCar.invinc = true;
				doesHit = 1;
			}
			carInvincibility();
			if (ga.numHearts < 0) {
				gameOver = true;
				cout << "You have crashed. Game has reset" << endl;
				resetGame(scr, ga.mainCar.pos[0], ga.mainCar.pos[1],	
						ga.enemyCar[0].pos[0], ga.enemyCar[0].pos[1], 
						ga.enemyCar[1].pos[1], ga.enemyCar[1].pos[0], 
						fxres, fyres);
				countDownBool = true;	
				firstCountDown = true;	
				doesHit = 2;				
			}
		}
	}
	return doesHit;
}

void getMainCarCoords(float (&M)[2]) {
	M[0] = ga.mainCar.pos[0];
	M[1] = ga.mainCar.pos[1];
}

void getEnemyCars(struct Car (&eCar)[3]){
	eCar[0] = ga.enemyCar[0];
	eCar[1] = ga.enemyCar[1];
	eCar[2] = ga.enemyCar[2];
}

void carInvincibility() {
	if (ga.mainCar.invinc) 
		if (ga.invincTimer == 0.0)
			if (ga.firstInvinc) 
				clock_gettime(CLOCK_REALTIME, &ftimeStart);
	ga.firstInvinc = false;
	clock_gettime(CLOCK_REALTIME, &ftimeEnd);	
	ga.invincTimer = timeDiff(&ftimeStart, &ftimeEnd);

	if (ga.invincTimer > ga.invincDurationTimer && ga.mainCar.invinc) {
		ga.invincTimer = 0.0;
		ga.mainCar.invinc = false;
		ga.firstInvinc=true;
	} 
}

void checkInvincOutside(){
	if (ga.mainCar.invinc && ga.invincTimer > 0.0){
		clock_gettime(CLOCK_REALTIME, &ftimeEnd);	
		ga.invincTimer = timeDiff(&ftimeStart, &ftimeEnd);
		if(ga.invincTimer > ga.t1){
			ga.t1 += 0.08;
			blink();
		}
	}
	if (ga.invincTimer > ga.invincDurationTimer && ga.mainCar.invinc) {
		ga.invincTimer = 0.0;
		ga.mainCar.invinc = false;
		ga.firstInvinc=true;
		ga.t1=0.08;
	}
}

void blink(){
	if (!ga.blink){
		ga.blink = true;
	}
	else
		ga.blink = false;
}

bool spawnEnemyCars(float yres){
	if (ga.enemyCar[0].pos[1] < 0.0) {
		ga.carSpawnPos = rand() % (X_MAX-X_MIN) + X_MIN;
		ga.enemyCar[0].pos[0] = ga.carSpawnPos;
		ga.enemyCar[0].pos[1] = yres+100;
		ga.enemyCar[0].carHit = 0;
		return true;
	}
	if (ga.enemyCar[1].pos[1] < 0.0) {
		//ga.enemyCar[1].pos[1] = fyres+((yres*.33)+100);
		ga.carSpawnPos = rand() % (X_MAX-X_MIN) + X_MIN;
		ga.enemyCar[1].pos[0] = ga.carSpawnPos;
		ga.enemyCar[1].pos[1] = yres+100;
		ga.enemyCar[1].carHit = 0;
		return true;
	}	
	if (ga.enemyCar[2].pos[1] < 0.0) {
		//ga.enemyCar[2].pos[1] = fyres+((yres*.66)+100);
		ga.carSpawnPos = rand() % (X_MAX-X_MIN) + X_MIN;
		ga.enemyCar[2].pos[0] = ga.carSpawnPos;
		ga.enemyCar[2].pos[1] = yres+100;
		ga.enemyCar[2].carHit = 0;
		return true;
	}

	return false;	
}

void wMovement(){
	ga.mainCar.pos[1] += 8;
}

void dMovement(){
	ga.mainCar.pos[0] += 8;
}

void aMovement(){
	ga.mainCar.pos[0] -= 8;
}

void sMovement(){
	ga.mainCar.pos[1] -= 8;
}

void fixCarBoundaries() {
	if (ga.mainCar.pos[1] > fyres-40.0)
		ga.mainCar.pos[1] = fyres-40.0;
	if (ga.mainCar.pos[0] > 370.0)
		ga.mainCar.pos[0] = 370.0;
	if (ga.mainCar.pos[0] < 140.0)
		ga.mainCar.pos[0] = 140.0;
	if (ga.mainCar.pos[1] < 40.0)
		ga.mainCar.pos[1] = 40.0;
}

void resetGame(float &scr, float &mcX, float &mcY, float &ecX, float &ecY,
		float &ec2X, float &ec2Y, float xres, float yres)
{
	int randnum = rand() % 2;
	scr = .01;
	mcX = xres;
	mcY = 80.0;
	ecY = yres+100;
	ec2Y = fyres+(fyres*0.35)+100;
	if(randnum)
		ecX = 180.0;
	else 
		ecX = 340.0;
	randnum = rand() % 2;
	if(randnum)
		ec2X = 180.0;
	else 
		ec2X = 340.0;
	for (int j = 0; j < 3; j++) {	
		ga.heart[j].pos[0]= (fxres*1.66) + (j*30);
		ga.heart[j].pos[1]= 774;
	}
	ga.enemyCar[2].pos[1] = fyres+((fyres*.7)+100);
	ga.numHearts = 2;
}

void generateTextures(){
	glGenTextures(1, &mainCarTexture);
	glGenTextures(1, &gameOverTexture);
	glGenTextures(1, &audiTexture);
	glGenTextures(1, &miniVanTexture);
	glGenTextures(1, &taxiTexture);
	glGenTextures(1, &livesTexture);
	glGenTextures(1, &livesFrameTexture);
	glGenTextures(1, &heartTexture);
	glGenTextures(1, &fireTexture);
	glGenTextures(1, &countDownTexture[0]);
	glGenTextures(1, &countDownTexture[1]);
	glGenTextures(1, &countDownTexture[2]);
	glGenTextures(1, &countDownTexture[3]);
	glGenTextures(1, &silhouetteMainCarTexture);
	glGenTextures(1, &silhouetteAudiTexture);
	glGenTextures(1, &silhouetteMiniVanTexture);
	glGenTextures(1, &silhouetteTaxiTexture);
	glGenTextures(1, &silhouetteHeartTexture);
	glGenTextures(1, &silhouetteMainMenuTexture);
	glGenTextures(1, &silhouetteLivesTexture);
	glGenTextures(1, &silhouetteLivesFrameTexture);
}

void initImages() {
	int w = fireImage.width;
	int h = fireImage.height;
	glBindTexture(GL_TEXTURE_2D, fireTexture);
	//
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	//
	//must build a new set of data...
	unsigned char *fireData = buildAlphaData(&fireImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, fireData);

	//Initialize main car Image
	w = mainCarImage.width;
	h = mainCarImage.height;

	glBindTexture(GL_TEXTURE_2D, mainCarTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, mainCarImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteMainCarTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData = buildAlphaData(&mainCarImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	free(silhouetteData);


	//audi Image
	w = audiImage.width;
	h = audiImage.height;

	glBindTexture(GL_TEXTURE_2D, audiTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, audiImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteAudiTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData2 = buildAlphaData(&audiImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData2);
	free(silhouetteData2);

	//Init enemy mini Van Image
	w = miniVanImage.width;
	h = miniVanImage.height;

	glBindTexture(GL_TEXTURE_2D, miniVanTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, miniVanImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteMiniVanTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData3 = buildAlphaData(&miniVanImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData3);
	free(silhouetteData3);

	//taxi
	w = taxiImage.width;
	h = taxiImage.height;

	glBindTexture(GL_TEXTURE_2D, taxiTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, taxiImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteTaxiTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteTaxi = buildAlphaData(&taxiImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteTaxi);
	free(silhouetteTaxi);

	//Init Heart
	w = heartImage.width;
	h = heartImage.height;

	glBindTexture(GL_TEXTURE_2D, heartTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, heartImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteHeartTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData4 = buildAlphaData(&heartImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData4);
	free(silhouetteData4);	

	//Init transparent Image
	w = mainMenuImage.width;
	h = mainMenuImage.height;

	glBindTexture(GL_TEXTURE_2D, mainMenuTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, mainMenuImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteMainMenuTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData6 = buildAlphaData(&mainMenuImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData6);
	free(silhouetteData6);

	//init game over 
	w = gameOverImage.width;
	h = gameOverImage.height;

	glBindTexture(GL_TEXTURE_2D, gameOverTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, gameOverImage.data);

	//Init Lives Image
	w = livesImage.width;
	h = livesImage.height;

	glBindTexture(GL_TEXTURE_2D, livesTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, livesImage.data);
	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteLivesTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteData7 = buildAlphaData(&livesImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData7);
	free(silhouetteData7);

	w = livesFrameImage.width;
	h = livesFrameImage.height;

	glBindTexture(GL_TEXTURE_2D, livesFrameTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
			GL_RGB, GL_UNSIGNED_BYTE, livesFrameImage.data);

	//silhouette
	glBindTexture(GL_TEXTURE_2D, silhouetteLivesFrameTexture);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	unsigned char *silhouetteFrameData = buildAlphaData(&livesFrameImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
			GL_RGBA, GL_UNSIGNED_BYTE, silhouetteFrameData);
	free(silhouetteFrameData);

	unsigned char *silhouetteCountDownData[4];
	for (int i=0; i<4; i++) {
		//Init transparent Image
		w = countDownImage[i].width;
		h = countDownImage[i].height;

		glBindTexture(GL_TEXTURE_2D, countDownTexture[i]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		glTexImage2D(GL_TEXTURE_2D, 0, 3, w, h, 0,
				GL_RGB, GL_UNSIGNED_BYTE, countDownImage[i].data);
		//silhouette
		glBindTexture(GL_TEXTURE_2D, countDownTexture[i]);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
		silhouetteCountDownData[i] = buildAlphaData(&countDownImage[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, silhouetteCountDownData[i]);
		free(silhouetteCountDownData[i]);
	}
}

float angle = 0;
void renderMainCar(bool l, bool r) {
	float x = ga.mainCar.pos[0];
	float y = ga.mainCar.pos[1];
	if (!ga.mainCar.invinc && !ga.mainCar.powerUp) {
		glPushMatrix();
		glTranslatef(x, y, 0);
		if(l) {
			glRotatef( 10.0, 0.0, 0.0, 1.0);
		}
		if(r) {
			glRotatef(-10.0, 0.0, 0.0, 1.0);
		}
		glColor4ub(255,255,255,255);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBindTexture(GL_TEXTURE_2D, silhouetteMainCarTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(-50,-50);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(-50, 50);
		glTexCoord2f(1.0f, 0.0f); glVertex2i( 50, 50);
		glTexCoord2f(1.0f, 1.0f); glVertex2i( 50,-50);
		glEnd();
		glPopMatrix();
	} else if (ga.mainCar.powerUp) {
		glPushMatrix();
		glTranslatef(x, y, 0);
		if(l) {
			glRotatef( 10.0, 0.0, 0.0, 1.0);
		}
		if(r) {
			glRotatef(-10.0, 0.0, 0.0, 1.0);
		}
		glColor4ub(255,255,255,255);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBindTexture(GL_TEXTURE_2D, silhouetteMainCarTexture);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(-50,-50);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(-50, 50);
		glTexCoord2f(1.0f, 0.0f); glVertex2i( 50, 50);
		glTexCoord2f(1.0f, 1.0f); glVertex2i( 50,-50);
		glEnd();
		glPopMatrix();
	} else if (ga.mainCar.invinc) {
		int s = ga.carSize;
		glPushMatrix();
		if(ga.blink)
			glColor4f(1.0,0.0,0.0,1.0); 
		else
			glColor4f(1.0,1.0,1.0,1.0);
		if(rand()%2==0){	
			x=ga.mainCar.pos[0]+=5;
		}else{
			x=ga.mainCar.pos[0]-=5;
		}
		fixCarBoundaries();
		//printf("%f\n",x);
		glTranslatef(x, y, 0);
		glRotatef( angle+=15.0, 0.0, 0.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, silhouetteMainCarTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(-s,-s);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(-s, s);
		glTexCoord2f(1.0f, 0.0f); glVertex2i( s, s);
		glTexCoord2f(1.0f, 1.0f); glVertex2i( s,-s);
		glEnd();
		glPopMatrix();
	}

}

float angle2;
void renderAudi() {
	if(ga.enemyCar[0].carHit){
		int s = ga.carSize;
		float x = ga.enemyCar[0].pos[0];
		float y = ga.enemyCar[0].pos[1];
		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef( angle2+=15.0, 0.0, 0.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, silhouetteAudiTexture);
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
	} else {
		int s = ga.carSize;
		float x = ga.enemyCar[0].pos[0];
		float y = ga.enemyCar[0].pos[1];
		glPushMatrix();
		glTranslatef(x, y, 0);
		glBindTexture(GL_TEXTURE_2D, silhouetteAudiTexture);
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

float angle3;
void renderTaxi() {
	if(ga.enemyCar[1].carHit){
		int sw = 20;
		int sh = sw*2.044444;
		float x = ga.enemyCar[1].pos[0];
		float y = ga.enemyCar[1].pos[1];
		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef( angle3+=15.0, 0.0, 0.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, silhouetteTaxiTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255,255,255,255);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(-sw,-sh);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(-sw, sh);
		glTexCoord2f(1.0f, 0.0f); glVertex2i( sw, sh);
		glTexCoord2f(1.0f, 1.0f); glVertex2i( sw,-sh);
		glEnd();
		glPopMatrix();
	} else {
		int sw = 20;
		int sh = sw*2.044444;
		float x = ga.enemyCar[1].pos[0];
		float y = ga.enemyCar[1].pos[1];
		glPushMatrix();
		glTranslatef(x, y, 0);
		glBindTexture(GL_TEXTURE_2D, silhouetteTaxiTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255,255,255,255);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(-sw,-sh);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(-sw, sh);
		glTexCoord2f(1.0f, 0.0f); glVertex2i( sw, sh);
		glTexCoord2f(1.0f, 1.0f); glVertex2i( sw,-sh);
		glEnd();
		glPopMatrix();
	}
}

float angle4;
void renderMiniVan() {
	if(ga.enemyCar[2].carHit){
		int s = ga.carSize;
		float x = ga.enemyCar[2].pos[0];
		float y = ga.enemyCar[2].pos[1];
		glPushMatrix();
		glTranslatef(x, y, 0);
		glRotatef(angle4 += 15.0, 0.0, 0.0, 1.0);
		glBindTexture(GL_TEXTURE_2D, silhouetteMiniVanTexture);
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

	} else {
		int s = ga.carSize;;
		float x = ga.enemyCar[2].pos[0];
		float y = ga.enemyCar[2].pos[1];
		glPushMatrix();
		glTranslatef(x, y, 0);
		glBindTexture(GL_TEXTURE_2D, silhouetteMiniVanTexture);
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



void renderAudi2() {
	int s = ga.carSize;
	float x = ga.enemyCar[2].pos[0];
	float y = ga.enemyCar[2].pos[1];
	glPushMatrix();
	glTranslatef(x, y, 0);
	glBindTexture(GL_TEXTURE_2D, silhouetteAudiTexture);
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


void renderHeart() {
	for (int i = 0; i < 3; i++) {
		int sw = ga.heart[i].size*.9175;
		int sh = ga.heart[i].size;
		float x = ga.heart[i].pos[0];
		float y = ga.heart[i].pos[1];
		glPushMatrix();
		glTranslatef(x, y, 0);
		glBindTexture(GL_TEXTURE_2D, silhouetteHeartTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255,255,255,255);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(-sw,-sh);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(-sw, sh);
		glTexCoord2f(1.0f, 0.0f); glVertex2i( sw, sh);
		glTexCoord2f(1.0f, 1.0f); glVertex2i( sw,-sh);
		glEnd();
		glPopMatrix();
	}
}

void renderLives() {
	int sy = 13;
	int sx = (3.64102*sy);
	float x = (fxres*1.7)+20;
	float y = 805.0;
	glPushMatrix();
	glTranslatef(x, y, 0);
	glBindTexture(GL_TEXTURE_2D, silhouetteLivesTexture);
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

void renderLivesFrame() {
	int sy = 43;
	int sx = 38*1.466666;
	float x = (fxres*1.7)+20;
	float y = 785.0;
	glPushMatrix();
	glTranslatef(x, y, 0);
	glBindTexture(GL_TEXTURE_2D, silhouetteLivesFrameTexture);
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


void renderMainMenu() {
	float sw = fxres;
	float sh = fyres/2.0; 
	glPushMatrix();
	glTranslatef(256.0, 512, 0);
	glBindTexture(GL_TEXTURE_2D, silhouetteMainMenuTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(-sw,-sh);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-sw, sh);
	glTexCoord2f(1.0f, 0.0f); glVertex2i( sw, sh);
	glTexCoord2f(1.0f, 1.0f); glVertex2i( sw,-sh);
	glEnd();
	glPopMatrix();
}

void renderGameOver() {
	float sw = fxres;
	float sh = fyres/2.0; 
	glPushMatrix();
	glTranslatef(256.0, 512, 0);
	glBindTexture(GL_TEXTURE_2D, gameOverTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(-sw,-sh);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-sw, sh);
	glTexCoord2f(1.0f, 0.0f); glVertex2i( sw, sh);
	glTexCoord2f(1.0f, 1.0f); glVertex2i( sw,-sh);
	glEnd();
	glPopMatrix();
}

void totalTimeFunction() {
	static double t = 0.0;
	struct timespec start, end;
	clock_gettime(CLOCK_REALTIME, &start);
	int total = 0;
	Rect r;
	r.bot = 470;
	r.left = 215;
	r.center = 0;
	for (int i = 0; i < 10000; i++){
		total += i/2;
	}
	clock_gettime(CLOCK_REALTIME, &end);
	t += timeDiff(&start, &end);
	ggprint8b(&r, 16, 0xFFFF00, "%lf", t);
}

void drawBox(float x, float y, int s) {
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

int fireFrame = 0;
void renderFire() {
	float cx = fxres/2.0;
	float cy = fyres/2.0;
	float h = 128.0;
	float w = 128.0;
	float sh = 1.0/8.0;
	float sw = 1.0/4.0;
	//float h = ((float)1.0/8.0)*1000;
	//float w = ((float)1.0/4.0)*1000;
	glPushMatrix();
	glColor3f(1.0, 1.0, 1.0);
	glBindTexture(GL_TEXTURE_2D, fireTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	int ix = fireFrame % 8;
	int iy = 0;
	if (fireFrame >= 8)
		iy = 1;
	if (fireFrame >= 16)
		iy = 2;
	if (fireFrame >= 24)
		iy = 3;
	float tx = (float)ix / 4.0;
	float ty = (float)iy / 2.0;
	glBegin(GL_QUADS);
	glTexCoord2f(tx,    ty+sh);  glVertex2i(cx-w, cy-h);
	glTexCoord2f(tx,    ty);     glVertex2i(cx-w, cy+h);
	glTexCoord2f(tx+sw, ty);     glVertex2i(cx+w, cy+h);
	glTexCoord2f(tx+sw, ty+sh);  glVertex2i(cx+w, cy-h);
	glEnd();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_2D, 0);
	glDisable(GL_ALPHA_TEST);
}

void startFireTime(){
	clock_gettime(CLOCK_REALTIME, &fireTime);
}

void fireAnimation() {
	float delay = 0.1;
	clock_gettime(CLOCK_REALTIME, &timeCurrent);
	double timeSpan = timeDiff(&fireTime, &timeCurrent);
	if(timeSpan > delay) {
		++fireFrame;
		cout << fireFrame << endl;
		if(fireFrame >= 32)
			fireFrame -= 32;
		clock_gettime(CLOCK_REALTIME, &fireTime);	
	}
}

void startCountDownTimer() {
	clock_gettime(CLOCK_REALTIME, &countDownTime); 
}

int inc= 0;
float delay = 1.0;

void renderCountDown(bool &countDownBool) {
	//render 
	int sx = 46;
	int sy = 79;
	if(inc == 3){
		sx = 130;
		sy = sx*0.509;
	}
	float x = (fxres/2.0) + 140;
	float y = (fyres/2.0) + 200.0;
	glPushMatrix();
	glTranslatef(x, y, 0);
	glBindTexture(GL_TEXTURE_2D, countDownTexture[inc]);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255,255,255,255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(-sx,-sy);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(-sx, sy);
	glTexCoord2f(1.0f, 0.0f); glVertex2i( sx, sy);
	glTexCoord2f(1.0f, 1.0f); glVertex2i( sx,-sy);
	glEnd();
	glPopMatrix();
	//
	clock_gettime(CLOCK_REALTIME, &currentCountTime);
	double timeSpan = timeDiff(&countDownTime, &currentCountTime);
	if(timeSpan > delay) {
		delay +=1;	
		inc++;
		//cout << "Timer has hit" << endl;
		if (inc == 4){
			countDownBool = false;
			inc = 0;
			delay = 1.0;
		}

	}
	//countDownImage[i];
}
