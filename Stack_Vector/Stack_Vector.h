#pragma once

#include <stdexcept>
#include <exception>
#include <array>

using namespace std;

template <typename T, size_t N>
class StackVector {
public:
	explicit StackVector(size_t a_size = 0)
	: m_size(a_size)
	{
		if (m_size > N)
			throw invalid_argument("");
	}

	T& operator[](size_t index)
	{
		return arr[index];
	}
	const T& operator[](size_t index) const
	{
		return arr[index];
	}

	auto begin()
	{
		return arr.begin();
	}

	auto end()
	{
		return arr.begin() + Size();

	}
	const auto begin() const
	{
		return arr.begin();
	}
	
	const auto end() const
	{
		return arr.begin() + Size();
	}

	size_t Size() const;
	size_t Capacity() const;

	void PushBack(const T& value)
	{
		if (Size() == Capacity())
		{
			throw overflow_error("");
		}

		arr[m_size] = value;
		++m_size;
	}

	T PopBack()
	{
		if (Size() == 0)
			throw underflow_error("");

	//	arr[Size() - 1] = 0;
		--m_size;

		return arr[m_size];
	}

private:
	size_t m_size;
	array<T, N> arr;
};


template<typename T, size_t N>
size_t StackVector<T, N>::Size() const
{
	return m_size;
}

template<typename T, size_t N>
size_t StackVector<T, N>::Capacity() const
{
	return N;
}