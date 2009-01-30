# assignment 2 makefile

CC = g++

CFLAGS=-ggdb

LDFLAGS=-lglut -lGL -lm

all: main test

main: myFunctions.o Matrix.o color.o setPixel.o drawPolygon.o clipPolygon.o

test: myFunctions.o Matrix.o color.o setPixel.o drawPolygon.o clipPolygon.o

myFunctions.o: drawPolygon.o Matrix.o color.o

color.o: setPixel.o

drawPolygon.o: color.o

clean:
	rm -f main *.o

