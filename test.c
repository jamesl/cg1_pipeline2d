/*
 *  2DPipeline
 *
 *  This program tests the 2D rendering pipeline.  
 *  
 *
 */

#ifdef __APPLE__
#include <GLUT/glut.h>         /* glut.h includes gl.h and glu.h*/
#else
#include <GL/glut.h>
#endif
#include <cstdlib>
#include <cmath>
#include "myFunctions.h"

int screenHeight = 500;
int screenWidth = 500;

int displayNumber = 0;


/* 
* Callback function for mouse interaction 
 */

void mouse( int button, int state, int x, int y ) {
	
	/* 
    * If state is not checked, we get two events for each mouse button
	 * usage, one for pressing it, one for releasing it 
	 */
	if ( state==GLUT_UP ) {
		displayNumber++;
		glutPostRedisplay();
	}
	
}

void drawHouse(void) {
	myBegin(GL_POLYGON); //roof
		myColor3f(1.0,0.0,0.0);
		myVertex2f(0.0,1.0);
		myVertex2f(0.5,1.5);
		myVertex2f(1.0,1.0);
	myEnd();

	myBegin(GL_POLYGON);
		// house
		myColor3f(0.0,1.0,0.0);
		myVertex2f(0.0,1.0);
		myVertex2f(1.0,1.0);
		myVertex2f(1.0,0.0);
		myVertex2f(0.0,0.0);
	myEnd();

	myBegin(GL_POLYGON);
		// door
		myColor3f(0.0,0.0,1.0);
		myVertex2f(0.2,0.0);
		myVertex2f(0.5,0.0);
		myVertex2f(0.5,0.65);
		myVertex2f(0.2,0.65);
	myEnd();
}

void drawbadcircle(float x,float y,float r) {
        glBegin(GL_POLYGON);
        for(float theta=0;theta<2.0*3.14159;theta+=3.14159/6.0) {
                glVertex2f(cos(theta)*r+x,sin(theta)*r+y);
        }
        glEnd();
}


void drawCar(void) {
	glColor4f(.1,0.5,0.1,1.0); 
	glBegin(GL_POLYGON); 
		glVertex2f(-.4,0.0); 
		glVertex2f(-.4,0.15); 
		glVertex2f(-.35,0.3); 
		glVertex2f(.1,0.3); 
		glVertex2f(.15,0.225); 
		glVertex2f(.4,0.17); 
		glVertex2f(.4,0.0); 
	glEnd(); 
	glColor4f(0.0,0.0,0.0,1.0); 
	drawbadcircle(-.2,0.0,.1); 
	drawbadcircle(.2,0.0,.1); 

}

void drawPolys(void) {
	myMatrixMode(GL_MODELVIEW);
	myScalef(50.0,50.0);

	drawHouse();

	myPopMatrix();
	myTranslatef(-50.0,0.0);
	myScalef(30.0,30.0);
	
	drawHouse();

	myPopMatrix();
	
	myTranslatef(0.0,-100.0);	
	myScalef(40.0,40.0);

	drawHouse();

	glFlush();
}

void display( void ) {
	
     /* 
	* Set clear color to gray 
     */
    myClearColor ( 0.8, 0.8, 0.8, 0.0 );
	
    /* 
	* Clear screen window 
     */
    myClear( GL_COLOR_BUFFER_BIT );
		
	myLoadIdentity();
	myPushMatrix();
	
	/* 
	 * plain old polygon test
	 */
	if ( (displayNumber % 4) == 1) {
		
		/* default clipping */
		myOrtho2D( -100.0, 100.0, -100.0, 100.0 );
		
		/* default viewport */
		myViewport( 0, 0, screenWidth, screenHeight );
	
		myPushMatrix();

		/* draw the polys */
		drawPolys();
	}
	else if ( (displayNumber % 4) == 2) {
		
		/* clipping test */
		myOrtho2D( -65.0, 75.0, -80.0, 65.0 );
		
		/* default viewport */
		myViewport( 0, 0, screenWidth, screenHeight );
		
		/* flip screen around! */
		myScalef(-1.0,1.0);
		myPushMatrix();
		

		/* draw the polys */
		drawPolys();
		
    }
	else if ( (displayNumber % 4) == 3) {
		
		/* default clipping */
		myOrtho2D( -100.0, 100.0, -100.0, 100.0 );
		
		/* default viewport */
		myViewport( 0, 0, screenWidth, screenHeight );

		/* rotate screen */
		myRotatef(15.0);
		myPushMatrix();

		/* draw the tranformed polys */
		drawPolys();
	}
	
	else /* displayNumber == 0 */ {
		
		/* default clipping */
		myOrtho2D( -100.0, 100.0, -100.0, 100.0 );
		
		/* default viewport */
		myViewport( 0, 0, screenWidth, screenHeight );

		myRotatef(-15.0);
		myScalef(.5,.5);
		myPushMatrix();
		myRotatef(15.0);
		myPushMatrix();

		/* draw the tranformed polys */
		drawPolys();
	
		
	}
	
	/* 
     * Flush GL buffers to the display   
     */
    glFlush( );
	
}


/* 
* Main routine - GLUT setup and initialization 
 */

int main( int argc, char** argv ) {
	
	/* 
    * Initialize mode and open a window in upper 
	 * left corner of screen 
	 */
	
	glutInit( &argc, argv ); 
	glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB );
	glutInitWindowSize( screenWidth, screenHeight );
	glutInitWindowPosition( 0, 0 );
	glutCreateWindow( "Draw World" ); 
	
	glutMouseFunc( mouse );
	glutDisplayFunc( display );
	
	glutMainLoop();
	
	return 0;
	
}
