#pragma once
#include <locale.h>
#include <fstream>
#include <string>
#include <iostream>
#include <Windows.h>
#include "Contacts.h"
#include "MyVector.h"

using namespace std;

// Вывести сообщение об окончании выполнения операции
void endMessage(string _msg) {
	cout << endl << _msg << endl;
	getchar();
	getchar();
}

int main() {
	// Ввод/вывод на русском языке
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	Contacts PhoneBook;

	int option;
	bool exit = false;
	Contacts::Contact * chosenContact = new Contacts::Contact();
	while (!exit) {
		system("cls");
		cout << "-----Список контактов-----" << endl << endl;

		cout << "Контакты: " << endl;
		cout << PhoneBook;
		cout << endl;

		cout << "Выбран: " << endl;
		if (chosenContact->surname != "") // проверка выбран ли контакт
			cout << PhoneBook.contactToString(*chosenContact) << endl;
		cout << endl;

		cout << "Действия:" << endl;
		cout << "[1] Создать новый контакт" << endl;
		cout << "[2] Найти контакт по ФИО" << endl;
		cout << "[3] Изменить контакт" << endl;
		cout << "[4] Найти контакт по телефону" << endl;
		cout << "[5] Получить все контакты на заданную букву" << endl;
		cout << "[6] Узнать число контактов" << endl;
		cout << "[7] Внести контакт в список избранных" << endl;
		cout << "[8] Удалить контакт из списка избранных" << endl;
		cout << "[9] Показать все избранные контакты" << endl;
		cout << "[10] Удалить контакт" << endl;
		cout << "[11] Записать контакты в файл" << endl;
		cout << "[12] Считать контакты из файла" << endl;
		cout << "[0] Выйти" << endl << endl;

		cout << "Ваш выбор: ";
		cin >> option;

		string inp;
		char letter;
		Contacts::Contact newCont;
		MyVector<Contacts::Contact> * vec;
		ofstream outputFile("output.txt");
		ifstream inputFile("input.txt");
		switch (option)
		{
		case 1:
			try {
				newCont = Contacts::Contact();
				cout << "Фамилия: ";
				cin >> newCont.surname;
				cout << "Имя: ";
				cin >> newCont.name;
				cout << "Отчество: ";
				cin >> newCont.patronymic;
				cout << "Номер телефона: ";
				cin >> newCont.phoneNumber;
				cout << "День рождения: ";
				cin >> newCont.birthDay;
				cout << "Месяц рождения: ";
				cin >> newCont.birthMonth;
				cout << "Год рождения: ";
				cin >> newCont.birthYear;
				cout << "Сделать контакт избранным? (0=нет, 1=да): ";
				cin >> newCont.isImportant;

				PhoneBook.add(newCont);
				endMessage("Контакт добавлен");
			}
			catch (...) {
				endMessage("Ошибка при добавлении контакта");
			}
			break;
		case 2:
			try {
				cout << "Фамилия: ";
				cin >> newCont.surname;
				cout << "Имя: ";
				cin >> newCont.name;
				cout << "Отчество: ";
				cin >> newCont.patronymic;

				chosenContact = PhoneBook.findByInitials(newCont.surname, newCont.name, newCont.patronymic);
				endMessage("Контакт найден");
			}
			catch (...) {
				endMessage("Контакт не найден");
			}
			break;
		case 3:
			try {
				newCont = Contacts::Contact();
				cout << "Введите новое значение или '-' если изменять не нужно" << endl;
				cout << "Фамилия: ";
				cin >> inp;
				newCont.surname = (inp != "-") ? inp : chosenContact->surname;
				cout << "Имя: ";
				cin >> inp;
				newCont.name = (inp != "-") ? inp : chosenContact->name;
				cout << "Отчество: ";
				cin >> inp;
				newCont.patronymic = (inp != "-") ? inp : chosenContact->patronymic;
				cout << "Номер телефона: ";
				cin >> inp;
				newCont.phoneNumber = (inp != "-") ? inp : chosenContact->phoneNumber;
				cout << "День рождения: ";
				cin >> inp;
				newCont.birthDay = (inp != "-") ? stoi(inp) : chosenContact->birthDay;
				cout << "Месяц рождения: ";
				cin >> inp;
				newCont.birthMonth = (inp != "-") ? stoi(inp) : chosenContact->birthMonth;
				cout << "Год рождения: ";
				cin >> inp;
				newCont.birthYear = (inp != "-") ? stoi(inp) : chosenContact->birthYear;
				cout << "Сделать контакт избранным? (0=нет, 1=да): ";
				cin >> inp;
				newCont.isImportant = (inp != "-") ? stoi(inp) : chosenContact->isImportant;

				PhoneBook.remove(*chosenContact); // удалим ранее выбранный
				PhoneBook.add(newCont); // поместим измененный в конец, затем переместим в позицию по алфавиту
				chosenContact->surname = ""; // отменим выбор
				endMessage("Контакт изменен");
			}
			catch (...) {
				endMessage("Ошибка при изменении контакта");
			}
			break;
		case 4:
			try {
				cout << "Номер телефона: ";
				cin >> newCont.phoneNumber;

				chosenContact = PhoneBook.findByPhoneNumber(newCont.phoneNumber);
				endMessage("Контакт найден");
			}
			catch (...) {
				endMessage("Контакт не найден");
			}
			break;
		case 5:
			try {
				cout << "Введите букву: ";
				cin >> letter;
				vec = PhoneBook.getByFirstLetter(letter);
				cout << endl << "Найдены контакты: " << endl;
				for (int i = 0; i < vec->getSize(); i++)
					cout << PhoneBook.contactToString((*vec)[i]) << endl;
				endMessage("");
			}
			catch (...) {
				endMessage("Ошибка при поиске контактов");
			}
			break;
		case 6:
			cout << "Число контактов в списке: " << PhoneBook.getListLength();
			endMessage("");
			break;
		case 7:
			chosenContact->isImportant = true;
			endMessage("Контакт добавлен в избранные");
			break;
		case 8:
			chosenContact->isImportant = false;
			endMessage("Контакт удален из избранных");
			break;
		case 9:
			try {
				vec = PhoneBook.getImportant();
				cout << endl << "Найдены контакты: " << endl;
				for (int i = 0; i < vec->getSize(); i++)
					cout << PhoneBook.contactToString((*vec)[i]) << endl;
				endMessage("");
			}
			catch (...) {
				endMessage("Ошибка при поиске контактов");
			}
			break;
		case 10:
			try {
				PhoneBook.remove(*chosenContact);
				chosenContact->surname = ""; // отменим выбор
				endMessage("Контакт удален");
			}
			catch (...) {
				endMessage("Ошибка при удалении контакта");
			}
			break;
		case 11:
			try {
				outputFile << PhoneBook;
				outputFile.close();
				endMessage("Контакты записаны в файл");
			}
			catch (...) {
				endMessage("Ошибка при записи в файл");
			}
			break;
		case 12:
			try {
				inputFile >> PhoneBook;
				inputFile.close();
				endMessage("Контакты считаны из файла");
			}
			catch (...) {
				endMessage("Ошибка при чтении из файла");
			}
			break;
		case 0:
			exit = true;
			break;
		default:
			endMessage("Выбрано несуществующее действие");
		}
	}

	return 0;
}