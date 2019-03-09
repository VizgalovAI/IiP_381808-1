#pragma once
#include "Matrix.h"

// Default initialization constructor (size=0, no memory allocation)
Matrix::Matrix() {
	size = 0;
	mat = NULL;
}

// Initialization of null matrix of specified size
Matrix::Matrix(int _size) {
	setSize(_size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mat[i][j] = 0;
		}
	}
}

// Initialization of matrix from two-dimansional array
Matrix::Matrix(int _size, int ** _mat) {
	setSize(_size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mat[i][j] = _mat[i][j];
		}
	}
}

// Copy constructor
Matrix::Matrix(const Matrix& _m) {
	size = _m.size;
	allocMatrix();
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mat[i][j] = _m[i][j];
		}
	}
}

// Assignment operator overload
Matrix& Matrix::operator=(const Matrix& _m) {
	setSize(_m.size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mat[i][j] = _m[i][j];
		}
	}
	return *this;
}

// Destructor
Matrix::~Matrix() {
	deallocMatrix();
	size = 0;
	mat = NULL;
}

// Set matrix size and allocate enough memory
void Matrix::setSize(int _size) {
	if (_size < 2) {
		throw "Matrix size is too small (must be >=2)";
	}
	if (_size > 8) {
		throw "Matrix size is too big (must be <=8)";
	}
	deallocMatrix();
	size = _size;
	allocMatrix();
}

// Check if matrix has diagonal dominance
bool Matrix::checkDiagonalDominance() {
	int sum;
	for (int i = 0; i < size; i++) {
		sum = 0;
		for (int j = 0; j < size; j++) {
			if (i != j) {
				sum += mat[i][j];
			}
		}
		if (mat[i][i] < sum) return false;
	}
	return true;
}

// Addition and subtraction operators overload
Matrix Matrix::operator+(const Matrix& _m) {
	if (size != _m.size) {
		throw "Only matrices of equal size can be summarized";
	}
	Matrix newMat;
	newMat.setSize(size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			newMat[i][j] = mat[i][j] + _m[i][j];
		}
	}
	return newMat;
}
Matrix Matrix::operator-(const Matrix& _m) {
	if (size != _m.size) {
		throw "Only matrices of equal size can be subtracted";
	}
	Matrix newMat;
	newMat.setSize(_m.size);
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			newMat[i][j] = mat[i][j] - _m[i][j];
		}
	}
	return newMat;
}
Matrix& Matrix::operator+=(const Matrix& _m)
{
	if (size != _m.size) {
		throw "Only matrices of equal size can be summarized";
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mat[i][j] += _m[i][j];
		}
	}
	return *this;
}
Matrix& Matrix::operator-=(const Matrix& _m)
{
	if (size != _m.size) {
		throw "Only matrices of equal size can be subtracted";
	}
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size; j++) {
			mat[i][j] -= _m[i][j];
		}
	}
	return *this;
}

// Stream output operator overload
ostream& operator<<(ostream& stream, const Matrix& _m) {
	// Output format: 1 2 3
	//				  4 5 6
	//				  7 8 9
	for (int i = 0; i < _m.size; i++) {
		for (int j = 0; j < _m.size; j++) {
			stream << _m[i][j] << " ";
		}
		stream << endl;
	}
	return stream;
}

// Stream input operator overload
istream& operator>>(istream& stream, Matrix& _m) {
	// Input format:  1 2 3
	//				  4 5 6
	//				  7 8 9
	for (int i = 0; i < _m.size; i++) {
		for (int j = 0; j < _m.size; j++) {
			stream >> _m[i][j];
		}
	}
	return stream;
}

// Internal method used for memory allocation
void Matrix::allocMatrix() {
	mat = new int*[size];
	for (int i = 0; i < size; i++) {
		mat[i] = new int[size];
	}
}

// Internal method used for memory deallocation 
void Matrix::deallocMatrix() {
	for (int i = 0; i < size; i++) {
		delete mat[i];
	}
	delete mat;
}