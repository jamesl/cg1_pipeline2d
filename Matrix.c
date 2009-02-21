// C++ Matrices (or at least enough for CG1)
// also used for vertices (with additional info)
// which is bad design, but was done due to lack
// of time

#include "Matrix.h"
#ifndef NODEBUG
#include <cassert>
#else
#define assert(x) 
#endif
#include <iostream>

using namespace std;

/**
 * default constructor
 * make a 4x4 matrix
 */
Matrix::Matrix() : _rows(4), _cols(4), _size(16), isVertex(false) {
	_data = new double[16];
	assert(_size<=16);
	clear();
	for(int i=0;i<4;i++)
		for(int j=0;j<4;j++)
			(*this)(i,j) = (i==j) ? 1.0 : 0;
}

/**
 * construct a matrix given
 * rows and columns
 */
Matrix::Matrix(int rows,int cols) :
		_rows(rows), _cols(cols), _size(rows*cols), isVertex(false) {
	assert(_size<=16);
	assert(_cols > 0 && _cols <= 4);
	assert(_rows > 0 && _rows <= 4);
	_data = new double[_size];
	clear();
}

/**
 * operator() -
 * This is used to more easily access elements in the
 * matrix. You can't do [a,b] but you can do (a,b)!
 */
double& Matrix::operator() (int row, int col) {
	assert(_size<=16);
	assert(_cols > 0 && _cols <= 4);
	assert(_rows > 0 && _rows <= 4);
	int loc = _cols*row+col;
	assert(loc<_size);
	return _data[loc];
}

/**
 * clears a matrix
 * (sets all values to 0)
 */
void Matrix::clear() { for(int i=0;i<_size;i++) _data[i]=0.0; }

/**
 * row/column accessors
 */
int Matrix::getRows() const { return _rows; }
int Matrix::getCols() const { return _cols; }

/**
 * operator<<
 * used for printing a matrix
 * I used this _very_ extensively when writing the
 * pipeline!
 */
ostream& operator<<(ostream& os, const Matrix &m) {
	assert(&m!=0);
	for(int i=0;i<m.getRows();i++) {	
		os << " [ ";
		for(int j=0;j<m.getCols();j++) {
			os << m(i,j) << " ";
		}
		os << "]" << endl;
	}
	return os;
}
			
/**
 * same as above operator() but for
 * a const Matrix
 */
double	Matrix::operator() (int row, int col) const {
	assert(_size<=16);
	assert(_cols > 0 && _cols <= 4);
	assert(_rows > 0 && _rows <= 4);
	int loc = _cols*row+col;
	assert(loc<_size);
	return _data[loc];
}

/**
 * destructor
 */
Matrix::~Matrix() {
	delete [] _data;
	_rows=_cols=_size=0;
	_data=0;
}

/**
 * copy constructor
 */
Matrix::Matrix(const Matrix& m) {
	assert((&m)!=0);
	_rows = m._rows;
	_cols = m._cols;
	_size = m._size;
	isVertex = m.isVertex;
	_c = m._c;
	assert(_size<=16);
	assert(_cols > 0 && _cols <= 4);
	assert(_rows > 0 && _rows <= 4);
	_data = new double[_size];
	for(int i=0;i<m._size;i++) {
		double d = m._data[i]; 
		_data[i] = d;
	}
	assert(_size<=16);
}

/**
 * assignment operator
 */
Matrix& Matrix::operator= (const Matrix& m) {
	delete [] _data;
	_rows = m._rows;
	_cols = m._cols;
	_size = m._size;
	assert(_size<=16);
	assert(_cols > 0 && _cols <= 4);
	assert(_rows > 0 && _rows <= 4);
	_data = new double[_size];
	for(int i=0;i<_size;i++) {
		_data[i] = m._data[i];
	}
	assert(_size<=16);
	return *this;
}

/**
 * operator*
 * this allows me to multiply a Matrix * vector<Matrix>
 * I use this for multiplying a matrix by all of the 
 * vertices of a primitive.
 */
vector<Matrix>  Matrix::operator* (const vector<Matrix>& v) {
	vector<Matrix>::const_iterator iter;	
	vector<Matrix> w;
	for(int i=0;i<v.size();i++) {
		w.push_back((*this) * v.at(i));
	}
	return w;
}

/**
 * operator*
 * used for multiplying 2 matrices.
 * works with 2 4x4 or of any size, as long as
 * columns of the first == rows of the 2nd.
 * vertices are also represented as 4x1 matrices.
 */
Matrix  Matrix::operator* (const Matrix& m) {
	assert(_cols == m.getRows());
	Matrix result(_rows,m._cols);
	result.isVertex = m.isVertex;
	result._c = m._c;
	for(int i=0;i<_rows;i++) {
		for(int j=0;j<m._cols;j++) {
			double sum=0;
			for(int k=0;k<_cols;k++) {
				sum+= (*this)(i,k) * m(k,j);
			}
			result(i,j) = sum;	
		}
	}
	assert(result._size <= 16);
	return result;
}

void Matrix::setvertexinfo(color c) {
	_c = c;
	isVertex = true;
}

color Matrix::getcolor() {
	assert(isVertex);
	return _c;
}

