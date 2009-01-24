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

#include <OPENGL/gl.h>

/*
 * Defining polygons
 */
extern void myBegin(GLenum mode);
extern void myEnd();
extern void myVertex2f(float x, float y);
extern void myColor3f(	float red, float green, float blue);
extern void myClearColor(	float red, float green, float blue, float alpha);
extern void myClear(GLbitfield mask);

/*
 * Transformation routines
 */
extern void myLoadIdentity( void);
extern void myTranslatef(float x, float y);
extern void myRotatef(	float angle);
extern void myScalef(float x, float y);


/*
 * clipping 
 */
extern void myOrtho2D(	double left, double right, double bottom, double top);

/*
 * Projection / viewport
 */
extern void myViewport(int x, int y, int width, int height);







