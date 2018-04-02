CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGL -lGLU -lm -Wall -Wextra

SOURCES = srcfile.cpp timers.cpp alecS.cpp jorgeZ.cpp guillermoR.cpp joseV.cpp ianT.cpp

all: srcfile

srcfile: $(SOURCES)
	g++ $(CFLAGS) $(SOURCES) libggfonts.a $(LFLAGS) -osrcfile

clean:
	rm -f srcfile

