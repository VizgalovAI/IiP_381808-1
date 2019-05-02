#pragma once
#include <iostream>
#include <fstream>
#include "TicketOffice.h"

using namespace std;

// Конструктор по умолчанию
TicketOffice::TicketOffice() {
	cinema = new Cinema();
}

// Конструктор кассы для уже существующего кинотеатра
TicketOffice::TicketOffice(Cinema * _cinema) {
	cinema = _cinema;
}

// Конструктор копирования
TicketOffice::TicketOffice(const TicketOffice& _to) {
	if (this == &_to) return;
	cinema = _to.cinema;
}

// Перегрузка оператора присваивания
TicketOffice& TicketOffice::operator=(const TicketOffice& _to) {
	if (this == &_to) return *this;
	cinema = _to.cinema;
	return *this;
}

// Деструктор
TicketOffice::~TicketOffice() {
	delete cinema;
}

//--------------------------------------------------------------------------------------------------------------------------

// Принять заказ билетов покупателем
Cinema::Seat * TicketOffice::processOrder(const Cinema::Seance& _seance, int _defaultSeatsQuantity, int _vipSeatsQuantity) {
	Cinema::Seance * seance = NULL;
	bool found = false;
	for (int i = 0; i < cinema->seancesQuantity; i++) {
		seance = &cinema->seances[i];
		if (_seance.dateTime.tm_year == seance->dateTime.tm_year &&
			_seance.dateTime.tm_mon == seance->dateTime.tm_mon &&
			_seance.dateTime.tm_mday == seance->dateTime.tm_mday &&
			_seance.dateTime.tm_hour == seance->dateTime.tm_hour &&
			_seance.dateTime.tm_min == seance->dateTime.tm_min &&
			_seance.movieTitle == seance->movieTitle &&
			_seance.hallNumber == seance->hallNumber) {
			found = true;
			break;
		}
	}
	if (!found) 
		throw "Такого сеанса нет";

	if (!checkTime(seance->dateTime)) {
		throw "Билеты на этот сеанс не продаются";
		return NULL;
	}

	if (!checkSeatsAvailiable(seance->hall, _defaultSeatsQuantity, _vipSeatsQuantity))
		throw "Недостаточно свободных мест";

	return reserveSeats(seance->hall, _defaultSeatsQuantity, _vipSeatsQuantity);
}

// Проверить наличие свободных мест в обеих зонах
bool TicketOffice::checkSeatsAvailiable(const Cinema::Hall& _hall, int _defaultSeatsQuantity, int _vipSeatsQuantity) {
	for (int i = 0; i < _hall.rowsColumnsNumber; i++) {
		for (int j = 0; j < _hall.rowsColumnsNumber; j++) {
			if (!_hall.seats[i][j].isBooked) {
				if (_hall.seats[i][j].isVIP && _vipSeatsQuantity > 0) {
					_vipSeatsQuantity--;
				}
				if (!_hall.seats[i][j].isVIP && _defaultSeatsQuantity > 0) {
					_defaultSeatsQuantity--;
				}
			}
			if (_defaultSeatsQuantity == 0 && _vipSeatsQuantity == 0) return true;
		}
	}
	return false;
}

// Зарезервировать требуемое количество мест
Cinema::Seat * TicketOffice::reserveSeats(const Cinema::Hall& _hall, int _defaultSeatsQuantity, int _vipSeatsQuantity) {
	Cinema::Seat * reservedSeats = new Cinema::Seat[_defaultSeatsQuantity + _vipSeatsQuantity];
	int queueTailIdx = 0;

	for (int i = 0; i < _hall.rowsColumnsNumber; i++) {
		for (int j = 0; j < _hall.rowsColumnsNumber; j++) {
			if (!_hall.seats[i][j].isBooked) {
				if (_hall.seats[i][j].isVIP && _vipSeatsQuantity > 0) {
					_vipSeatsQuantity--;
					_hall.seats[i][j].isBooked = true;
					reservedSeats[queueTailIdx++] = _hall.seats[i][j];
				}
				if (!_hall.seats[i][j].isVIP && _defaultSeatsQuantity > 0) {
					_defaultSeatsQuantity--;
					_hall.seats[i][j].isBooked = true;
					reservedSeats[queueTailIdx++] = _hall.seats[i][j];
				}
			}
			if (_defaultSeatsQuantity == 0 && _vipSeatsQuantity == 0) return reservedSeats;
		}
	}
	throw "Недостаточно свободных мест";
}

// Рассчитать общую стоимость билетов
double TicketOffice::calcTotalCost(const Cinema::Seance& _seance, int _defaultSeatsQuantity, int _vipSeatsQuantity) {
	return _seance.ticketPrice.defaultPrice*_defaultSeatsQuantity + _seance.ticketPrice.vipPrice*_vipSeatsQuantity;
}

// Отменить заказ билета
void TicketOffice::cancelSeatReservation(const Cinema::Seance& _seance, int _seatRow, int _seatColumn) {
	Cinema::Seance * seance = NULL;
	bool found = false;
	for (int i = 0; i < cinema->seancesQuantity; i++) {
		seance = &cinema->seances[i];
		if (_seance.dateTime.tm_year == seance->dateTime.tm_year &&
			_seance.dateTime.tm_mon == seance->dateTime.tm_mon &&
			_seance.dateTime.tm_mday == seance->dateTime.tm_mday &&
			_seance.dateTime.tm_hour == seance->dateTime.tm_hour &&
			_seance.dateTime.tm_min == seance->dateTime.tm_min &&
			_seance.movieTitle == seance->movieTitle &&
			_seance.hallNumber == seance->hallNumber) {
			found = true;
			break;
		}
	}
	if (!found)
		throw "Такого сеанса нет";

	if (seance->hall.seats[_seatRow][_seatColumn].isBooked) {
		seance->hall.seats[_seatRow][_seatColumn].isBooked = false;
	}
	else {
		throw "Место не было забронировано";
	}
}

// Сформировать билеты
TicketOffice::Ticket * TicketOffice::createTickets(const Cinema::Seance& _seance, Cinema::Seat * _seats, int _seatsCount) {
	Ticket * tickets = new Ticket[_seatsCount];
	for (int i = 0; i < _seatsCount; i++) {
		tickets[i].dateTime = _seance.dateTime;
		tickets[i].hallNumber = _seance.hallNumber;
		tickets[i].movieTitle = _seance.movieTitle;
		tickets[i].seatRowNumber = _seats[i].row;
		tickets[i].seatColumnNumber = _seats[i].column;
	}
	return tickets;
}

// Напечатать билеты в поток
ostream& TicketOffice::printTickets(ostream& stream, Ticket * _tickets, int _ticketsCount) {
	for (int i = 0; i < _ticketsCount; i++) {
		stream << "Билет на фильм \"" << _tickets[i].movieTitle << "\"" << endl;
		stream << "Дата: " << _tickets[i].dateTime.tm_mday << "."
			<< (_tickets[i].dateTime.tm_mon + 1) << "." << (_tickets[i].dateTime.tm_year+1900) << endl;
		stream << "Начало сеанса: " << Cinema::formatTime(_tickets[i].dateTime.tm_hour) << ":"
			<< Cinema::formatTime(_tickets[i].dateTime.tm_min) << endl;
		stream << "Зал: " << _tickets[i].hallNumber << endl;
		stream << "Ряд: " << _tickets[i].seatRowNumber << endl;
		stream << "Место: " << _tickets[i].seatColumnNumber << endl;
		if (i != _ticketsCount - 1) stream << "---------------------------------------------------" << endl;
	}
	return stream;
}

//--------------------------------------------------------------------------------------------------------------------------

// Вывод информации о билетной кассе в поток
ostream& operator<<(ostream& stream, const TicketOffice& _to) {
	Cinema::Hall * hall;
	stream << _to.cinema->hallsQuantity << endl;
	for (int i = 0; i < _to.cinema->hallsQuantity; i++) {
		hall = &_to.cinema->halls[i];
		stream << hall->rowsColumnsNumber << endl;
		stream << hall->basePrice.defaultPrice << " " << hall->basePrice.vipPrice << endl;
		for (int j = 0; j < hall->rowsColumnsNumber; j++) {
			for (int k = 0; k < hall->rowsColumnsNumber; k++) {
				stream << (hall->seats[j][k].isVIP ? "v" : "d");
			}
			stream << endl;
		}
	}

	Cinema::Seance * seance;
	stream << _to.cinema->seancesQuantity << endl;
	for (int i = 0; i < _to.cinema->seancesQuantity; i++) {
		seance = &_to.cinema->seances[i];
		stream << seance->movieTitle << endl;
		stream << seance->dateTime.tm_mday << " " << seance->dateTime.tm_mon << " " << seance->dateTime.tm_year << endl;
		stream << Cinema::formatTime(seance->dateTime.tm_hour) << " " << Cinema::formatTime(seance->dateTime.tm_min) << endl;
		stream << seance->hallNumber << endl;
		for (int j = 0; j < seance->hall.rowsColumnsNumber; j++) {
			for (int k = 0; k < seance->hall.rowsColumnsNumber; k++) {
				stream << int(seance->hall.seats[j][k].isBooked);
			}
			stream << endl;
		}
	}
	return stream;
}

// Считывание информации о билетной кассе из потока
istream& operator>>(istream& stream, TicketOffice& _to) {
	if (_to.cinema != nullptr) {
		delete _to.cinema;
	}
	
	string oneRow, hallConfig;
	int hallsCount;
	stream >> hallsCount;
	Cinema::Hall * halls = new Cinema::Hall[hallsCount];
	for (int i = 0; i < hallsCount; i++)
	{
		int rowsColumns;
		stream >> rowsColumns;
		Cinema::TicketPrice tp;
		stream >> tp.defaultPrice >> tp.vipPrice;

		hallConfig = "";
		for (int j = 0; j < rowsColumns; j++) {
			stream >> oneRow;
			hallConfig += oneRow;
		}
		halls[i] = Cinema::Hall(hallConfig, tp);
	}

	int seancesCount;
	stream >> seancesCount;
	Cinema::Seance * seances = new Cinema::Seance[seancesCount];
	for (int i = 0; i < seancesCount; i++)
	{
		stream.get();
		char buffer[256];
		stream.getline(buffer, 256);
		string title(buffer);

		int day, month, year;
		stream >> day >> month >> year;
		int hours, minutes;
		stream >> hours >> minutes;
		int hallNumber;
		stream >> hallNumber;
		seances[i] = Cinema::Seance(_to.cinema, year-1900, month-1, day, hours, minutes, title, hallNumber, &halls[hallNumber]);

		hallConfig = "";
		int rowColNum = halls[hallNumber].rowsColumnsNumber;
		for (int j = 0; j < rowColNum; j++)
		{
			stream >> oneRow;
			hallConfig += oneRow;
		}
		for (int j = 0; j < hallConfig.length(); j++)
		{
			seances[i].hall.seats[j / rowColNum][j % rowColNum].isBooked = hallConfig[j] - '0';
		}
	}
	_to.cinema = new Cinema(hallsCount, halls, seancesCount, seances);

	return stream;
}

// Проверить, возможна ли покупка билетов в данный момент
// (меньше трех дней до сеанса, не больше 10 минут после начала)
bool TicketOffice::checkTime(tm _seanceTime) {
	// Получить текущее время
	tm now;
    time_t t = time(0);
    localtime_s(&now, &t);

	_seanceTime.tm_sec = 0;
	double diffSeconds;

	// Проверить прошло ли 10 мин. с начала сеанса
	diffSeconds = difftime(t, mktime(&_seanceTime));
	if (diffSeconds >= 10*60) {
		return false;
	}

	// Проверить больше ли трех дней до сеанса
	diffSeconds = difftime(mktime(&_seanceTime), t);
	if (diffSeconds > 3*24*60*60) {
		return false;
	}

	return true;
}

// Интерфейс покупки билетов
void TicketOffice::buyTickets(Cinema::Seance * _seance) {
	int defSeatsCount, vipSeatsCount, totalSeatsCount;
	cout << "Сколько требуется мест?" << endl;
	cout << "обычных: ";
	cin >> defSeatsCount;
	cout << "VIP-мест: ";
	cin >> vipSeatsCount;
	totalSeatsCount = defSeatsCount + vipSeatsCount;

	cout << "Стоимость: " << calcTotalCost(*_seance, defSeatsCount, vipSeatsCount) << endl;
	string buyOption = "";
	while (true) {
		cout << "Купить? (да/нет): ";
		cin >> buyOption;
		if (buyOption == "нет") {
			return;
		}
		else if (buyOption == "да") {
			try {
				Cinema::Seat * chosenSeats = new Cinema::Seat[totalSeatsCount];
				chosenSeats = processOrder(*_seance, defSeatsCount, vipSeatsCount);
				cout << "Места успешно забронированы!" << endl;

				TicketOffice::Ticket * tickets = new TicketOffice::Ticket[totalSeatsCount];
				tickets = createTickets(*_seance, chosenSeats, totalSeatsCount);
				ofstream ticketsOutput("tickets.txt");
				printTickets(ticketsOutput, tickets, totalSeatsCount);
				cout << "Билеты напечатаны в файл \"tickets.txt\"" << endl;
				cout << "Спасибо за покупку!" << endl;
				system("pause");
				return;
			}
			catch (const char err[]) {
				cout << "Ошибка: " << err << endl;
				system("pause");
				break;
			}
		}
		else {
			cout << "Так сделать нельзя" << endl;
		}
	}
}

// Интерфейс возврата билетов
void TicketOffice::returnTickets(Cinema::Seance * _seance) {
	int defSeatsCount, vipSeatsCount, totalSeatsCount;
	cout << "Сколько мест хотите вернуть?" << endl;
	cout << "обычных: ";
	cin >> defSeatsCount;
	cout << "VIP-мест: ";
	cin >> vipSeatsCount;
	totalSeatsCount = defSeatsCount + vipSeatsCount;

	cout << "Вам будет возвращено: " << calcTotalCost(*_seance, defSeatsCount, vipSeatsCount) << endl;
	string returnOption = "";
	while (true) {
		cout << "Вернуть билеты? (да/нет): ";
		cin >> returnOption;
		if (returnOption == "нет") {
			return;
		}
		else if (returnOption == "да") {
			try {
				int returnSeatRow, returnSeatColumn;
				cout << "Введите номера мест на билетах:" << endl;
				for (int i = 0; i < totalSeatsCount; i++)
				{
					cout << "Билет #" << (i+1) << ":" << endl;
					cout << "Ряд: ";
					cin >> returnSeatRow;
					cout << "Место: ";
					cin >> returnSeatColumn;
					cancelSeatReservation(*_seance, returnSeatRow, returnSeatColumn);
				}
				cout << "Билеты успешно возвращены!" << endl;

				system("pause");
				return;
			}
			catch (...) {
				cout << "Место не было куплено" << endl;
				system("pause");
				break;
			}
		}
		else {
			cout << "Так сделать нельзя" << endl;
		}
	}
}

// Интерфейс билетной кассы
void TicketOffice::runTicketOffice() {
	string input;
	while (true) {
		system("cls");
		cout << "---Касса кинотеатра---------------------" << endl;
		cout << "Сеансы: " << endl;
		Cinema::Seance * seance = NULL;
		for (int i = 0; i < cinema->seancesQuantity; i++)
		{
			seance = &cinema->seances[i];
			cout << "[" + to_string(i + 1) + "] \"" << seance->movieTitle << "\"";
			cout << " " << seance->dateTime.tm_mday << "." << (seance->dateTime.tm_mon + 1)
				<< "." << (seance->dateTime.tm_year + 1900);
			cout << " " << Cinema::formatTime(seance->dateTime.tm_hour) << ":"
				<< Cinema::formatTime(seance->dateTime.tm_min);
			cout << " " << "Зал:" << seance->hallNumber;
			cout << " " << "Цена:" << seance->ticketPrice.defaultPrice << "/" << seance->ticketPrice.vipPrice;
			cout << endl;
		}

		string option = "-1";
		while (stoi(option) < 1 || stoi(option) > cinema->seancesQuantity) {
			cout << "Выберите сеанс или введите \"выйти\": ";
			cin >> option;
			if (option == "выйти") return;
		}

		cout << "Хотите купить или вернуть билеты? (купить/вернуть): ";
		cin >> input;
		if (input == "купить") {
			buyTickets(&cinema->seances[stoi(option) - 1]);
		}
		else if (input == "вернуть") {
			returnTickets(&cinema->seances[stoi(option) - 1]);
		}
		else {
			cout << "Это сделать нельзя" << endl;
		}
	}
}