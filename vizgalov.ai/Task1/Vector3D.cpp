#include "Vector3D.h"

// Default initialization constructor
Vector3D::Vector3D() {
	x = y = z = length = 0.0;
}

// Initialization from three real numbers
Vector3D::Vector3D(double _x, double _y, double _z) {
	x = _x;
	y = _y;
	z = _z;
	length = calculateLength();
}

// Copy constructor
Vector3D::Vector3D(const Vector3D& _v) {
	x = _v.x;
	y = _v.y;
	z = _v.z;
	length = _v.length;
}

// Destructor
Vector3D::~Vector3D() {
	x = y = z = length = 0.0;
}

// Get methods for all three coordinates and length value
double Vector3D::getX() { return x; };
double Vector3D::getY() { return y; };
double Vector3D::getZ() { return z; };
double Vector3D::getLength() { return length; };

// Set methods for all three coordinates
void Vector3D::setX(double _x) {
	x = _x;
	length = calculateLength();
}
void Vector3D::setY(double _y) {
	y = _y;
	length = calculateLength();
}
void Vector3D::setZ(double _z) {
	z = _z;
	length = calculateLength();
}

// Calculates vector's length
double Vector3D::calculateLength() {
	return sqrt(x*x + y*y + z*z);
}

// Assignment operator overload
Vector3D& Vector3D::operator=(const Vector3D& _v) {
	x = _v.x;
	y = _v.y;
	z = _v.z;
	length = calculateLength();
	return *this;
}

// Addition operator overload
Vector3D Vector3D::operator+(const Vector3D& _v) {
	Vector3D res;
	res.x = x + _v.x;
	res.y = y + _v.y;
	res.z = z + _v.z;
	res.length = res.calculateLength();
	return res;
}

// Subtraction operator overload
Vector3D Vector3D::operator-(const Vector3D& _v) {
	Vector3D res;
	res.x = x - _v.x;
	res.y = y - _v.y;
	res.z = z - _v.z;
	res.length = res.calculateLength();
	return res;
}

// Multiplication operator overload
// (vector multiplied by vector)
double Vector3D::operator*(const Vector3D& _v) {
	return x*_v.x + y*_v.y + z*_v.z;
}

// Multiplication operator overload
// (vector multiplied by scalar)
double Vector3D::operator*(double scalar) {
	return x*scalar + y*scalar + z*scalar;
}

// Comparison operators overload
bool Vector3D::operator==(const Vector3D& _v) {
	return length == _v.length;
}
bool Vector3D::operator!=(const Vector3D& _v) {
	return !(*this == _v);
}
bool Vector3D::operator>(const Vector3D& _v) {
	return length > _v.length;
}
bool Vector3D::operator<(const Vector3D& _v) {
	return length < _v.length;
}
bool Vector3D::operator>=(const Vector3D& _v) {
	return !(length < _v.length);
}
bool Vector3D::operator<=(const Vector3D& _v) {
	return !(*this > _v);
}

// Stream output operator overload
ostream& operator<<(ostream& stream, const Vector3D& _v) {
	// Output format: { x ; y ; z }
	stream << "{ " << _v.x << " ; " << _v.y << " ; " << _v.z << " }";
	return stream;
}

// Stream input operator overload
istream& operator>>(istream& stream, Vector3D& _v) {
	// Input format: { x ; y ; z }
	char separator;	// "separator" variable is used here to remove '{', '}' and ';' symbols from input
	cin >> separator;
	stream >> _v.x;
	cin >> separator;
	stream >> _v.y;
	cin >> separator;
	stream >> _v.z;
	cin >> separator;
	return stream;
}