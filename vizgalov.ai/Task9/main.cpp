#include <iostream>
#include <cmath>
#include <algorithm>

#include "Triangle.h"

using namespace std;

int main() {
	Triangle tri = Triangle(30, 16, 16);
	cout << "Exists: " << (tri.exists() ? "Yes" : "No") << endl;
	if (tri.exists()) {
		cout << "Perimeter: " << tri.getPerimeter() << endl;
		cout << "Area: " << tri.getArea() << endl;
		switch (tri.getType())
		{
		case 0:
			cout << "Doesn't exist!" << endl;
			break;
		case 1:
			cout << "Type: Right" << endl;
			break;
		case 2:
			cout << "Type: Acute" << endl;
			break;
		case 3:
			cout << "Type: Obtuse" << endl;
			break;
		}
	}


	return 0;
}