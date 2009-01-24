/**
 * Routines that you'll need to write
 *
 */

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>         /* glut.h includes gl.h and glu.h*/
#endif
#define abs(x) ((x) < 0 ? (-1*(x)) : (x))
#define swap(a,b) { int temp; temp = a; a = b; b = temp; }
#include <stdio.h>

void setPixel (int x, int y);

/* 
 * Draw line from x1, y1 to x2, y2 
 */

void drawLine( int x1, int y1, int x2, int y2) {
  /* Your task is to rewrite this using only calls to setPixel() */
	// midpoint for N-NE
	int incE, incNE, x, y, d, xmax;
	int dy = y2 - y1, dx = x2 - x1;
	bool swap = false;
	// |slope| > 1, swap x's and y's
	// so that we draw a pixel for each y
	if(abs(dy) > abs(dx)) {
		swap = true;
		swap(dy,dx);
		swap(x1,y1);
		swap(x2,y2);	
	} 
	// move from lower x (or y) to higher
	if(x2 < x1) {
		swap(x1,x2);
		swap(y1,y2);
	}
	// invert both dx and dy so that we 
	// are moving up in the x (or y) 
	if(dx < 0) { 
		dy = -1*dy; 
		dx = -1*dx;
	}
		
	incE = 2 * abs(dy);
	// dx should be pos already
	incNE = 2 * (abs(dy) - dx);

	d = incE - dx; /* 2*dy - dx */

	for( x = x1, y = y1; x <= x2; ++x ) {
		if(!swap) // x is x and y is y 
			setPixel( x, y );
		else	  // x is really y...
			setPixel( y, x );

		if( d <= 0 ) { /* choose E,N,S,W */
			d += incE;
		} else {
			/* choose NE,SE,NW,SW */
			if(dy > 0) {
				y++;
			} else {
				y--;
			}
			d += incNE;
		}
	}
}


