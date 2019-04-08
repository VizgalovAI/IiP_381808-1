#pragma once
#include "Contacts.h"
#include "MyVector.h"

// Конструктор по умолчанию
Contacts::Contacts() {
	list = MyVector<Contact>();
}

// Конструктор копирования
Contacts::Contacts(const Contacts& _c) {
	if (this != &_c) {
		list = _c.list;
	}
}

// Перегрузка оператора присваивания
Contacts& Contacts::operator=(const Contacts& _c) {
	if (this != &_c) {
		list = _c.list;
	}
	return *this;
}

// Добавить контакт в список
void Contacts::add(const Contact& _c) {
	list.pushBack(_c);

	// Переместим добавленный контакт так, чтобы он не нарушал алфавитный порядок 
	for (int i = list.getSize() - 1; i > 0; i--) {
		if ((list[i].surname < list[i - 1].surname) ||
			((list[i].surname == list[i - 1].surname) && (list[i].name < list[i - 1].name)) ||
			((list[i].surname == list[i - 1].surname) && (list[i].name == list[i - 1].name) && (list[i].patronymic < list[i - 1].patronymic))) {
			swap(list[i], list[i - 1]);
		}
	}
}

// Найти контакт по ФИО
Contacts::Contact * Contacts::findByInitials(string _surname, string _name, string _patronymic) {
	for (int i = 0; i < list.getSize(); i++)
	{
		if (list[i].surname == _surname &&
			list[i].name == _name &&
			list[i].patronymic == _patronymic) {
			return &list[i];
		}
	}
	throw "Not found";
}

// Найти контакт по номеру телефона
Contacts::Contact * Contacts::findByPhoneNumber(string _phoneNumber) {
	for (int i = 0; i < list.getSize(); i++)
	{
		if (list[i].phoneNumber == _phoneNumber) {
			return &list[i];
		}
	}
	throw "Not found";
}

// Получить набор контактов, ФИО которых начинается с указанной буквы
MyVector<Contacts::Contact> * Contacts::getByFirstLetter(char _letter) {
	MyVector<Contact> * newList = new MyVector<Contact>();
	for (int i = 0; i < list.getSize(); i++)
	{
		if (list[i].surname[0] == _letter) {
			newList->pushBack(list[i]);
		}
	}
	return newList;
}

// Получить набор контактов, которые являются "избранными"
MyVector<Contacts::Contact> * Contacts::getImportant() {
	MyVector<Contact> * newList = new MyVector<Contact>();
	for (int i = 0; i < list.getSize(); i++)
	{
		if (list[i].isImportant) {
			newList->pushBack(list[i]);
		}
	}
	return newList;
}

// Удалить контакт по ссылке.
// Ссылку можно получить вызовом метода поиска по ФИО или номеру телефона.
void Contacts::remove(Contact& _c) {
	for (int i = 0; i < list.getSize(); i++)
	{
		if (&list[i] == &_c) {
			list.erase(i);
			break;
		}
	}
}

// Сохранить контакты в файле
ostream& operator<<(ostream& stream, const Contacts& _c) {
	for (int i = 0; i < _c.list.getSize(); i++)
		stream << _c.contactToString(_c.list[i]) << endl;
	return stream;
}

// Считать контакты из файла
istream& operator>>(istream& stream, Contacts& _c) {
	_c.list.clear();
	string input;
	Contacts::Contact newCont = Contacts::Contact();
	while (!stream.eof())
	{
		stream >> newCont.surname >> newCont.name >> newCont.patronymic;
		stream >> newCont.phoneNumber;
		stream >> newCont.birthDay >> input >> newCont.birthMonth >> input >> newCont.birthYear;
		stream >> input;
		newCont.isImportant = (input == "(Избранный)");
		_c.add(newCont);
	}
	return stream;
}

// Преобразовать информацию о заданном контакте в строку
string Contacts::contactToString(const Contact& _c) const {
	string str = "" + _c.surname + " " + _c.name + " " + _c.patronymic + " " + _c.phoneNumber +
		" " + to_string(_c.birthDay) + " / " + to_string(_c.birthMonth) + " / " + to_string(_c.birthYear) +
		((_c.isImportant) ? " (Избранный)" : " ()");
	return str;
}