#pragma once
#include <ctime>
#include <cmath>
#include <string>

using namespace std;

class Cinema {
public:
	// Цены на обычное и VIP-место
	struct TicketPrice {
		double defaultPrice, vipPrice;
	};

	// Одно место в зале
	struct Seat {
		int row, column;
		bool isVIP;
		bool isBooked; // занято или не занято
	};

	// Один зал
	struct Hall {
		// Создание пустого зала
		Hall();

		// Создание зала заданной конфигурации
		// Формат _hallConfiguration :
		// "dddd
		//  dvvd
		//  dvvd
		//  dddd"
		// d - обычное место, v - VIP место, переносов строки нет
		Hall(string _hallConfiguration, TicketPrice _ticketPrice);

		// Перегрузка оператора присваивания
		// (для создания копии зала для каждого сеанса)
		Hall& operator=(const Hall& _h);

		// Деструктор
		~Hall();

		int rowsColumnsNumber;
		Seat ** seats;
		TicketPrice basePrice;
	};

	// Один сеанс
	struct Seance {
		// Создание сеанса (по умолчанию)
		Seance() {}

		// Создание сеанса с заданными параметрами
		Seance(Cinema * _cinema, int _year, int _month, int _day, int _hours, int _minutes, string _title, int _hallNumber, Hall * _hall);

		tm dateTime;
		string movieTitle;
		int hallNumber;
		Hall hall;
		TicketPrice ticketPrice;
	};

	// Конструктор по умолчанию (пустой кинотеатр)
	Cinema();

	// Создать кинотеатр
	Cinema(int _hallsQuantity, Hall * _halls, int _seancesQuantity, Seance * _seances);

	// Перегрузка оператора присваивания
	Cinema& operator=(const Cinema& _c);

	// Деструктор
	~Cinema();

	// Вычислить цену билета на заданный сеанс
	static TicketPrice calcPrice(TicketPrice _basePrice, tm _seanceTime);

	// Преобразовать время в читаемый формат "4" -> "04"
	static string formatTime(int time);

	// Количество залов в кинотеатре и количество доступных сеансов
	int hallsQuantity, seancesQuantity;

	// Данные о залах и сеансах
	Hall * halls;
	Seance * seances;
};