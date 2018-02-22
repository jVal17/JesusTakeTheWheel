CFLAGS = -I ./include
LFLAGS = -lrt -lX11 -lGL

all: background

background: background.cpp
	g++ $(CFLAGS) background.cpp libggfonts.a -Wall $(LFLAGS) -lX11 -lGL -lGLU -lm

clean:
	rm -f background a.out


