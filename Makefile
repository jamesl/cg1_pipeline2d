# assignment 2 makefile

CC = g++

CFLAGS=-ggdb

LDFLAGS=-framework GLUT -framework OpenGL

all: main

main: myFunctions.o myPipeline.o Matrix.o

clean:
	rm -f main *.o

