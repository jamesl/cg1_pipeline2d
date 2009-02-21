
#include "Matrix.h"
#include "color.h"

class myVertex : public Matrix {
  public:
	myVertex(color c,float x,float y,float z); 
	~myVertex();

	double& getX();
	double  getX() const;
	double& getY();
	double  getY() const;
	double& getZ();
	double  getZ() const;
	
  private:
	color _c;	
};
