# assignment 2 makefile

CC = g++

CFLAGS=-ggdb

LDFLAGS=-framework GLUT -framework OpenGL

all: main

main: myFunctions.o Matrix.o

myFunctions.o: drawPolygon.o Matrix.o

color.o: setPixel.o

drawPolygon.o: color.o

clean:
	rm -f main *.o

