#pragma once
#include <string>
#include <ctime>
#include "MyVector.h"

using namespace std;

class Contacts {
public:
	// Информация об одном контакте
	struct Contact
	{
		Contact() {
			surname = name = patronymic = "";
			phoneNumber = "";
			birthDay = birthMonth = birthYear = 0;
			isImportant = false;
		}

		string surname, name, patronymic;
		string phoneNumber;
		int birthDay, birthMonth, birthYear;
		bool isImportant;
	};

	// Конструктор по умолчанию
	Contacts();

	// Конструктор копирования
	Contacts(const Contacts& _c);

	// Перегрузка оператора присваивания
	Contacts& operator=(const Contacts& _c);

	// Деструктор
	~Contacts() { list.clear(); }

	// Добавить контакт в список
	void add(const Contact& _c);

	// Найти контакт по ФИО
	Contact * findByInitials(string _surname, string _name, string _patronymic);

	// Найти контакт по номеру телефона
	Contact * findByPhoneNumber(string _phoneNumber);

	// Получить набор контактов, ФИО которых начинается с указанной буквы
	MyVector<Contact> * getByFirstLetter(char _letter);

	// Получить длину списка контактов
	int getListLength() { return list.getSize(); }

	// Получить набор контактов, которые являются "избранными"
	MyVector<Contact> * getImportant();

	// Удалить контакт по ссылке.
	// Ссылку можно получить вызовом метода поиска по ФИО или номеру телефона.
	void remove(Contact& _c);

	// Сохранить контакты в файле
	friend ostream& operator<<(ostream& stream, const Contacts& _c);

	// Считать контакты из файла
	friend istream& operator>>(istream& stream, Contacts& _c);

	// Преобразовать информацию о заданном контакте в строку
	string contactToString(const Contact& _c) const;

private:
	// Список контактов
	MyVector<Contact> list;
};
