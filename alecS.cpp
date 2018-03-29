// Alec Sherlock
// This is muh file.
// Soft Eng 2018

#include "alecS.h"

ALuint alSource[5];
ALuint alBuffer[5];

//create volume
static float Volume = 1.0f;
void getVolume(float V)
{
		Volume = V;
}

void printText()
{
    Rect r;
    r.bot = 200;
    r.left = 100;
    r.center = 0;
    ggprint8b(&r, 16, 0x00ff0000, "Text");
    ggprint8b(&r, 16, 0x00ff0000, "by Alec Sherlock");
    glEnd();
}

void drawDatBox1() 
{
    static double t = 0.0;
    struct timespec ftimeStart, ftimeEnd;
    clock_gettime(CLOCK_REALTIME, &ftimeStart);
//------^^ setting up the clock time


    glColor3f(0.25, 0.0, 0.25);
    glPushMatrix();
    glTranslatef(-(pow(14.0, 2.0)), pow(20.0,2.0), 0.0);
//Start the box
    glBegin(GL_QUADS);
    glVertex2i(pow(19.0,2.0), pow(7.0,2.0));
    glVertex2i(pow(19.0,2.0),-(pow(7.0, 2.0)));
    glVertex2i(pow(23.0,2.0),-(pow(7.0, 2.0)));
    glVertex2i(pow(23.0,2.0),pow(7.0,2.0 ));
    glEnd();
    glPopMatrix();



    Rect r;
    r.bot = pow(20.0,2.0);
    r.left = pow(13.0,2.0);
    r.center = 0.0;

    clock_gettime(CLOCK_REALTIME, &ftimeEnd);
    t += timeDiff(&ftimeStart, &ftimeEnd);
    ggprint8b(&r, 16, 0x00ff0000, "Box with pow");
    ggprint8b(&r, 16, 0x00ff0000, "%lf",  t );
}

void drawDatBox2()
{
    static double t = 0.0;
    struct timespec ftimeStart, ftimeEnd;
    clock_gettime(CLOCK_REALTIME, &ftimeStart);
// -------^^ setting up clock time again ^^ ---------
    glColor3f(0.5, 0.01, 0.01);
    glPushMatrix();
    glTranslatef(-(14*14), (18*18), 0.0);
//Start the box
    glBegin(GL_QUADS);
    glVertex2i((17*17), (7*7));
    glVertex2i((17*17),-(7*7));
    glVertex2i((21*21),-(7*7));
    glVertex2i((21*21), (7*7));
    glEnd();
    glPopMatrix();

    Rect r;
    r.bot = (18*18);
    r.left = (13*13);
    r.center = 0.0;

    clock_gettime(CLOCK_REALTIME, &ftimeEnd);
    t+= timeDiff(&ftimeStart, &ftimeEnd);
// increment the total time and display
    ggprint8b(&r, 16, 0x00aa00aa, "%lf", t);
    ggprint8b(&r, 16, 0x00aa00aa, "Box w/o pow");


}
//----------------------------------------------------------

//Starting Open AL stuff.

void initSounds() {
    // catch errors and set up listener 
    alutInit( 0, NULL );
    if (alGetError() != AL_NO_ERROR){
        printf("Error: alutInit()\n")
    }
    alGetError();
    
    float orientVec[6] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListener3fv(AL_ORIENTATION, orientVec);
    alListenerf(AL_GAIN, 1.0f);

}

void clearSounds() {

    //  clear the sources and buffers
        alDeleteSources(1, &alSource[0]);
        alDeleteSources(1, &alSource[1]);
        alDeleteSources(1, &alSource[2]);
        alDeleteBuffers(1, &alBuffer[0]);
        alDeleteBuffers(1, &alBuffer[1]);
        alDeleteBuffers(1, &alBuffer[2]);

    // get context and device

        ALCcontext *Context = alcGetCurrentContext();
        ALCdevice *Device = alcGetContextsDevice(Context);

    //make null and destroy
        alcMakeContextCurrent(NULL);
        alcDestroyContext(Context);

    //close
        alcCloseDevice(Device);
}

void bringInSounds(){
    //car crashing sounds
    alBuffer[0] = alutCreateBufferFromFile("./sounds/car-crash.wav");
    alGenSources(1, &alSource[0]);
    alSourcei(alSource[0], AL_BUFFER, alBuffer[0]);

    //in game music
    alBuffer[1] = alutCreateBufferFromFile("./sounds/inGame.wav");
    alGenSources(1, &alSource[1]);
    alSourcei(alSource[1], AL_BUFFER, alBuffer[1]);

    // main menu music

    alBuffer[2] = alutCreateBufferFromFile("./sounds/mainMenue.wav");
    alGenSources(1, &alSource[2]);
    alSourcei(alSource[2], AL_BUFFER, alBuffer[2]);

    // pause music
    alBuffer[3] = alutCreateBufferFromFile("./sounds/pause.wav");
    alGenSources(1, &alSource[0]);
    alSourcei(alSource[3], AL_BUFFER, alBuffer[3]);

    //car starting sound
    alBuffer[4] = alutCreateBufferFromFile("./sounds/startCar.wav");
    alGenSources(1, &alSource[4]);
    alSourcei(alSource[4], AL_BUFFER, alBuffer[4]);

}

void play_sounds(int soundOption)
{
    //Set volume and pitch.
    alSourcef(alSource[soundOption], AL_GAIN, Volume);
    alSourcef(alSource[soundOption], AL_PITCH, 1.0f);
    alSourcei(alSource[soundOption], AL_LOOPING, AL_FALSE);

    
    if (alGetError() != AL_NO_ERROR) {
        printf("Error: Setting Source\n");
    }
    alSourcePlay(alSource[soundOption]);
}



//play sound over loop
void play_sounds(int soundOption, int loop)
{
    //Set volume and pitch.
    alSourcef(alSource[soundOption], AL_GAIN, Volume);
    alSourcef(alSource[soundOption], AL_PITCH, 1.0f);
    alSourcei(alSource[soundOption], AL_LOOPING, AL_TRUE);

    
    if (alGetError() != AL_NO_ERROR) {
        printf("Error: Setting Source\n");
    }
    alSourcePlay(alSource[soundOption]);
}

//mute sounds
void play_sounds(int soundOption, char mute)
{
    //Set volume and pitch.
    alSourcef(alSource[soundOption], AL_GAIN, 0.0f);
    alSourcef(alSource[soundOption], AL_PITCH, 0.0f);
    alSourcei(alSource[soundOption], AL_LOOPING, AL_FALSE);

    
    if (alGetError() != AL_NO_ERROR) {
        printf("Error: Setting Source\n");
    }
    alSourcePlay(alSource[soundOption]);
}
