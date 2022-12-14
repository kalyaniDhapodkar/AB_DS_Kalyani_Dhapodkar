

#include	<iostream>
#include	<ctime>

#include	"mv_merge_sort.hpp"
#include	"mv_array.hpp"
#include	"mv_dcll.hpp"

long long no_of_elements = 10;
MVArray<long long, 10> array;

int main(void)
{
	//Code

	srand(time(0));


	for( long long le = 0; le < no_of_elements; ++le )
	{
		array[le] = 1 + rand() % LONG_MAX;
	}

	std::cout << "Before Merge Sorting:" << std::endl;
	for( long long le = 0; le < no_of_elements; ++le )
		std::cout << array[le] << ", ";
	std::cout << std::endl << std::endl;

	MergeSort(array, array.Size(), [](long long a, long long b){
		return( a < b );
	});

	std::cout << "After Merge Sorting:" << std::endl;
	for( long long le = 0; le < no_of_elements; ++le )
		std::cout << array[le] << ", ";
	std::cout << std::endl << std::endl;

	return(0);
}

