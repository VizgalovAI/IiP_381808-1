#pragma once
#include "Cinema.h"

// Создание пустого зала
Cinema::Hall::Hall() {
	rowsColumnsNumber = 0;
	seats = NULL;
	basePrice = { 0, 0 };
}

// Создание зала заданной конфигурации
// Формат _hallConfiguration :
// "dddd
//  dvvd
//  dvvd
//  dddd"
// d - обычное место, v - VIP место, переносов строки нет
Cinema::Hall::Hall(string _hallConfiguration, TicketPrice _ticketPrice) {
	basePrice = _ticketPrice;

	// Вычисляем число рядов (оно равно числу мест в ряде)
	int seatsQuantity = _hallConfiguration.length();
	double configSqrt = sqrt(seatsQuantity);
	if (floor(configSqrt) == ceil(configSqrt)) {
		rowsColumnsNumber = floor(configSqrt);
	}
	else throw "Количества рядов и мест в ряде не совпадают";

	// Создаем места
	seats = new Seat*[rowsColumnsNumber];
	for (int i = 0; i < rowsColumnsNumber; i++) {
		seats[i] = new Seat[rowsColumnsNumber];
	}
	for (int i = 0; i < rowsColumnsNumber; i++) {
		for (int j = 0; j < rowsColumnsNumber; j++) {
			seats[i][j].row = i;
			seats[i][j].column = j;
			seats[i][j].isVIP = (_hallConfiguration[i*rowsColumnsNumber + j] == 'v');
			seats[i][j].isBooked = false;
		}
	}
}

// Перегрузка оператора присваивания
// (для создания копии зала для каждого сеанса)
Cinema::Hall& Cinema::Hall::operator=(const Hall& _h) {
	// Проверка на присваивание самого себе
	if (this == &_h) return *this;

	// Очистить память, если размеры залов различаются
	if (rowsColumnsNumber != _h.rowsColumnsNumber &&
		seats != nullptr) {
		for (int i = 0; i < rowsColumnsNumber; i++) {
			delete[] seats[i];
		}
		delete[] seats;
		seats = NULL;
	}
	rowsColumnsNumber = _h.rowsColumnsNumber;

	// Выделить новую память, если требуется
	if (seats == nullptr) {
		seats = new Seat*[rowsColumnsNumber];
		for (int i = 0; i < rowsColumnsNumber; i++) {
			seats[i] = new Seat[rowsColumnsNumber];
		}
	}

	// Скопировать информацию о местах
	for (int i = 0; i < rowsColumnsNumber; i++) {
		for (int j = 0; j < rowsColumnsNumber; j++) {
			seats[i][j] = _h.seats[i][j];
		}
	}

	basePrice = _h.basePrice;

	return *this;
}

// Деструктор
Cinema::Hall::~Hall() {
	for (int i = 0; i < rowsColumnsNumber; i++) {
		delete[] seats[i];
	}
	delete[] seats;
}

// Создание сеанса с заданными параметрами
Cinema::Seance::Seance(Cinema * _cinema, int _year, int _month, int _day, int _hours, int _minutes, string _title, int _hallNumber, Hall * _hall) {
	dateTime.tm_year = _year;
	dateTime.tm_mon = _month;
	dateTime.tm_mday = _day;
	dateTime.tm_hour = _hours;
	dateTime.tm_min = _minutes;
	movieTitle = _title;
	hallNumber = _hallNumber;
	hall = *_hall;
	ticketPrice = calcPrice(_hall->basePrice, dateTime);
}

// Конструктор по умолчанию (пустой кинотеатр)
Cinema::Cinema() {
	hallsQuantity = seancesQuantity = 0;
	halls = NULL;
	seances = NULL;
}

// Создать кинотеатр
Cinema::Cinema(int _hallsQuantity, Hall * _halls, int _seancesQuantity, Seance * _seances) {
	hallsQuantity = _hallsQuantity;
	halls = _halls;

	seancesQuantity = _seancesQuantity;
	seances = _seances;
}

// Перегрузка оператора присваивания
Cinema& Cinema::operator=(const Cinema& _c) {
	if (this == &_c) return *this;

	if (hallsQuantity != _c.hallsQuantity) {
		delete[] halls;
	}
	hallsQuantity = _c.hallsQuantity;
	halls = new Hall[hallsQuantity];
	for (int i = 0; i < hallsQuantity; i++)
	{
		halls[i] = _c.halls[i];
	}

	if (seancesQuantity != _c.seancesQuantity) {
		delete[] seances;
	}
	seancesQuantity = _c.seancesQuantity;
	seances = new Seance[seancesQuantity];
	for (int i = 0; i < seancesQuantity; i++)
	{
		seances[i] = _c.seances[i];
	}

	return *this;
}

// Деструктор
Cinema::~Cinema() {
	hallsQuantity = seancesQuantity = 0;
	delete[] halls;
	delete[] seances;
}

// Вычислить цену билета на заданный сеанс
Cinema::TicketPrice Cinema::calcPrice(TicketPrice _basePrice, tm _seanceTime) {
	TicketPrice _ticketPrice = { _basePrice.defaultPrice, _basePrice.vipPrice };
	if (_seanceTime.tm_hour < 12) { // утро, до 12:00
		_ticketPrice.defaultPrice *= 0.75;
		_ticketPrice.vipPrice *= 0.75;
	} else if (_seanceTime.tm_hour >= 18) { // вечер, с 18:00
		_ticketPrice.defaultPrice *= 1.5;
		_ticketPrice.vipPrice *= 1.5;
	}
	return _ticketPrice;
}

// Преобразовать время в читаемый формат "4" -> "04"
string Cinema::formatTime(int time) {
	string str = "";
	if (time < 10) {
		str += "0";
	}
	str += to_string(time);
	return str;
}