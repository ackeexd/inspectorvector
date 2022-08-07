#include <iostream>
using namespace std;

template<typename T>
class Vector
{
	unsigned int size; // количество действительно присутствующих элементов в контейнере
	unsigned int capacity; // ёмкость (вместительность, запас памяти)
	T* data = nullptr; // указатель на динамический массив данных

public:
	Vector();
	Vector(unsigned int capacity);
	~Vector();

	Vector(const Vector& other);
	Vector(Vector&& other);

	bool operator==(const Vector& other);
	bool operator!=(const Vector& other);
    const T operator[](int index);
	Vector& operator=(const Vector& other);

private:
	void EnsureCapacity();

public:
	void PushBack(const T& value);
	void PushFront(const T& value);
	void Clear();
	bool IsEmpty() const;
	void Print() const;
	void pop_beck();
	void pop_front();
	void Insert(int index, const T& value);
	void Erase(int index);
	void remove_by_value(const T& value);
	void trim_to_size();
	int index_of(T& value);
	int last_index_of(T& value);
	void reverse();
	void shuffle();
	bool equals(const Vector* other);
};
	template<typename T>
	Vector<T>::Vector() 
	{
		capacity = 10;
		size = 0;
		data = new T[capacity];
	}

	template<typename T>
	Vector<T>::Vector(unsigned int capacity) 
	{
		if (capacity < 10) capacity = 10;
		this->capacity = capacity;
		size = 0;
		data = new T[capacity];
	}

	template<typename T>
	Vector<T>::~Vector() 
	{
		delete[] data;
		data = nullptr;
	}

	template<typename T>
	Vector<T>::Vector(const Vector& other)
	{
		capacity = other.capacity;
		size = other.size;
		delete[] data;
		data = new T[capacity];

		for (int i = 0; i < size; ++i)
			data[i] = other.data[i];
	}

	template<typename T>
	Vector<T>::Vector(Vector&& other)
	{
		capacity = other.capacity;
		size = other.size;
		data = other.data;
		other.data = nullptr;
	}

	template<typename T>
	void Vector<T>::EnsureCapacity()
	{
		if (size == capacity) // если все элементы массива заняты
		{
			capacity *= 2;
			T* temp = new T[capacity];
			for (unsigned int i = 0; i < size; i++)
				temp[i] = data[i];
			delete[] data;
			data = temp;
		}
	}

	template<typename T>
	void Vector<T>::PushBack(const T& value)
	{
		EnsureCapacity();
		data[size++] = value;
	}

	template<typename T>
	void Vector<T>::PushFront(const T& value)
	{
		EnsureCapacity();
		for (unsigned int i = size; i > 0; i--)
			data[i] = data[i - 1];
		data[0] = value;
		size++;
	}

	template<typename T>
	void Vector<T>::Clear()
	{
		size = 0;
	}

	template<typename T>
	bool Vector<T>::IsEmpty() const
	{
		return size == 0;
	}

	template<typename T>
	void Vector<T>::Print() const
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

	template<typename T>
	void Vector<T>::pop_beck()
	{
		size--;
	}

	template<typename T>
	void Vector<T>::pop_front()
	{
		Erase(0);
	}

	template<typename T>
	void Vector<T>::Insert(int index, const T& value)
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

	template<typename T>
	void Vector<T>::Erase(int index)
	{
		if (index < 0 || index >= size) throw "wrong index)";
		for (int i = 0; i < size; i++) {
			if (i <= index) continue;
			else data[i - 1] = data[i];
		}
		size--;
	}

	template<typename T>
	void Vector<T>::remove_by_value(const T& value)
	{
		for (int i = 0; i < size; i++)
			if (data[i] == value) Erase(i);
	}

	template<typename T>
	void Vector<T>::trim_to_size()
	{
		capacity = size;
		T* temp = new T[capacity];

		for (int i = 0; i < size; i++)
			temp[i] = data[i];

		delete[] data;
		data = temp;
		temp = nullptr;
	}

	template<typename T>
	int Vector<T>::index_of(T& value)
	{
		for (int i = 0; i < size; i++)
			if (data[i] == value) return i;
		return -1;
	}

	template<typename T>
	int Vector<T>::last_index_of(T& value)
	{
		for (int i = size - 1; i >= 0; i--)
			if (data[i] == value) return i;
		return -1;
	}

	template<typename T>
    void Vector<T>::reverse()
	{
		for (int i = 0; i < size / 2; i++)
			swap(data[i], data[size - 1 - i]);
	}

    template<typename T>
	void Vector<T>::shuffle()
	{
		srand(time(0));
		for (int i = 0; i < size; i++) {
			int a = rand() % size;
			int b = rand() % size;
			swap(data[a], data[b]);
		}
	}

	template<typename T>
    bool Vector<T>::equals(const Vector* other)
	{
		return *this == *other;
	}

	template<typename T>
	bool Vector<T>:: operator==(const Vector& other)
	{
		if (size != other.size) return false;
		for (int i = 0; i < size; i++)
			if (data[i] != other.data[i]) return false;
		return true;
	}

	template<typename T>
	bool Vector<T>:: operator!=(const Vector& other)
	{
		if (*this == other) return false;
		return true;
	}

	template<typename T>
	const T Vector<T>::operator[](int index)
	{
		if (index < 0 || index >= size) throw "wrong index)";
		else return data[index];
	}

	template<typename T>
	Vector<T>& Vector<T>::operator=(const Vector& other)
	{
		if (this == &other) return *this;
		capacity = other.capacity;
		size = other.size;
		delete[] data;
		data = new T[capacity];

		for (int i = 0; i < size; ++i)
			data[i] = other.data[i];

		return *this;
	}

int main()
{
	Vector<int> v;
	v.PushBack(37);
	v.PushBack(27);
	v.PushBack(177);
	v.PushFront(7);
	v.PushFront(17);
	v.PushFront(77);
	v.Print();
}
