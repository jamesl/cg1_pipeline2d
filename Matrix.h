// C++ Matrices (or at least enough for CG1)

#include <iostream>

using namespace std;

class Matrix {
  public:
	Matrix();
	Matrix(int rows,int cols);
	double& operator() (int row, int col);
	double	operator() (int row, int col) const;	

	~Matrix();
	Matrix(const Matrix& m);
	Matrix& operator= (const Matrix& m);
	Matrix  operator* (const Matrix& m);

	int getRows() const { return _rows; }
	int getCols() const { return _cols; }

  private:
	double *_data;
	int _rows,_cols;
};

ostream& operator<<(ostream& os, const Matrix &m);


