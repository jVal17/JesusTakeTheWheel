CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGL -lGLU -lm -Wall -Wextra -D USE_OPENAL_SOUND
LIB = /usr/lib/x86_64-linux-gnu/libopenal.so /usr/lib/x86_64-linux-gnu/libalut.so

SOURCES = srcfile.cpp timers.cpp alecS.cpp jorgeZ.cpp guillermoR.cpp joseV.cpp ianT.cpp

all: srcfile

srcfile: $(SOURCES)
	g++ $(CFLAGS) $(SOURCES) libggfonts.a $(LIB) $(LFLAGS) -osrcfile

clean:
	rm -f srcfile

