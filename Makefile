CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGL

all: srcfile

<<<<<<< HEAD
srcfile: srcfile.cpp alecS.cpp jorgeZ.cpp timers.cpp guillermoR.cpp joseV.cpp ianT.cpp
	g++ $(CFLAGS) srcfile.cpp timers.cpp  alecS.cpp jorgeZ.cpp guillermoR.cpp joseV.cpp ianT.cpp libggfonts.a -Wall $(LFLAGS) -osrcfile -lX11 -lGL -lGLU -lm
=======
srcfile: srcfile.cpp timers.cpp alecS.cpp jorgeZ.cpp guillermoR.cpp joseV.cpp ianT.cpp
	g++ $(CFLAGS) srcfile.cpp timers.cpp alecS.cpp jorgeZ.cpp guillermoR.cpp joseV.cpp ianT.cpp libggfonts.a -Wall $(LFLAGS) -osrcfile -lX11 -lGL -lGLU -lm
>>>>>>> de0f692d790b3a27f563b86f6bef345d5206d0ad

clean:
	rm -f srcfile

