CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGL

all: srcfile

srcfile: srcfile.cpp alecS.cpp jorgeZ.cpp timers.cpp guillermoR.cpp joseV.cpp ianT.cpp
	g++ $(CFLAGS) srcfile.cpp timers.cpp  alecS.cpp jorgeZ.cpp guillermoR.cpp joseV.cpp ianT.cpp libggfonts.a -Wall $(LFLAGS) -osrcfile -lX11 -lGL -lGLU -lm

clean:
	rm -f srcfile

