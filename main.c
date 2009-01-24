/*
 *  2DPipeline
 *
 *  This program tests the 2D rendering pipeline.  
 *  
 *
 */


#include <GLUT/glut.h>         /* glut.h includes gl.h and glu.h*/
#include <cstdlib>
#include "myFunctions.h"

int screenHeight = 500;
int screenWidth = 500;

int displayNumber = 1;


/*
 * Callback for keystrokes
 */
void key (unsigned char key, int x, int y)
{
	if ((key == 'C') || (key == 'c')) displayNumber = 2; // clip
	if ((key == 'P') || (key == 'p')) displayNumber = 1; // polygon
	if ((key == 'T') || (key == 't')) displayNumber = 3; // transform
	if ((key == 'V') || (key == 'v')) displayNumber = 0; // viewport
	
	if ((key == 'Q') || (key == 'q')) exit(0); // quit

	
	glutPostRedisplay();
}


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


/* 
* Function that draws the entire contents of the modeled world.
 * Used in the "display" callback function.
 */

void drawPolys( void ) {
	
	/* 
    * Draw a red triangle
	*/
	myLoadIdentity();
	myBegin( GL_POLYGON );
	myColor3f( 1.0, 0.0, 0.0 );
	myVertex2f( -75.0, 25.0 );
	myVertex2f( -25.0, 25.0 );
	myVertex2f( -50, 75.0 );
	myEnd();
	
	/* 
	 * Draw a white square 	 
	 */
	myBegin( GL_POLYGON );
	myColor3f( 1.0, 1.0, 1.0 );
	myVertex2f( 25.0, 25.0 );
	myVertex2f( 75.0, 25.0 );
	myVertex2f( 75.0, 75.0 );
	myVertex2f( 25.0, 75.0 );
	myEnd();
	
	/* 
	 * Draw a blue otcagon
	 */
	myBegin( GL_POLYGON );
	myColor3f( 0.0, 0.0, 1.0 );
	myVertex2f( -75.0, -75.0 );
	myVertex2f( -65.0, -85.0 );
	myVertex2f( -45.0, -85.0 );
	myVertex2f( -25.0, -75.0 );
	myVertex2f( -25.0, -45.0 );
	myVertex2f( -45.0, -25.0 );
	myVertex2f( -65.0, -25.0 );
	myVertex2f( -75.0, -45.0 );
	myEnd();
	
	/* 
		* Draw a green star
	 * .1, .1 
	 */
	myBegin( GL_POLYGON );
	myColor3f( 0.0, 1.0, 0.0 );
	myVertex2f( 50.0, -10.0 );
	myVertex2f( 40.0, -35.0 );
	myVertex2f( 10.0, -35.0 );
	myVertex2f( 40.0, -60.0 );
	myVertex2f( 10.0, -90.0 );
	myVertex2f( 50.0, -75.0 );
	myVertex2f( 90.0, -90.0 );
	myVertex2f( 60.0, -60.0 );
	myVertex2f( 90.0, -35.0 );
	myVertex2f( 60.0, -35.0 );
	myEnd();
	
}



void drawTPolys( void ) {
	
	/* 
    * Draw a red triangle rotated
	 */
	myLoadIdentity();
	myRotatef (45.0);
	myBegin( GL_POLYGON );
	myColor3f( 1.0, 0.0, 0.0 );
	myVertex2f( -75.0, 25.0 );
	myVertex2f( -25.0, 25.0 );
	myVertex2f( -50, 75.0 );
	myEnd();
	
	/* 
		* Draw a white square translated	 
	 */
	myLoadIdentity();
	myTranslatef (-80.0, -75.0);
	myBegin( GL_POLYGON );
	myColor3f( 1.0, 1.0, 1.0 );
	myVertex2f( 25.0, 25.0 );
	myVertex2f( 75.0, 25.0 );
	myVertex2f( 75.0, 75.0 );
	myVertex2f( 25.0, 75.0 );
	myEnd();
	
	/* 
		* Draw a blue otcagon scaled
	 */
	myLoadIdentity();
	myScalef (0.75, 0.5);
	myBegin( GL_POLYGON );
	myColor3f( 0.0, 0.0, 1.0 );
	myVertex2f( -75.0, -75.0 );
	myVertex2f( -65.0, -85.0 );
	myVertex2f( -45.0, -85.0 );
	myVertex2f( -25.0, -75.0 );
	myVertex2f( -25.0, -45.0 );
	myVertex2f( -45.0, -25.0 );
	myVertex2f( -65.0, -25.0 );
	myVertex2f( -75.0, -45.0 );
	myEnd();
	
	/* 
		* Draw a green star translated, scaled, rotates, then scaled back
	 * .1, .1 
	 */
	myLoadIdentity();
	myTranslatef (50.0, -50.0);
	myScalef (0.2, 0.2);
	myRotatef (90.0);
	myTranslatef (-50.0, 50.0);
	myBegin( GL_POLYGON );
	myColor3f( 0.0, 1.0, 0.0 );
	myVertex2f( 50.0, -10.0 );
	myVertex2f( 40.0, -35.0 );
	myVertex2f( 10.0, -35.0 );
	myVertex2f( 40.0, -60.0 );
	myVertex2f( 10.0, -90.0 );
	myVertex2f( 50.0, -75.0 );
	myVertex2f( 90.0, -90.0 );
	myVertex2f( 60.0, -60.0 );
	myVertex2f( 90.0, -35.0 );
	myVertex2f( 60.0, -35.0 );
	myEnd();
	
}


/* This will display the original world when the displaynumber is
* odd and an altered world when it is even.  "gluOrtho2D" is used
* to determine which portion of the world is displayed. "glViewport"
* is used to determine WHERE the selected portion will be displayed.
*/

void display( void ) {
	
	/* 
	* Set clear color to gray 
     */
    myClearColor ( 0.8, 0.8, 0.8, 0.0 );
	
    /* 
	* Clear screen window 
     */
    myClear( GL_COLOR_BUFFER_BIT );
		
	
	/* 
	 * plain old polygon test
	 */
	if ( (displayNumber % 4) == 1) {
		
		/* default clipping */
		myOrtho2D( -100.0, 100.0, -100.0, 100.0 );
		
		/* default viewport */
		myViewport( 0, 0, screenWidth, screenHeight );

		/* draw the polys */
		drawPolys();
	}
	else if ( (displayNumber % 4) == 2) {
		
		/* clipping test */
		myOrtho2D( -65.0, 75.0, -80.0, 65.0 );
		
		/* default viewport */
		myViewport( 0, 0, screenWidth, screenHeight );
		
		/* draw the polys */
		drawPolys();
		
    }
	else if ( (displayNumber % 4) == 3) {
		
		/* default clipping */
		myOrtho2D( -100.0, 100.0, -100.0, 100.0 );
		
		/* default viewport */
		myViewport( 0, 0, screenWidth, screenHeight );
		
		/* draw the tranformed polys */
		drawTPolys();
	}
	
	else /* displayNumber == 0 */ {
		
		/* default clipping */
		myOrtho2D( -100.0, 100.0, -100.0, 100.0 );
		
		/* have some fun with the view port */
		int wdiff = screenWidth / 5;
		int hdiff = screenHeight / 5;
		int x = 0;
		int y = 0;
		int i,j;
		for (i=0; i < 5; i++) {
				myViewport (x, y, wdiff, hdiff);
				drawPolys();
				y+= hdiff;
				x+= wdiff;
		}
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
	glutKeyboardFunc ( key );
	glutDisplayFunc( display );
	
	glutMainLoop();
	
	return 0;
	
}
