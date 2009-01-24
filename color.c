
#include "setPixel.h"
#include "color.h"

color currentcolor;
color clearcolor;

void setPixel(int x,int y) {
	setPixel(x,y,currentcolor.r,currentcolor.g,currentcolor.b);
}



color getcolor() {
	return currentcolor;
}

color getclearcolor() {
	return clearcolor;
}

void setcolor(float r,float g,float b) {
	currentcolor.r=r;
	currentcolor.g=g;
	currentcolor.b=b;
}

void setclearcolor(float r,float g,float b) {
	clearcolor.r=r;
	clearcolor.g=g;
	clearcolor.b=b;
}

