// C++ Matrices (or at least enough for CG1)

#include <iostream>
#include <vector>

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
	vector<Matrix> operator* (const vector<Matrix>& v);

	int getRows() const { return _rows; }
	int getCols() const { return _cols; }

  private:
	int _rows,_cols,_size;
	double *_data;
};

ostream& operator<<(ostream& os, const Matrix &m);


