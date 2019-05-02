#pragma once
#include "Cinema.h"
#include "TicketOffice.h"

class TicketOffice {
public:
	// Один билет
	struct Ticket {
		tm dateTime;
		string movieTitle;
		int hallNumber;
		int seatRowNumber, seatColumnNumber;
	};

	// Конструктор по умолчанию
	TicketOffice();

	// Конструктор кассы для уже существующего кинотеатра
	TicketOffice(Cinema * _cinema);

	// Конструктор копирования
	TicketOffice(const TicketOffice& _to);

	// Перегрузка оператора присваивания
	TicketOffice& operator=(const TicketOffice& _to);

	// Деструктор
	~TicketOffice();

	//--------------------------------------------------------------------------------------------------------------------------

	// Принять заказ билетов покупателем
	Cinema::Seat * processOrder(const Cinema::Seance& _seance, int _defaultSeatsQuantity, int _vipSeatsQuantity);
	
	// Проверить наличие свободных мест в обеих зонах
	bool checkSeatsAvailiable(const Cinema::Hall& _hall, int _defaultSeatsQuantity, int _vipSeatsQuantity);
	
	// Зарезервировать требуемое количество мест
	Cinema::Seat * reserveSeats(const Cinema::Hall& _hall, int _defaultSeatsQuantity, int _vipSeatsQuantity);

	// Рассчитать общую стоимость билетов
	double calcTotalCost(const Cinema::Seance& _seance, int _defaultSeatsQuantity, int _vipSeatsQuantity);

	// Отменить заказ билета
	void TicketOffice::cancelSeatReservation(const Cinema::Seance& _seance, int _seatRow, int _seatColumn);

	// Сформировать билеты
	Ticket * createTickets(const Cinema::Seance& _seance, Cinema::Seat * _seats, int _seatsCount);

	// Напечатать билеты в поток
	ostream& printTickets(ostream& stream, Ticket * _tickets, int _ticketsCount);

	//--------------------------------------------------------------------------------------------------------------------------

	// Вывод информации о билетной кассе в поток
	friend ostream& operator<<(ostream& stream, const TicketOffice& _to);

	// Считывание информации о билетной кассе из потока
	friend istream& operator>>(istream& stream, TicketOffice& _to);

	// Проверить, возможна ли покупка билетов в данный момент
	// (меньше трех дней до сеанса, не больше 10 минут после начала)
	static bool checkTime(tm _seanceTime);

	//--------------------------------------------------------------------------------------------------------------------------

	// Интерфейс покупки билетов
	void buyTickets(Cinema::Seance * _seance);

	// Интерфейс возврата билетов
	void returnTickets(Cinema::Seance * _seance);

	// Интерфейс билетной кассы
	void runTicketOffice();

	// Вся информация о кинотеатре
	Cinema * cinema;
};