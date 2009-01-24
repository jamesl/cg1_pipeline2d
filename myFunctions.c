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

using namespace std;

Matrix modelview;
Matrix projection;
Matrix *currentmatrix;

stack<Matrix> matrixstack;
vector<Matrix> vertices;
GLenum vertexmode;

struct window{
	//Matrix a(4,1),b(4,1);
	double x1,y1,x2,y2;
} clip,viewport;


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
	cout << vertices.size() << endl;
}


/**
 * myEnd - delimit the vertices of a primitive or a group of like primitives.  
 * Closes a myBegin() statement.
 *
 * This routine will initiate the processing and drawing of a polygon.
 */
void myEnd()
{
	// draw
	// draw based on mode now
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
	if(vertices.size()>=4) return;
	vertices.push_back(pt);
	cout << vertices.size() << endl;
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
	glClearColor (red, green, blue, alpha);
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
	glClear (mask);
}

void myMatrixMode(int mode) {
	switch(mode) {
	case GL_PROJECTION:
		currentmatrix = &projection;
		break;
	case GL_MODELVIEW:
		currentmatrix = &modelview;
		break;
	}
}

void myPushMatrix() {
	assert(currentmatrix != 0);
	matrixstack.push(*currentmatrix);
}

void myPopMatrix() {
	assert(matrixstack.size());
	assert(currentmatrix != 0);
	*currentmatrix = matrixstack.top();
	matrixstack.pop();
}

void myLoadIdentityCurrent() {
	assert(currentmatrix != 0);
	for(int c=0;c<4;c++)
		(*currentmatrix)(c,c) = 1.0;
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
void myTranslatefx(float x, float y) {
	Matrix translate;
	translate(0,0) = translate(1,1) = 1.0;
	translate(2,2) = translate(3,3) = 1.0;
	translate(0,3) = x;
	translate(1,3) = y;
	translate(2,3) = 1.0;
	(*currentmatrix) = (*currentmatrix) * translate;
}
void myTranslatef(float x, float y) {
	myMatrixMode(GL_MODELVIEW);
	myTranslatefx(x,y);
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
void myRotatefx(float angle) {
	Matrix rotate;
	rotate(2,2) = rotate(3,3) = 1.0;
	rotate(0,0) = rotate(1,1) = cos(angle);
	rotate(0,1) = -sin(angle);
	rotate(1,0) = sin(angle);
	(*currentmatrix) = (*currentmatrix) * rotate;
}
void myRotatef(float angle) {
	myMatrixMode (GL_MODELVIEW);
	myRotatefx(angle);
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
void myScalefx(float x, float y) {
	Matrix scale;
	scale(0,0) = x;
	scale(1,1) = y;
	scale(2,2) = scale(3,3) = 1.0;
	(*currentmatrix) = (*currentmatrix) * scale;
}
void myScalef(float x, float y) {
	myMatrixMode(GL_MODELVIEW);
	myScalefx(x,y);
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
	myMatrixMode( GL_PROJECTION );
    	myLoadIdentityCurrent();
	//gluOrtho2D (left, right, bottom, top);
	clip.x1 = left;
	clip.y1 = bottom;
	clip.x2 = right;
	clip.y2 = top;
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
	//glViewport (x, y, width, height);
	viewport.x1 = x;
	viewport.x2 = x + width;
	viewport.y1 = y;	
	viewport.y2 = y + height;

	myTranslatef(clip.x1,clip.y1);
	myScalef((clip.x2-clip.x1)/(viewport.x2-viewport.x1),
		  (clip.y2-clip.y1)/(viewport.x2-viewport.x1));
	myTranslatef(-viewport.x1,-viewport.y1);
}
