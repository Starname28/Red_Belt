#include "test_runner.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <queue>
#include <stdexcept>
#include <set>

using namespace std;

template <class T>
class ObjectPool {
public:
	T* Allocate();
	T* TryAllocate();

	void Deallocate(T* object);

	~ObjectPool();

private:
	queue<T*> free_pool;
	set<T*> busy_pool;
	// Добавьте сюда поля
};

void TestObjectPool() {
	ObjectPool<string> pool;

	auto p1 = pool.Allocate();
	auto p2 = pool.Allocate();
	auto p3 = pool.Allocate();

	*p1 = "first";
	*p2 = "second";
	*p3 = "third";

	pool.Deallocate(p2);
	ASSERT_EQUAL(*pool.Allocate(), "second");

	pool.Deallocate(p3);
	pool.Deallocate(p1);
	ASSERT_EQUAL(*pool.Allocate(), "third");
	ASSERT_EQUAL(*pool.Allocate(), "first");

	pool.Deallocate(p1);
}

int main() {
	TestRunner tr;
	RUN_TEST(tr, TestObjectPool);
	return 0;
}

template<class T>
T* ObjectPool<T>::Allocate()
{
	if (!free_pool.empty())
	{
		auto ptr = free_pool.front();
		busy_pool.insert(ptr);
		free_pool.pop();

		return ptr;
	}

	T* ptr = new T;
	busy_pool.insert(ptr);

	return ptr;
}

template<class T>
T* ObjectPool<T>::TryAllocate()
{
	if (!free_pool.empty())
	{
		auto ptr = free_pool.front();
		busy_pool.insert(ptr);
		free_pool.pop();

		return ptr;
	}

	return nullptr;
}

template<class T>
void ObjectPool<T>::Deallocate(T* object)
{
	auto it = busy_pool.find(object);

	if (it == busy_pool.end())
		throw invalid_argument("");

	free_pool.push(object);
	busy_pool.erase(object);
}

template<class T>
ObjectPool<T>::~ObjectPool()
{
	while (!free_pool.empty())
	{
		auto ptr = free_pool.front();
		delete ptr;
		free_pool.pop();
	}

	for (auto ptr : busy_pool)
		delete ptr;

	busy_pool.clear();
}
