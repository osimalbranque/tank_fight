#LDFLAGS=-F/Library/Frameworks -framework SDL2 -framework Cocoa -I/System/Library/Frameworks/OpenGL.framework/Headers -framework OpenGL
#CFLAGS=-g -Wall ~dbarthou/bin -I/Library/Frameworks/SDL2.framework/Headers  -I/System/Library/Frameworks/OpenGL.framework/Headers
CFLAGS=-g -Wall `sdl2-config --cflags`
LDFLAGS=-g -Wall `sdl2-config --libs`

all: tank

tank: engine.o timer.o graphics.o tank.o
	gcc -o $@ ${LDFLAGS} $^

engine.o: engine.h
graphics.o: engine.h graphics.h timer.h
tank.o: engine.h graphics.h timer.h
timer.o: timer.h

.c.o:
	gcc -c ${CFLAGS} $<

clean: 
	rm tank *.o *~
