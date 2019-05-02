#pragma once
#include <locale.h>
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Cinema.h"
#include "TicketOffice.h"

using namespace std;

int main() {
	// Ввод/вывод на русском языке
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	TicketOffice TO;
	ifstream toInput("input.txt");
	toInput >> TO;

	TO.runTicketOffice();

	ofstream toOutput("output.txt");
	toOutput << TO;

	return 0;
}