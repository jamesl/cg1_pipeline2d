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

#include <iostream>
#include <cassert>
#include <stack>
#include <vector>
#include <cmath>

#include "Matrix.h"
#include "color.h"
#include "myFunctions.h"
#include "setPixel.h"

void drawPolygon(vector<Matrix>);
vector<Matrix> clipper(vector<Matrix>);
extern int screenWidth;
extern int screenHeight;

using namespace std;

Matrix matrix_modelview;
Matrix matrix_projection;
Matrix matrix_viewport;
Matrix matrix_normalize;
Matrix *currentmatrix = &matrix_modelview;

stack<Matrix> matrixstack;
vector<Matrix> vertices;
GLenum vertexmode;

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
void myBegin(GLenum mode) {
	vertexmode = mode;
	vertices.clear();
}


/**
 * myEnd - delimit the vertices of a primitive or a group of like primitives.  
 * Closes a myBegin() statement.
 *
 * This routine will initiate the processing and drawing of a polygon.
 */
void myEnd()
{
	switch(vertexmode) {
	case GL_POLYGON:	
		// clip normalized vertices
		vertices = clipper(vertices);
		// transform into screen coords
		vertices = matrix_viewport * vertices;
		// draw polygon
		drawPolygon(vertices);
		break;
	}
	return;
}


/**
 * myVertex2f -- Specify a vertex
 *
 * x,y -- Specify x and y coordinates of a vertex.
 */
void myVertex2f(float x, float y)
{
	Matrix pt(4,1);
	pt(0,0) = x;
	pt(1,0) = y;
	pt(2,0) = 0.0;
	pt(3,0) = 1.0;
	// multiply each point by normalize
	// and modelview upon insertion into
	// list
	pt = 	matrix_normalize * 
		matrix_modelview * pt;
	vertices.push_back(pt);
	
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
	setcolor(red,green,blue);
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
	setclearcolor(red,green,blue);
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
	color c;
	switch(mask) {
	case GL_COLOR_BUFFER_BIT:
		c = getclearcolor();
		break;
	}
	for(int x=0;x<screenWidth;x++)
		for(int y=0;y<screenHeight;y++)
			setPixel(x,y,c.r,c.g,c.b);
}

/**
 * myMatrixMode
 * switch to a new matrix mode:
 * only projection and modelview are supported
 */
void myMatrixMode(GLenum mode) {
	switch(mode) {
	case GL_PROJECTION:
		currentmatrix = &matrix_projection;
		break;
	case GL_MODELVIEW:
		currentmatrix = &matrix_modelview;
		break;
	}
}

/**
 * myPushMatrix
 * push currentmatrix to top of matrix stack
 */
void myPushMatrix() {
	assert(currentmatrix != 0);
	matrixstack.push(*currentmatrix);
}

/**
 * myPopMatrix
 * change currentmatrix to matrix on top
 * of matrix stack
 */
void myPopMatrix() {
	assert(matrixstack.size());
	assert(currentmatrix != 0);
	*currentmatrix = matrixstack.top();
	matrixstack.pop();
}

/**
 * myLoadIdentityCurrent - load the 
 * identity matrix into whatever matrix
 * is currently set
 */
void myLoadIdentityCurrent() {
	assert(currentmatrix != 0);
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			(*currentmatrix)(i,j) = (i==j) ? 1.0 : 0;
}

/**
 * myLoadIdentity — replace the current matrix with the identity matrix.
 *
 * For this implementation, it is assumed that the current matrix is the
 * transformation (MODELVIEW) matrix.
 */
void myLoadIdentity( void)
{
	myMatrixMode (GL_MODELVIEW);
	myLoadIdentityCurrent();
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
void myTranslatef(float x, float y) {
	myMatrixMode(GL_MODELVIEW);
	Matrix translate;
	translate(0,0) = translate(1,1) = 1.0;
	translate(2,2) = translate(3,3) = 1.0;
	translate(0,3) = x;
	translate(1,3) = y;
	translate(2,3) = 1.0;
	(*currentmatrix) = (*currentmatrix) * translate;
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
void myRotatef(float degrees) {
	myMatrixMode (GL_MODELVIEW);
	Matrix rotate;
	// GL uses degrees, but math.h uses radians!
	double angle = degrees * 3.14159 / 180.0;
	rotate(2,2) = rotate(3,3) = 1.0;
	rotate(0,0) = rotate(1,1) = cos(angle);
	rotate(0,1) = -sin(angle);
	rotate(1,0) = sin(angle);
	(*currentmatrix) = (*currentmatrix) * rotate;
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
void myScalef(float x, float y) {
	myMatrixMode(GL_MODELVIEW);
	Matrix scale;
	scale(0,0) = x;
	scale(1,1) = y;
	scale(2,2) = scale(3,3) = 1.0;
	(*currentmatrix) = (*currentmatrix) * scale;
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
	// create matrix to normalize coords
	matrix_normalize(0,0) = 2.0/(right-left);
	matrix_normalize(1,1) = 2.0/(top-bottom);
	matrix_normalize(0,3) = -(right+left)/(right-left);
	matrix_normalize(1,3) = -(top+bottom)/(top-bottom);

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
	// create matrix to take normalized coords
	// to screen coords
	matrix_viewport(0,0) = (width)/2.0;
	matrix_viewport(1,1) = (height)/2.0;
	matrix_viewport(0,3) = ((x+width)+x)/2.0;
	matrix_viewport(1,3) = ((y+height)+y)/2.0;
}
