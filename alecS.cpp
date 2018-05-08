// Alec Sherlock
// This is muh file.
// Soft Eng 2018

#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif



#ifdef USE_OPENAL_SOUND
ALuint alSource;
ALuint mainSource;
ALuint pauseSource;
ALuint gameOverSource;
ALuint inGameSource;
ALuint alBuffer;

extern void initSounds() 
{
    alutInit(0, NULL);
    if ( alGetError() != AL_NO_ERROR ) {
	printf("error initializing sound\n");
	return;
    }
    alGetError();

    float vec[6] = { 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f };
    alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
    alListenerfv(AL_ORIENTATION, vec);
    alListenerf(AL_GAIN, 1.0f);

}
extern void cleanSounds()
{
    ALCcontext *Context = alcGetCurrentContext();
    ALCdevice *Device = alcGetContextsDevice(Context);

    alcMakeContextCurrent(NULL);

    alcDestroyContext(Context);

    alcCloseDevice(Device);

}
extern void playMain()
{
    alBuffer = alutCreateBufferFromFile("./sound/mainMenu.wav");
    alGenSources(1, &mainSource);
    alSourcei(mainSource, AL_BUFFER, alBuffer);

    alSourcef(mainSource, AL_GAIN, .30f);
    alSourcef(mainSource, AL_PITCH, 1.0f);
    alSourcei(mainSource, AL_LOOPING, AL_TRUE);
    if (alGetError() != AL_NO_ERROR){
        printf("ERROR setting sound source\n");
        return ;
    }
    alSourcePlay(mainSource);
}
extern void stopMain()
{
    alSourcePause(mainSource);
    return;
}
extern void resumeMain()
{
    alSourcePlay(mainSource);

}
extern void playPause()
{
    alBuffer = alutCreateBufferFromFile("./sound/pause.wav"); // INSERT SOUND FILE
    alGenSources(1, &pauseSource);
    alSourcei(pauseSource, AL_BUFFER, alBuffer);

    alSourcef(pauseSource, AL_GAIN, .30f);
    alSourcef(pauseSource, AL_PITCH, 1.0f);
    alSourcei(pauseSource, AL_LOOPING, AL_TRUE);
        if (alGetError() != AL_NO_ERROR){
        printf("ERROR setting sound source\n");
        return ;
    }
    alSourcePlay(pauseSource);
}
extern void stopPause()
{
    alSourcePause(pauseSource);
    return;
}
extern void resumePause()
{
    alSourcePlay(pauseSource);

}
extern void playMenuSelect()
{
    alBuffer = alutCreateBufferFromFile("./sound/menuSelect.wav"); // INSERT SOUND FILE
    
    alGenSources(1 , &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR setting sound source\n");
	return;
    }

    alSourcePlay(alSource);

}
extern void carExplodeOne()
{
    alBuffer = alutCreateBufferFromFile(); // INSERT SOUND FILE
    
    alGenSources(1 , &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR setting sound source\n");
	return;
    }

    alSourcePlay(alSource);  
}

extern void carExplodeTwo()
{
    alBuffer = alutCreateBufferFromFile(); // INSERT SOUND FILE
    
    alGenSources(1 , &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR setting sound source\n");
	return;
    }

    alSourcePlay(alSource);  
}
extern void carExplodeThree()
{
    alBuffer = alutCreateBufferFromFile(); // INSERT SOUND FILE
    
    alGenSources(1 , &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR setting sound source\n");
	return;
    }

    alSourcePlay(alSource);  
}
extern void healthLossOne()
{
    alBuffer = alutCreateBufferFromFile(); // INSERT SOUND FILE
    
    alGenSources(1 , &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR setting sound source\n");
	return;
    }

    alSourcePlay(alSource);  
}
extern void healthLossTwo()
{
    alBuffer = alutCreateBufferFromFile(); // INSERT SOUND FILE
    
    alGenSources(1 , &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR setting sound source\n");
	return;
    }

    alSourcePlay(alSource);  
}
extern void healthLossThree()
{
    alBuffer = alutCreateBufferFromFile(); // INSERT SOUND FILE
    
    alGenSources(1 , &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR setting sound source\n");
	return;
    }

    alSourcePlay(alSource);  
}
extern void playGameOver()
{
    alBuffer = alutCreateBufferFromFile(); // INSERT SOUND FILE
    alGenSources(1, &gameOverSource);
    alSourcei(gameOverSource, AL_BUFFER, alBuffer);

    alSourcef(gameOverSource, AL_GAIN, .30f);
    alSourcef(gameOverSource, AL_PITCH, 1.0f);
    alSourcei(gameOverSource, AL_LOOPING, AL_TRUE);
        if (alGetError() != AL_NO_ERROR){
        printf("ERROR setting sound source\n");
        return ;
    }
    alSourcePlay(gameOverSource);
}
extern void stopGameOver()
{
    alSourcePause(gameOverSource);
    return;
}
extern void resumeGameOver()
{
    alSourcePlay(gameOverSource);

}

extern void playInGame()
{
    alBuffer = alutCreateBufferFromFile(); // INSERT SOUND FILE
    alGenSources(1, &inGameSource);
    alSourcei(inGameSource, AL_BUFFER, alBuffer);

    alSourcef(inGameSource, AL_GAIN, .30f);
    alSourcef(inGameSource, AL_PITCH, 1.0f);
    alSourcei(inGameSource, AL_LOOPING, AL_TRUE);
        if (alGetError() != AL_NO_ERROR){
        printf("ERROR setting sound source\n");
        return ;
    }
    alSourcePlay(inGameSource);
}
extern void stopInGame()
{
    alSourcePause(inGameSource);
    return;
}
extern void resumeInGame()
{
    alSourcePlay(inGameSource);

}
extern void carRevOne()
{
    alBuffer = alutCreateBufferFromFile(); // INSERT SOUND FILE
    
    alGenSources(1 , &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR setting sound source\n");
	return;
    }

    alSourcePlay(alSource);  
}

extern void carRevTwo()
{
    alBuffer = alutCreateBufferFromFile(); // INSERT SOUND FILE
    
    alGenSources(1 , &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR setting sound source\n");
	return;
    }

    alSourcePlay(alSource);  
}
extern void carRevThree()
{
    alBuffer = alutCreateBufferFromFile(); // INSERT SOUND FILE
    
    alGenSources(1 , &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR setting sound source\n");
	return;
    }

    alSourcePlay(alSource);  
}

extern void startGame()
{
    alBuffer = alutCreateBufferFromFile(); //Insert HOLY.WAV

    alGenSources(1, &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR setting sound source\n");
	return;
    }

    alSourcePlay(alSource);

}

extern void playBrake()
{
    alBuffer = alutCreateBufferFromFile(); //Insert SOUND

    alGenSources(1, &alSource);
    alSourcei(alSource, AL_BUFFER, alBuffer);

    alSourcef(alSource, AL_GAIN, 1.0f);
    alSourcef(alSource, AL_PITCH, 1.0f);
    alSourcei(alSource, AL_LOOPING, AL_FALSE);

    if (alGetError() != AL_NO_ERROR) {
	printf("ERROR setting sound source\n");
	return;
    }

    alSourcePlay(alSource); 
}

#endif