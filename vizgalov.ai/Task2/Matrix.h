#pragma once
#include <iostream>

using namespace std;

class Matrix {
public:
	// Default initialization constructor (size=0, no memory allocation)
	Matrix();

	// Initialization of null matrix of specified size
	Matrix(int _size);

	// Initialization of matrix from two-dimansional array
	Matrix(int _size, int ** _mat);

	// Copy constructor
	Matrix(const Matrix& _m);

	// Assignment operator overload
	Matrix& operator=(const Matrix& _m);

	// Destructor
	~Matrix();

	// Set matrix size and allocate enough memory
	void setSize(int _size);

	// Get size of matrix
	int getSize() { return size; };

	// Subclass which is used for [][] indexing operation overload
	class IndexingProxy {
	public:
		// Counstructor
		IndexingProxy(int * _subMatrix) : subMatrix(_subMatrix) {}
		// [] indexing operation overload
		int& operator[](int _i) { return subMatrix[_i]; }
	private:
		int * subMatrix;	// One row of the matrix
	};
	// [][] indexing operation overload for matrix
	IndexingProxy operator[](int _i) { return IndexingProxy(mat[_i]); }

	// Subclass which is used for [][] indexing operation overload (for CONST matrix)
	class Const_IndexingProxy {
	public:
		// Counstructor
		Const_IndexingProxy(int * _subMatrix) : subMatrix(_subMatrix) {}
		// [] indexing operation overload
		int operator[](int _i) { return subMatrix[_i]; }
	private:
		int * subMatrix;	// One row of the matrix
	};
	// [][] indexing operation overload for CONST matrix
	Const_IndexingProxy operator[](int _i) const { return Const_IndexingProxy(mat[_i]); }

	// Check if matrix has diagonal dominance
	bool checkDiagonalDominance();

	// Addition and subtraction operators overload
	Matrix operator+(const Matrix& _m);
	Matrix operator-(const Matrix& _m);
	Matrix& operator+=(const Matrix& _m);
	Matrix& operator-=(const Matrix& _m);

	// Stream output operator overload
	friend ostream& operator<<(ostream& stream, const Matrix& _m);

	// Stream input operator overload
	friend istream& operator>>(istream& stream, Matrix& _m);

	// Unit testing method
	friend void testMatrix();

private:
	// Internal method used for memory allocation
	void allocMatrix();

	// Internal method used for memory deallocation 
	void deallocMatrix();

	int size;	// Matrix size
	int ** mat; // Matrix pointer
};