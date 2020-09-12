#pragma once
#include <map>
#include <vector>
#include <sstream>
#include <iostream>

struct Container
{
	Container(size_t vector_size) :
		vector_container(vector_size)
	{
	}

	std::vector<int> vector_container;
	std::map<int, int> map_container;
};

std::ostream& operator<<(std::ostream& os, const Container& container)
{
	os << "Vector elements: ";
	for (const auto& el : container.vector_container)
		os << el << ' ';

	os << '\n';

	os << "   Map elements: ";
	for (const auto& [key, value] : container.map_container)
		os << value << ' ';
	
	os << '\n';

	return os;
}
