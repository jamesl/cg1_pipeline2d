/*
 *  myFunctions.c
 *  2DFramework
 *
 *  This file contains implementations of all of the 2D routines required for 
 *  the 2D Pipeline Implementation Option.
 *
 *  The functions are stubbed with OpenGL implementations of the routines you 
 *  are to write
 *
 *  Created by Joe Geigel on 9/25/07.
 *
 */

#include "myFunctions.h"

/**
 *  myBegin - delimit the vertices of a primitive or a group of like primitives.
 *
 *  mode -- Specifies the primitive or primitives that will be created from vertices
 *  presented between glBegin and the subsequent glEnd.
 *
 *  Ten symbolic constants are accepted:
 *		GL_POINTS,
 *		GL_LINES,
 *		GL_LINE_STRIP,
 *		GL_LINE_LOOP,
 *		GL_TRIANGLES,
 *		GL_TRIANGLE_STRIP,
 *		GL_TRIANGLE_FAN,
 *		GL_QUADS,
 *		GL_QUAD_STRIP, and
 *		GL_POLYGON.
 *
 *  For your implementation, only GL_POLYGON need be considered
 */
void myBegin(GLenum mode)
{
	glBegin(mode);
}


/**
 * myEnd - delimit the vertices of a primitive or a group of like primitives.  
 * Closes a myBegin() statement.
 *
 * This routine will initiate the processing and drawing of a polygon.
 */
void myEnd()
{
	glEnd();
}


/**
 * myVertex2f -- Specify a vertex
 *
 * x,y -- Specify x and y coordinates of a vertex.
 */
void myVertex2f(float x, float y)
{
	glVertex2f (x, y);
}


/**
 *  myColor — set the current color
 *
 *  red, green, blue - Specify new red, green, and blue values for the current color.
 *  Color values should be between 0 and 1.
 */
void myColor3f(	float  	red, 
				float  	green, 
				float  	blue)
{
	glColor3f( red, green, blue);
}


/**
 * myClearColor — specify clear values for the color buffers
 * 
 * red, green, blue, alpha - Specify the red, green, blue, and alpha values used 
 * when the color buffers are cleared.
 *
 * The initial values are all 0.  Values should range between 0-1
 */
void myClearColor(	float  	red, 
					float  	green, 
					float  	blue, 
					float  	alpha)
{
	glClearColor (red, green, blue, alpha);
}


/**
 * myClear — clear buffers to preset values
 *
 * mask - Bitwise OR of masks that indicate the buffers to be cleared.
 *	The four masks are
 *		GL_COLOR_BUFFER_BIT,
 *		GL_DEPTH_BUFFER_BIT,
 *		GL_ACCUM_BUFFER_BIT, and
 *		GL_STENCIL_BUFFER_BIT.
 *
 * For this implementation, only GL_COLOR_BUFFER_BIT need be considered.
 */
void myClear(GLbitfield mask)
{
	glClear (mask);
}

/**
 * myLoadIdentity — replace the current matrix with the identity matrix.
 *
 * For this implementation, it is assumed that the current matrix is the
 * transformation (MODELVIEW) matrix.
 */
void myLoadIdentity( void)
{
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity ();
}


/**
 * myTranslatef — multiply the current matrix by a translation matrix.
 *
 * x, y - Specify the x, y, and z coordinates of a translation vector.
 * No translation in the z direction for now.
 * 
 * For this implementation, it is assumed that the current matrix is the 
 * transformation (MODELVIEW) matrix.
 */
void myTranslatef(float x, float y)
{
	glMatrixMode (GL_MODELVIEW);
	glTranslatef (x, y, 0.0);
}



/**
 * myRotatef — multiply the current matrix by a rotation matrix.  Rotation is 
 * assumed to be about the z-axis, thus rotation is performed in the x-y plane
 *
 * angle - Specifies the angle of rotation, in degrees.
 *
 * For this implementation, it is assumed that the current matrix is the 
 * transformation (MODELVIEW) matrix.
 */
void myRotatef(	float angle)
{
	glMatrixMode (GL_MODELVIEW);
	glRotatef (angle, 0.0, 0.0, 1.0);
}


/**
 * myScale — multiply the current matrix by a general scaling matrix
 * 
 * x, y  - Specify scale factors along the x, y, and z axes, respectively.
 * No scaling in the z-direction for now.
 *
 * For this implementation, it is assumed that the current matrix is the 
 * transformation (MODELVIEW) matrix.
 *
 */
void myScalef(float x, float y)
{
	glMatrixMode (GL_MODELVIEW);
	glScalef (x, y, 1.0);
}

/**
 * myOrtho2D — define a 2D orthographic projection matrix
 *
 * left, right - Specify the coordinates for the left and right vertical clipping 
 * planes.
 * 
 * bottom, top - Specify the coordinates for the bottom and top horizontal clipping planes.
 *
 */
void myOrtho2D(	double left, double right, double bottom, double top)
{
	glMatrixMode( GL_PROJECTION );
    glLoadIdentity( );
	gluOrtho2D (left, right, bottom, top);
}


/**
 *  myViewport — set the viewport
 *
 * x, y -- Specify the lower left corner of the viewport rectangle,
 *		in pixels. The initial value is (0,0).
 * width, height -- Specify the width and heigh of the viewport.
 */
void myViewport(int x, int y, int width, int height)
{
	glViewport (x, y, width, height);
}
