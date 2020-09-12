// Task_for_TrueConf.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "VectorAndMap.h"
#include "Container.h"

#include <ctime>

using namespace VectorAndMap;

void Generation(Container& con, size_t SIZE)
{
	std::cout << "Generation containers:" << std::endl;

	GenerateConteinerElements(con.vector_container, SIZE);
	GenerateConteinerElements(con.map_container, SIZE);
	std::cout << con;
}

void DeleteElements(Container& con)
{
	std::cout << "Delete elements containers:" << std::endl;

	DeleteConteinerElements(con.map_container, con.vector_container);
	std::cout << con;
}

void Synchronize(Container& con)
{
	std::cout << "Synchronize containers:" << std::endl;

	SynchronizeConteiners(con.map_container, con.vector_container);
	std::cout << con;

}

int main()
{
   srand(time(NULL));

   std::cout << "Enter size for vector and map: ";
   size_t SIZE;
   std::cin >> SIZE;

   Container con(SIZE);

   Generation(con, SIZE);

   DeleteElements(con);

   Synchronize(con);

   system("pause");
   return 0;
}
