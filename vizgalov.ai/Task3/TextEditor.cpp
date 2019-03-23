#pragma once
#include "TextEditor.h"

// Default initialization constructor
TextEditor::TextEditor() {
	inputFieldLength = 0;
	inputFieldPosition = { 0, 0 };
	inputString = "";
}

// Initialization with specified field length and its coordinates
TextEditor::TextEditor(int _fieldLength, pair<int, int> _position, string _str) {
	inputFieldLength = _fieldLength;
	inputFieldPosition = _position;
	inputString = _str;
}

// Copy constructor
TextEditor::TextEditor(const TextEditor& _te) {
	inputFieldLength = _te.inputFieldLength;
	inputFieldPosition = _te.inputFieldPosition;
	inputString = _te.inputString;
}

// Assignment operator overload
TextEditor& TextEditor::operator=(const TextEditor& _te) {
	inputFieldLength = _te.inputFieldLength;
	inputFieldPosition = _te.inputFieldPosition;
	inputString = _te.inputString;
	return *this;
}

// Destructor
TextEditor::~TextEditor() {
	inputFieldLength = 0;
	inputFieldPosition = { 0, 0 };
	inputString = "";
}

// Stream output operator overload
ostream& operator<<(ostream& stream, const TextEditor& _te) {
	// Output format:	| inputFieldLength			|
	//					| cursorPos.x cursorPos.y	|
	//					| inputString				|
	stream << _te.inputFieldLength << endl;
	stream << _te.inputFieldPosition.first << " " << _te.inputFieldPosition.second << endl;
	stream << _te.inputString;
	return stream;
}

// Stream input operator overload
istream& operator>>(istream& stream, TextEditor& _te) {
	// Input format:	| inputFieldLength			|
	//					| cursorPos.x cursorPos.y	|
	//					| inputString				|
	int length, x, y;
	string str;
	stream >> length >> x >> y >> str;
	_te.setInputFieldLength(length);
	_te.setInputFieldPosition({x, y});
	_te.setInputString(str);
	return stream;
}

// Set methods for all input field's parameters
void TextEditor::setInputFieldLength(int _length) {
	if (inputFieldPosition.first + _length > 80)
		throw "Input field length must fit the console window";
	inputFieldLength = _length;
}
void TextEditor::setInputFieldPosition(pair<int, int> _coords) {
	if (_coords.first < 0 || _coords.first > (80 - inputFieldLength))
		throw "Input field length must fit the console window";
	inputFieldPosition = _coords;
}
void TextEditor::setInputString(string _str) {
	if (_str.length() > inputFieldLength)
		throw "The text is too long";
	inputString = _str;
}

// Open console interface
void TextEditor::runConsole() {
	bool isRunning = true;
	int option = 0;
	bool firstCall[4] = { true, true, true, true };

	// Menu navigation
	while (isRunning) {
		printInterface(option);
		option = getMenuOption();

		switch (option) {
		case 0: {
			editLength(firstCall[option]);
			firstCall[option] = false;
			break;
		}
		case 1: {
			editPosition(firstCall[option]);
			firstCall[option] = false;
			break;
		}
		case 2: {
			editText(firstCall[option]);
			firstCall[option] = false;
			break;
		}
		case 3:
			isRunning = false;
			break;
		}

		Sleep(150);
	}
}

// Set cursor position in the console
void TextEditor::setCursorPosition(pair<int, int> _pos)
{
	COORD coords = { _pos.first, _pos.second };
	SetConsoleCursorPosition(hConsole, coords);
}

// Print the logo, options and menu to console
void TextEditor::printInterface(int _option) {
	// Clear screen and flush input buffer
	system("cls");
	fflush(stdin);

	// Print text editor's logo in green color
	SetConsoleTextAttribute(hConsole, 10);
	cout << "TextEditor (by VizgalovAI)" << endl << endl;
	SetConsoleTextAttribute(hConsole, 7);

	// Print the options
	cout << "Current options:" << endl;
	cout << "- Input field length: " << inputFieldLength << endl;
	cout << "- Input field position: " << inputFieldPosition.first << ", " << inputFieldPosition.second << endl;
	cout << "- Text: " << inputString << endl << endl;

	// Print the menu
	cout << "---Menu:----------------" << endl;
	string menuItems[] = { "Set input field length", 
					  "Set input field position",
					  "Enter new text",
					  "Exit" };
	for (int i = 0; i < 4; i++) {
		if (i == _option) {
			SetConsoleTextAttribute(hConsole, BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED);
			cout << menuItems[i];
			SetConsoleTextAttribute(hConsole, 7);
		}
		else {
			cout << menuItems[i];
		}
		cout << endl;
	}
	cout << "------------------------" << endl;
}

// Lets the user choose commands from menu
// by using ARROWS KEYS and ENTER KEY
int TextEditor::getMenuOption() {
	int option = 0;
	bool optionChosen = false;
	bool moveFlag = false;

	while (!optionChosen) {
		printInterface(option);

		while (true) {
			if (GetKeyState(VK_DOWN) & 0x8000) {
				if (option < 3) option++;
				Sleep(150);
				moveFlag = true;
				break;
			}
			else if (GetKeyState(VK_UP) & 0x8000) {
				if (option > 0) option--;
				Sleep(150);
				moveFlag = true;
				break;
			}
			else if (GetKeyState(VK_RETURN) & 0x8000) {
				optionChosen = true;
				if (moveFlag) cin.ignore(1);
				printInterface(option);
				break;
			}
		}
	}
	return option;
}

// Lets the user set the length of input field 
void TextEditor::editLength(bool __firstCall) {
	int length;
	do {
		if (__firstCall) {
			cin.ignore(1);
		}
		else {
			cin.ignore(2);
		}
		printInterface(0);
		cout << "Enter new input field length (from 1 to 80): ";
		cin >> length;
		try {
			setInputFieldLength(length);
			break;
		}
		catch (const char * exc) { }
	} while (true);
}

// Lets the user set the position of input field
void TextEditor::editPosition(bool __firstCall) {
	int x, y;
	do {
		if (!__firstCall) {
			cin.ignore(1);
		}
		printInterface(0);
		cout << "Enter new X coordinate of the field (from 0 to " << 80 - inputFieldLength << "): ";
		cin >> x;
		try {
			setInputFieldPosition({x, inputFieldPosition.second});
			break;
		}
		catch (const char * exc) { }
	} while (true);

	cout << "Enter new Y coordinate of the field: ";
	cin >> y;
	setInputFieldPosition({ inputFieldPosition.first, y });
}

// Lets the user edit the text
void TextEditor::editText(bool __firstCall) {
	char inpChar, tmp;
	do {
		setCursorPosition(inputFieldPosition);
		cout << inputString;
		for (int i = 0; i < inputFieldLength - inputString.length(); i++) {
			cout << "_";
		}
		setCursorPosition({ inputFieldPosition.first + inputString.length(), inputFieldPosition.second });
		inpChar = _getwch();

		if (inpChar == '\r')
			break;

		if (inpChar == '\b' && inputString.length() > 0) {
			if (inputString.length() > 0) {
				inputString.erase(inputString.length() - 1);
			}
			continue;
		}

		if (inputString.length() < inputFieldLength) {
			inputString += inpChar;
		}
	} while (true);
}
