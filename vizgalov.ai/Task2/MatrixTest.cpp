#include "Matrix.h"
#include <windows.h>
#include <fstream>
#include <string>

using namespace std;

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

void testMatrix() {
	cout << "TEST: Default initialization constructor (size=0, no memory allocation)" << endl;
	Matrix mat;
	test(0, mat.size);
	if (mat.mat == nullptr) test(NULL, NULL);
	cout << endl;

	cout << "TEST: Initialization of null matrix of specified size" << endl;
	Matrix mat1(3);
	test(3, mat1.size);
	test(0, mat1[1][1]);
	cout << endl;

	cout << "TEST: Initialization of matrix from ** pointer" << endl;
	int ** pMat = new int*[2];
	pMat[0] = new int[2];
	pMat[1] = new int[2];
	pMat[0][0] = 1; pMat[0][1] = 2;
	pMat[1][0] = 3; pMat[1][1] = 4;
	Matrix mat2(2, pMat);
	test(2, mat2.size);
	test(4, mat2[1][1]);
	cout << endl;

	cout << "TEST: Assignment operator overload" << endl;
	Matrix mat3(2, pMat);
	Matrix mat4(2);
	mat3 = mat4;
	test(0, mat3[1][1]);
	cout << endl;

	cout << "TEST: Set the matrix size and allocate enough memory" << endl;
	Matrix mat5(3);
	mat5.setSize(7);
	test(7, mat5.size);
	cout << endl;

	cout << "TEST: Get size of the matrix" << endl;
	test(mat5.size, mat5.getSize());
	cout << endl;

	cout << "TEST: Check if matrix has diagonal dominance" << endl;
	int ** pMat1 = new int*[3];
	pMat1[0] = new int[3];
	pMat1[1] = new int[3];
	pMat1[2] = new int[3];
	pMat1[0][0] = 10; pMat1[0][1] = 2; pMat1[0][2] = 3;
	pMat1[1][0] = 3; pMat1[1][1] = 10; pMat1[1][2] = 0;
	pMat1[2][0] = 1; pMat1[2][1] = 8; pMat1[2][2] = 10;
	Matrix mat6(3, pMat1);
	int ** pMat2 = new int*[3];
	pMat2[0] = new int[3];
	pMat2[1] = new int[3];
	pMat2[2] = new int[3];
	pMat2[0][0] = 1; pMat2[0][1] = 2; pMat2[0][2] = 3;
	pMat2[1][0] = 3; pMat2[1][1] = 10; pMat2[1][2] = 0;
	pMat2[2][0] = 1; pMat2[2][1] = 8; pMat2[2][2] = 10;
	Matrix mat7(3, pMat2);
	test(true, mat6.checkDiagonalDominance());
	test(false, mat7.checkDiagonalDominance());
	cout << endl;


	// TODO
	cout << "TEST: Addition and subtraction operators overload" << endl;
	mat6 += mat7;
	test(20, mat6[1][1]);
	mat6 -= mat7;
	test(10, mat6[1][1]);
	Matrix mat8(3, pMat1);
	mat8 = mat6 + mat7;
	test(20, mat8[1][1]);
	mat8 = mat6 - mat7;
	test(0, mat8[1][1]);
	cout << endl;

	cout << "TEST: [][] indexing" << endl;
	Matrix mat9(3);
	mat9[1][1] = 15;
	test(mat9.mat[1][1], mat9[1][1]);
	cout << endl;

	cout << "TEST: Stream I/O on console" << endl;
	Matrix mat10(3);
	cout << "Please enter 3x3 matrix: " << endl;
	cin >> mat10;
	cout << "Result:" << endl;
	cout << mat10;
	cout << endl;

	cout << "TEST: Stream I/O on file" << endl;
	Matrix mat11(3);
	ifstream matrixInput("matrixInput.txt");
	matrixInput >> mat11;
	matrixInput.close();
	ofstream matrixOutput("matrixOutput.txt");
	matrixOutput << mat11;
	matrixOutput.close();
	cout << "File operation was completed, please check 'matrixOutput.txt'";
	cout << endl;
}

int main() {
	testMatrix();

	// Enter any key to close the console
	char exit;
	cin >> exit;

	return 0;
}