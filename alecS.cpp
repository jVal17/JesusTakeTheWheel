// Alec Sherlock
// This is muh file.
// Soft Eng 2018


#include <stdio.h>
#include <string,h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#ifdef USE_OPENAL_SOUND
#include </usr/include/AL/alut.h>
#endif

int main()
{
    	
#ifdef USE_OPENAL_SOUND
	//init the OPENAL
	alutInit(0,NULL);
	//give error if invalid setup
	if (alGetError() != AL_NO_ERROR) 
	{
		printf("Error: failed openAL init\n");
		return 0;
	}
	// clear the error
	alGetError();
	//
	//
	//Setting up the listener vector (floating point values)
	float vec[6] = {0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f};
	// setting up Listener position
	alListener3f(AL_POSITION, 0.0f, 0.0f, 0.0f);
	// setting up listener orientation using vectors
	alListenerfv(AL_ORIENTATION, vec);
	// Set up listener gain
	alListenerf(AL_GAIN, 1.0f);
	//
	//
	//Buffer is responsible for holding sound data
	ALuint alBuffer;

	alBuffer = alutCreateBufferFromFile("./test.wav");
	
	//Sound Source information
	ALuint alSource;
	// make a single source and store into buffer
	alGenSources(1, &alSource);
	alSourcei(alSource, AL_BUFFER, alBuffer);
	// set vol and pitch
	alSourcef(alSource, AL_GAIN, 1.0f);
	alSourcef(alSource, AL_PITCH, 1.0f);
	alSource (alSource, AL_LOOPING, AL_FALSE);
		

}


