// used for storing colors

#ifndef _COLOR_H
#define _COLOR_H
typedef struct {
	float r;
	float g;
	float b;
} color;

color getcolor();
color getclearcolor();
void setcolor(float,float,float);
void setclearcolor(float,float,float);

void setPixel(int,int);
#endif
