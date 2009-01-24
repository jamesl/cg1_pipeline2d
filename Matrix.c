// C++ Matrices (or at least enough for CG1)

#include "Matrix.h"
#ifndef NODEBUG
#include <cassert>
#else
#define assert(x) 
#endif
#include <iostream>

using namespace std;

Matrix::Matrix() : _rows(4), _cols(4) {
	_data = new double[4*4];
}

Matrix::Matrix(int rows,int cols) :
		_rows(rows), _cols(cols) {
	_data = new double[_rows*_cols];
}

double& Matrix::operator() (int row, int col) {
	int loc = _cols*row+col;
	assert(loc<_cols*_rows);
	return _data[loc];
}

ostream& operator<<(ostream& os, const Matrix &m) {
	for(int i=0;i<m.getRows();i++) {	
		os << " [ ";
		for(int j=0;j<m.getCols();j++) {
			os << m(i,j) << " ";
		}
		os << "]" << endl;
	}
	return os;
}
			
double	Matrix::operator() (int row, int col) const {
	int loc = _cols*row+col;
	assert(loc<_cols*_rows);
	return _data[loc];
}

Matrix::~Matrix() {
	delete [] _data;
}

Matrix::Matrix(const Matrix& m) {
	int size = m.getRows() * m.getCols();
	_data = new double[size];
	for(int i=0;i<size;i++) {
		_data[i] = m._data[i];
	}
}

Matrix& Matrix::operator= (const Matrix& m) {
	delete [] _data;
	int size = m.getRows() * m.getCols();
	_data = new double[size];
	for(int i=0;i<size;i++) {
		_data[i] = m._data[i];
	}
	return *this;
}

Matrix  Matrix::operator* (const Matrix& m) {
	assert(_cols == m.getRows());
	Matrix result(_rows,m._cols);
	for(int i=0;i<_rows;i++) {
		for(int j=0;j<m._cols;j++) {
			double sum=0;
			for(int k=0;k<_cols;k++) {
				sum+= (*this)(i,k) * m(k,j);
			}
			result(i,j) = sum;	
		}
	}
	return result;
}


