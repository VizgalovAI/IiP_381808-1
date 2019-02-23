#pragma once
#include <iostream>
#include <stdio.h>

using namespace std;

class Vector3D {
public:
	// Default initialization constructor
	Vector3D();

	// Initialization from three real numbers
	Vector3D(double _x, double _y, double _z);

	// Copy constructor
	Vector3D(const Vector3D& _v);

	// Destructor
	~Vector3D();

	// Get methods for all three coordinates and length value
	double getX();
	double getY();
	double getZ();
	double getLength();

	// Set methods for all three coordinates
	void setX(double _x);
	void setY(double _y);
	void setZ(double _z);

	// Calculates vector's length
	double calculateLength();

	// Assignment operator overload
	Vector3D& operator=(const Vector3D& _v);

	// Addition operator overload
	Vector3D operator+(const Vector3D& _v);

	// Subtraction operator overload
	Vector3D operator-(const Vector3D& _v);

	// Multiplication operator overload
	// (vector multiplied by vector)
	double operator*(const Vector3D& _v);

	// Multiplication operator overload
	// (vector multiplied by scalar)
	double operator*(double scalar);

	// Comparison operators overload
	bool operator==(const Vector3D& _v);
	bool operator!=(const Vector3D& _v);
	bool operator>(const Vector3D& _v);
	bool operator<(const Vector3D& _v);
	bool operator>=(const Vector3D& _v);
	bool operator<=(const Vector3D& _v);

	// Stream output operator overload
	friend ostream& operator<<(ostream& stream, const Vector3D& _v);

	// Stream input operator overload
	friend istream& operator>>(istream& stream, Vector3D& _v);

private:
	// Vector's coordinates and length
	double x, y, z, length;
};