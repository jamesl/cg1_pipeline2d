
#include "myVertex.h"

myVertex::myVertex(color c,float x,float y,float z) :
		Matrix(), _c(c) {
	operator()(0,0) = x;
	operator()(1,0) = y;
	operator()(2,0) = z;
	operator()(3,0) = 1.0;
}

double& myVertex::getX() { return operator()(0,0); }
double  myVertex::getX() const { return operator()(0,0); }
double& myVertex::getY() { return operator()(1,0); }
double  myVertex::getY() const { return operator()(1,0); }
double& myVertex::getZ() { return operator()(2,0); }
double  myVertex::getZ() const { return operator()(2,0); }
	
