#include "TextEditor.h"
#include <string>
#include <iostream>
#include <fstream>

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

void testTextEditor() {
	cout << "TEST: Default initialization constructor" << endl;
	TextEditor te1;
	test(0, te1.inputFieldLength);
	test(0, te1.inputFieldPosition.first);
	test(0, te1.inputFieldPosition.second);
	test("", te1.inputString);
	cout << endl;

	cout << "TEST: Initialization with specified field length and its coordinates" << endl;
	TextEditor te2(20, {30, 40}, "aaa");
	test(20, te2.inputFieldLength);
	test(30, te2.inputFieldPosition.first);
	test(40, te2.inputFieldPosition.second);
	test("aaa", te2.inputString);
	cout << endl;

	cout << "TEST: Assignment operator overload" << endl;
	TextEditor te3(10, { 20, 30 }, "aaa");
	TextEditor te4(10, { 10, 10 }, "bbb");
	te3 = te4;
	test(10, te3.inputFieldLength);
	test(10, te3.inputFieldPosition.first);
	test(10, te3.inputFieldPosition.second);
	test("bbb", te3.inputString);
	cout << endl;

	cout << "TEST: Stream I/O for console" << endl;
	cout << "Test values:" << endl;
	TextEditor te5(10, { 20, 30 }, "aaa");
	TextEditor te6;
	cout << te5;
	cout << endl << "Please enter the values above:" << endl;
	cin >> te6;
	test(10, te6.inputFieldLength);
	test(20, te6.inputFieldPosition.first);
	test(30, te6.inputFieldPosition.second);
	test("aaa", te6.inputString);
	cout << endl;

	cout << "TEST: Stream I/O for file" << endl;
	TextEditor te7;
	ifstream teInput("teInput.txt");
	teInput >> te7;
	teInput.close();
	ofstream teOutput("teOutput.txt");
	teOutput << te7;
	teOutput.close();
	cout << "File operation was completed, please check 'teOutput.txt'";
	cout << endl;

	cout << "TEST: Set methods for all input field's parameters" << endl;
	TextEditor te8;
	te8.setInputFieldLength(10);
	te8.setInputFieldPosition({ 20, 30 });
	te8.setInputString("aaa");
	test(10, te8.inputFieldLength);
	test(20, te8.inputFieldPosition.first);
	test(30, te8.inputFieldPosition.second);
	test("aaa", te8.inputString);
	cout << endl;

	cout << "TEST: Console interface" << endl;
	cout << "Do you want to test the console interface? (yes/no) ";
	string ans;
	cin >> ans;
	if (ans == "yes") {
		cin.ignore(1);
		system("cls");
		TextEditor te9(20, {40, 40}, "aaa");
		te9.runConsole();
	}
}

int main() {
	testTextEditor();

	system("pause");
	return 0;
}