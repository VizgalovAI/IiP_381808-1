#include "Vector3D.h"
#include <windows.h>

// This variable is used for changing console's text color
HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

// Template function for testing two values for equality
// and then printing the result to console
template<typename T1, typename T2>
void test(T1 exp, T2 got) {
	cout << "Expected: " << exp;
	cout << " Got: " << got;
	cout << " Result: ";
	if (exp == got) {
		SetConsoleTextAttribute(hConsole, 10); // Green text color
		cout << "OK";
	}
	else {
		SetConsoleTextAttribute(hConsole, 12); // Red text color
		cout << "Failed";
	}
	SetConsoleTextAttribute(hConsole, 7); // Default (gray) text color
	cout << endl;
}

int main() {
	cout << "TEST: Default initialization constructor" << endl;
	Vector3D vec;
	test(0, vec.getX());
	test(0, vec.getY());
	test(0, vec.getZ());
	cout << endl;

	cout << "TEST: Initialization from three real numbers" << endl;
	Vector3D vec1 = Vector3D(1.1, 2.2, 3.3);
	test(1.1, vec1.getX());
	test(2.2, vec1.getY());
	test(3.3, vec1.getZ());
	cout << endl;

	cout << "TEST: Copy constructor" << endl;
	vec = vec1;
	test(1.1, vec.getX());
	test(2.2, vec.getY());
	test(3.3, vec.getZ());
	cout << endl;

	cout << "TEST: Calculate length" << endl;
	Vector3D vec2 = Vector3D(1, 2, 3);
	test(sqrt(14), vec2.calculateLength());
	cout << endl;

	cout << "TEST: Assignment operator" << endl;
	Vector3D vec3;
	Vector3D vec4 = Vector3D(1, 2, 3);
	vec3 = vec4;
	test(1, vec3.getX());
	test(2, vec3.getY());
	test(3, vec3.getZ());
	test(sqrt(14), vec3.getLength());
	cout << endl;

	cout << "TEST: Addition operator" << endl;
	Vector3D vec5 = Vector3D(1, 2, 3);
	Vector3D vec6 = Vector3D(1, 2, 3);
	Vector3D vec7;
	vec7 = vec5 + vec6;
	test(2, vec7.getX());
	test(4, vec7.getY());
	test(6, vec7.getZ());
	test(sqrt(56), vec7.getLength());
	cout << endl;

	cout << "TEST: Subtraction operator" << endl;
	Vector3D vec8 = Vector3D(1, 2, 3);
	Vector3D vec9 = Vector3D(1, 2, 3);
	Vector3D vec10;
	vec10 = vec8 - vec9;
	test(0, vec10.getX());
	test(0, vec10.getY());
	test(0, vec10.getZ());
	test(sqrt(0), vec10.getLength());
	cout << endl;

	cout << "TEST: Multiplication vector by vector" << endl;
	Vector3D vec11 = Vector3D(1, 2, 3);
	Vector3D vec12 = Vector3D(1, 2, 3);
	double multvv = vec11 * vec12;
	test(14, multvv);
	cout << endl;

	cout << "TEST: Multiplication vector by scalar" << endl;
	Vector3D vec13 = Vector3D(1, 2, 3);
	double multvs = vec13 * 2;
	test(12, multvs);
	cout << endl;

	cout << "TEST: Comparison operators" << endl;
	Vector3D vec14 = Vector3D(1, 2, 3);
	Vector3D vec15 = Vector3D(2, 4, 6);
	test(false, vec14 == vec15);
	test(true, vec14 != vec15);
	test(true, vec14 < vec15);
	test(true, vec15 > vec14);
	test(true, vec14 <= vec15);
	test(true, vec15 >= vec14);
	cout << endl;

	cout << "TEST: Stream output" << endl;
	Vector3D vec16 = Vector3D(1, 2, 3);
	cout << "Expected: " << "{ 1 ; 2 ; 3 }";
	cout << " Got: " << vec16;
	cout << endl << endl;

	cout << "TEST: Stream input" << endl;
	Vector3D vec17 = Vector3D(1.1, 2.2, 3.3);
	Vector3D vec18;
	cout << "Expected: " << "{ 1.1 ; 2.2 ; 3.3 }" << endl;
	cout << "Please enter the expected vector: ";
	cin >> vec18;
	cout << "Got: " << vec18;
	cout << endl;

	// Just to stop the console from closing
	int x; cin >> x;

	return 0;
}