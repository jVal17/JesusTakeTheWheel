CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGL

all: srcfile

srcfile: srcfile.cpp
	g++ $(CFLAGS) srcfile.cpp alecS.cpp guillermoR.cpp joseV.cpp ianT.cpp libggfonts.a -Wall $(LFLAGS) -osrcfile -lX11 -lGL -lGLU -lm

clean:
	rm -f srcfile

