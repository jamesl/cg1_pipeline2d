/*
 *  myFunctions.h
 *  2DFramework
 *
 *  This file contains signatures of all of the 2D routines required for 
 *  the 2D Pipeline Implementation Option.
 *
 *  Created by Joe Geigel on 9/25/07.
 *
 */

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __APPLE__
#include <OPENGL/gl.h>
#include <OPENGL/glu.h>
#else
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2


/*
 * Defining polygons
 */
extern void myBegin(GLenum mode);
extern void myEnd();
extern void myVertex2f(float x, float y);
extern void myVertex3f(float x, float y, float z);
extern void myColor3f(	float red, float green, float blue);
extern void myClearColor(	float red, float green, float blue, float alpha);
extern void myClear(GLbitfield mask);
extern void myFlush(void);

/*
 * Transformation routines
 */
extern void myLoadIdentity( void);
extern void myTranslatef(float x, float y);
extern void myTranslatef(float x, float y, float z);
extern void myRotatef(	float angle);
extern void myRotatef(	float angle, int axis);
extern void myScalef(float x, float y);
extern void myScalef(float x, float y, float z);


/*
 * clipping 
 */
extern void myOrtho2D(	double left, double right, double bottom, double top);

/*
 * viewing
 */
extern void myFrustum(double left, double right, double bottom, double top, double near, double far);
extern void myOrtho(double left, double right, double bottom, double top, double near, double far);
extern void myLookAt( double eyeX, double eyeY, double eyeZ, double centerX, double centerY, double centerZ,double upX, double upY,double upZ );


/*
 * Projection / viewport
 */
extern void myViewport(int x, int y, int width, int height);


void myMatrixMode(GLenum mode);

// push matrix onto stack
void myPushMatrix();

// pop matrix off of stack
void myPopMatrix();

void myLoadIdentityCurrent();
	
