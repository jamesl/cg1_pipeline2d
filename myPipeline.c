// Store state information for the pipeline

#include "Matrix.h"
#include <iostream>
#include <cassert>
#include "myFunctions.h"
#include <stack>

using namespace std;

Matrix modelview;
Matrix projection;
Matrix *currentmatrix;

stack<Matrix> matrixstack;

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
