#pragma once
#include <string>
#include <iostream>
#include <windows.h>
#include <conio.h>

using namespace std;

// Simple single-line text editor
class TextEditor {
public:
	// Default initialization constructor
	TextEditor();

	// Initialization with specified field length , its postion and default string
	TextEditor(int _fieldLength, pair<int, int> _position, string _str);

	// Copy constructor
	TextEditor(const TextEditor& _te);

	// Assignment operator overload
	TextEditor& operator=(const TextEditor& _te);

	// Destructor
	~TextEditor();

	// Stream output operator overload
	friend ostream& operator<<(ostream& stream, const TextEditor& _te);

	// Stream input operator overload
	friend istream& operator>>(istream& stream, TextEditor& _te);

	// Set methods for all input field's parameters
	void setInputFieldLength(int _length);
	void setInputFieldPosition(pair<int, int> _coords);
	void setInputString(string _str);

	// Get methods for all input field's parameters
	int getInputFieldLength() { return inputFieldLength; }
	pair<int, int> getInputFieldPosition() { return inputFieldPosition; }
	string getInputString() { return inputString; }

	// Open console interface
	void runConsole();

	// Unit testing method
	friend void testTextEditor();

private:
	// === CONSOLE INTERFACE ==================================================
	// Console handle
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

	// Set cursor position in the console
	void setCursorPosition(pair<int, int> _pos);

	// Print the logo, options and menu to console
	void printInterface(int _option);

	// Lets the user choose commands from menu
	// by using ARROWS and ENTER keys
	int getMenuOption();

	// Lets the user set the length of input field 
	void editLength(bool __firstCall);

	// Lets the user set the position of input field 
	void editPosition(bool __firstCall);

	// Lets the user edit the text
	void editText(bool __firstCall);
	// ========================================================================

	// Length of the input field
	int inputFieldLength;

	// Input field position coordinates
	// .first = x
	// .second = y
	pair<int, int> inputFieldPosition;

	// Text string
	string inputString;
};