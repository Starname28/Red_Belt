#pragma once

#include <cstdlib>

// � еализуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
	SimpleVector();
	explicit SimpleVector(size_t size);
	~SimpleVector();

	T& operator[](size_t index);
	const T& operator[](size_t index) const;

	T* begin();
	T* end();

	const T* begin() const;
	const T* end() const;


	size_t Size() const;
	size_t Capacity() const;
	void PushBack(const T& value);

private:
	size_t size, capacity;
	T* ptr;

	// Добавьте поля для хранения данных вектора
};

template<typename T>
inline SimpleVector<T>::SimpleVector()
	: size(0), capacity(0), ptr(nullptr)
{
}

template<typename T>
inline SimpleVector<T>::SimpleVector(size_t size)
	: size(size), capacity(size), ptr(new T[size])
{
}

template<typename T>
inline SimpleVector<T>::~SimpleVector()
{
	if (!(end() - begin()))
		delete[] ptr;
	size = 0;
	capacity = 0;
}

template<typename T>
inline T& SimpleVector<T>::operator[](size_t index)
{
	return ptr[index];
}

template<typename T>
inline const T& SimpleVector<T>::operator[](size_t index) const
{
	return ptr[index];
}

template<typename T>
inline T* SimpleVector<T>::begin()
{
	return ptr;
}

template<typename T>
inline T* SimpleVector<T>::end()
{
	return ptr + Size();
}

template<typename T>
inline const T* SimpleVector<T>::begin() const
{
	return ptr;
}

template<typename T>
inline const T* SimpleVector<T>::end() const
{
	return ptr + Size();
}

template<typename T>
inline size_t SimpleVector<T>::Size() const
{
	return size;
}

template<typename T>
inline size_t SimpleVector<T>::Capacity() const
{
	return capacity;
}

template<typename T>
inline void SimpleVector<T>::PushBack(const T& value)
{
	if (!ptr)
	{
		ptr = new T[1];
		size = 1;
		capacity = 1;
		ptr = value;
	}

	if (Size() == Capacity())
	{
		T* tmp = new T[Size() + 1];

		for (size_t i = 0 i < Size(); i++)
			tmp[i] = ptr[i];

		tmp[Size()] = value;

		delete[] ptr;

		capacity *= 2;
		++size;

		ptr = new T[Capacity()];

		for (size_t i = 0; i < Size(); i++)
			ptr[i] = tmp[i];

		delete[] tmp;
	}
	else
	{
		ptr[Size()] = value;
		++size;
	}
}
