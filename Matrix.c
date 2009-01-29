// C++ Matrices (or at least enough for CG1)

#include "Matrix.h"
#ifndef NODEBUG
#include <cassert>
#else
#define assert(x) 
#endif
#include <iostream>

using namespace std;

Matrix::Matrix() : _rows(4), _cols(4), _size(16) {
	_data = new double[16];
	assert(_size<=16);
	clear();
}

Matrix::Matrix(int rows,int cols) :
		_rows(rows), _cols(cols), _size(rows*cols) {
	assert(_size<=16);
	_data = new double[_size];
	clear();
}

double& Matrix::operator() (int row, int col) {
	int loc = _cols*row+col;
	assert(loc<_size);
	return _data[loc];
	assert(_size<=16);
}

void Matrix::clear() { for(int i=0;i<_size;i++) _data[i]=0.0; }

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
	assert(loc<_size);
	return _data[loc];
	assert(_size<=16);
}

Matrix::~Matrix() {
	delete [] _data;
}

Matrix::Matrix(const Matrix& m) {
	assert((&m)!=0);
	_rows = m._rows;
	_cols = m._cols;
	_size = m._size;
	_data = new double[_size];
	for(int i=0;i<_size;i++) {
		_data[i] = m._data[i];
	}
	assert(_size<=16);
}

Matrix& Matrix::operator= (const Matrix& m) {
	delete [] _data;
	_rows = m._rows;
	_cols = m._cols;
	_size = m._size;
	_data = new double[_size];
	for(int i=0;i<_size;i++) {
		_data[i] = m._data[i];
	}
	assert(_size<=16);
	return *this;
}

vector<Matrix>  Matrix::operator* (const vector<Matrix>& v) {
	vector<Matrix>::const_iterator iter;	
	vector<Matrix> w;
	cout << v.size() << endl;
	for(int i=0;i<v.size();i++) {
		cout << v.at(i);
		w.push_back((*this) * v.at(i));
		cout << w.at(i) << endl;
	}
	return w;
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
	assert(result._size <= 16);
	return result;
}


