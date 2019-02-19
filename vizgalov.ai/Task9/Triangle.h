#pragma once

class Triangle {
public:
	Triangle();
	Triangle(double _a, double _b, double _c);
	Triangle(const Triangle& _T);
	~Triangle();

	double getPerimeter();
	double getArea();
	bool exists();
	int getType();

private:
	double a, b, c;
};