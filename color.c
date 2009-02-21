
#include "setPixel.h"
#include "color.h"

color currentcolor;
color clearcolor;

/**
 * 2 argument setPixel allows me to use
 * code from assignment 2 without changing
 * setPixel calls
 */
void setPixel(int x,int y,color c) {
	setPixel(x,y,c.r,c.g,c.b);
}

/**
 * return current drawing color
 */
color getcolor() {
	return currentcolor;
}

/**
 * return current clear color
 */
color getclearcolor() {
	return clearcolor;
}

/**
 * set current drawing color
 */
void setcolor(float r,float g,float b) {
	currentcolor.r=r;
	currentcolor.g=g;
	currentcolor.b=b;
}

/**
 * set current clear color
 */
void setclearcolor(float r,float g,float b) {
	clearcolor.r=r;
	clearcolor.g=g;
	clearcolor.b=b;
}

