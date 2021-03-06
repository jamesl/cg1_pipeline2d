/*
 *  setPixel.c
 *  2DFramework
 *
 *  Created by Joe Geigel on 9/25/07.
 *  Copyright 2007 __MyCompanyName__. All rights reserved.
 *
 */

/**
* setPixel -- openGL routine for setting a pixel...Color version
 *
 */

#include <GL/glu.h>

extern int screenHeight;
extern int screenWidth;

void setPixel (int x, int y, float r, float g, float b)
{
	GLubyte rgb[3];
	rgb[0] = (GLubyte)(r * 255);
	rgb[1] = (GLubyte)(g * 255);
	rgb[2] = (GLubyte)(b * 255);
	
	glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
	gluOrtho2D (0.0, (double)screenWidth, 0.0, (double)screenHeight);
	
	glRasterPos2i (x,y);
	glDrawBuffer (GL_FRONT);
	glDrawPixels (1, 1, GL_RGB, GL_UNSIGNED_BYTE, rgb);
	
	
}
