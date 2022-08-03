#include <iostream>
using namespace std;

class Vector
{
	unsigned int size = 0; // количество действительно присутствующих элементов в контейнере
	unsigned int capacity = 10; // ёмкость (вместительность, запас памяти)
	int* data = nullptr; // указатель на динамический массив данных

public:
	Vector() : Vector(10)
	{
		// cout << "C-TOR WITHOUT PARAMS!\n";
	}

	Vector(unsigned int capacity)
	{
		if (capacity < 10)
		{
			capacity = 10;
		}
		this->capacity = capacity;
		data = new int[capacity];
		// cout << "C-TOR WITH PARAMS!\n";
	}

	~Vector()
	{
		// cout << "DESTRUCTOR!\n";
		if (data != nullptr)
		{
			delete[] data;
			data = nullptr;
		}
	}

private:
	void EnsureCapacity()
	{
		if (size == capacity) // если все элементы массива заняты
		{
			capacity *= 2;
			int* temp = new int[capacity];
			for (unsigned int i = 0; i < size; i++)
				temp[i] = data[i];
			delete[] data;
			data = temp;
		}
	}

public:
	void PushBack(int value)
	{
		EnsureCapacity();
		data[size++] = value;
	}

	void PushFront(int value)
	{
		EnsureCapacity();
		for (unsigned int i = size; i > 0; i--)
			data[i] = data[i - 1];
		data[0] = value;
		size++;
	}

	void Clear()
	{
		size = 0;
	}

	bool IsEmpty() const
	{
		return size == 0;
	}

	void Print() const
	{
		if (IsEmpty())
		{
			cout << "Vector is empty.\n";
			return;
		}

		for (unsigned int i = 0; i < size; i++)
			cout << data[i] << " ";
		cout << "\n";
	}
	void pop_beck()
	{
		size--;
	}
    void pop_front()
	{
		Erase(0);
	}
	void Insert(int index, int value)
	{
		if (index < 0 || index >= size) throw "wrong index)";
		EnsureCapacity();

		for (int i = size; i >= 0; i--) {
			if (i > index) data[i] = data[i - 1];
			else if (i == index) data[i] = value;
			else break;
		}
		size++;
	}
	void Erase(int index)
	{
		if (index < 0 || index >= size) throw "wrong index)";
		for (int i = 0; i < size; i++) {
			if (i <= index) continue;
			else data[i - 1] = data[i];
		}
		size--;
	}
	void remove_by_value(int value)
	{
		for (int i = 0; i < size; i++)
			if (data[i] == value) Erase(i);
	}
	void trim_to_size()
	{
		capacity = size;
		int* temp = new int[capacity];

		for (int i = 0; i < size; i++)
			temp[i] = data[i];

		delete[] data;
		data = temp;
		temp = nullptr;
	}
	int index_of(int value)
	{
		for (int i = 0; i < size; i++)
			if (data[i] == value) return i;
		return -1;
	}
    int last_index_of(int value)
	{
		for (int i = size - 1; i >= 0; i--)
			if (data[i] == value) return i;
		return -1;
	}
    void reverse()
	{
		for (int i = 0; i < size / 2; i++)
			swap(data[i], data[size - 1 - i]);
	}
	void shuffle()
	{
		srand(time(0));
		for (int i = 0; i < size; i++) {
			int a = rand() % size;
			int b = rand() % size;
			swap(data[a], data[b]);
		}
	}
    bool equals(const Vector* other)
	{
		return *this == *other;
	}
	bool operator==(const Vector& other)
	{
		if (size != other.size) return false;
		for (int i = 0; i < size; i++)
			if (data[i] != other.data[i]) return false;
		return true;
	}
    bool operator!=(const Vector& other)
	{
		if (*this == other) return false;
		return true;
	}
    Vector operator[](int index)
	{
		if (index < 0 || index >= size) throw "wrong index)";
		else return data[index];
	}
    Vector operator=(const Vector& other)
	{
		if (this == &other) return *this;
		capacity = other.capacity;
		size = other.size;
		delete[] data;
		data = new int[capacity];
        for (int i = 0; i < size; ++i)
			data[i] = other.data[i];
        return *this;
	}
};
int main()
{
	Vector v;
	for (int i = 0; i < 1000; i++) v.PushBack(rand() % 100);
	v.Print();
}