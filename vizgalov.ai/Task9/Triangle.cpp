#include <iostream>
#include <cmath>
#include <algorithm>

#include "Triangle.h"

using namespace std;

Triangle::Triangle() {
	a = b = c = 0.0;
}

Triangle::Triangle(double _a, double _b, double _c) {
	a = _a;
	b = _b;
	c = _c;
}

Triangle::Triangle(const Triangle& _T) {
	a = _T.a;
	b = _T.b;
	c = _T.c;
}

Triangle::~Triangle() {
	a = b = c = 0.0;
}

double Triangle::getPerimeter() {
	return a + b + c;
}

double Triangle::getArea() {
	double p = getPerimeter() / 2;
	return sqrt(p*(p - a)*(p - b)*(p - c));
}

bool Triangle::exists() {
	return ((a + b >= c) && (a + c >= b) && (b + c >= a));
}

// Triangle types:
//  0 - doesn't exist
//  1 - right
//  2 - acute
//  3 - obtuse
int Triangle::getType() {
	double _a, _b, _c;
	_a = a;
	_b = b;
	_c = c;
	if (_a > _c) {
		swap(_a, _c);
	}
	if (_b > _c) {
		swap(_b, _c);
	}

	if (!exists()) { return 0; }
	if (_c*_c == _a * _a + _b * _b) {
		return 1;
	}
	else if (_c*_c < _a*_a + _b * _b) {
		return 2;
	}
	else {
		return 3;
	}
}