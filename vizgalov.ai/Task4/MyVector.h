#pragma once

// Моя собственная реализация класса "вектор"
template <typename T>
class MyVector {
public:
	// Конструктор по умолчанию
	MyVector() {
		size = realSize = 0;
		items = NULL;
	}

	// Деструктор
	~MyVector() {
		size = realSize = 0;
		delete[] items;
	}

	// Добавление объекта в конец вектора
	void pushBack(T _item) {
		// Если заполнена вся доступная длина, то удвоим ее
		if (realSize == size) {
			int newSize = (size == 0) ? 1 : size * 2;
			T * newItems = new T[newSize];
			for (int i = 0; i < size; i++)
				newItems[i] = items[i];
			delete[] items;
			items = newItems;
			realSize = newSize;
		}
		items[size] = _item;
		size++;
	}

	// Удаление элемента вектора по индексу
	void erase(int _i) {
		size--;
		for (int i = _i; i < size; i++)
			items[i] = items[i + 1];	
	}

	// Полная очистка вектора
	void clear() {
		size = realSize = 0;
		delete[] items;
		items = NULL;
	}

	// Получить длину вектора (без учета памяти выделенной "про запас")
	int getSize() const { return size; }

	// Оператор индексации
	T& operator[](int _i) { return items[_i]; }
	T& operator[](int _i) const { return items[_i]; }

	// Оператор присваивания
	MyVector& operator=(const MyVector& _v) {
		clear();
		for (int i = 0; i < _v.getSize(); i++)
			pushBack(_v[i]);
		return *this;
	}

private:
	// size - длина вектора
	// realSize - длина вектора с учетом памяти выделенной "про запас"
	int size, realSize;

	// Элементы вектора
	T * items;
};