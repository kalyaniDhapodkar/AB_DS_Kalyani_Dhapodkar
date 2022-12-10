

#include <iostream>
#include <ctime>

#include "mv_dcll.hpp"
#include "mv_insertion_sort.hpp"

MV_DCLL<long>* list = NULL;

int main(void)
{
	list = new MV_DCLL<long>();

	srand(time(0));

	long no_of_elements = 1 + rand() % 50;

	for(long le = 0; le < no_of_elements; le++)
	{
		list->InsertBack( 1 + rand() % LONG_MAX );
	}

	std::cout << "List Before Insertion Sort: " << std::endl;
	std::cout << list << std::endl;

	InsertionSort(list->begin(), list->end());

	std::cout << "List After Insertion Sort: " << std::endl;
	std::cout << list << std::endl;

	InsertionSort(list->begin(), list->end(), [](long a, long b) { return( a > b); } );

	std::cout << "List After Insertion Sort in Descending: " << std::endl;
	std::cout << list << std::endl;

	return(SUCCESS);
}

