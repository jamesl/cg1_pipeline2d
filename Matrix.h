// C++ Matrices (or at least enough for CG1)

#include <iostream>
#include <vector>
#include "color.h"

using namespace std;

class Matrix {
  public:
	Matrix();
	Matrix(int rows,int cols);
	double& operator() (int row, int col);
	double	operator() (int row, int col) const;	

	virtual ~Matrix();
	Matrix(const Matrix& m);
	Matrix& operator= (const Matrix& m);
	Matrix  operator* (const Matrix& m);
	vector<Matrix> operator* (const vector<Matrix>& v);

	int getRows() const;
	int getCols() const;
	void clear();
	void setvertexinfo(color c);

  private:
	int _rows,_cols,_size;
	double *_data;

	bool isVertex;
	color _c;
};

ostream& operator<<(ostream& os, const Matrix &m);


