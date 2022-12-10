

// Header Files
#include <stdio.h>
#include <stdlib.h>

#include "mv_merge_sort.h"


// Helper/Auxillary Functions
static void* xcalloc(long long no_of_elements, size_t size)
{
	// Code
	void* p = calloc(no_of_elements, size);
	if(p == NULL)
	{
		fprintf(stderr, "ERROR: Out of Memory.\n");
		return(NULL);
	}

	return(p);
}


static void Merge(data_t* array, long long first, long long mid, long long last, COMPARE pcompare)
{
	long long left_size = mid - first + 1;

	long long right_size = last - (mid+1) + 1;

	data_t* left = (data_t*)xcalloc(left_size, sizeof(data_t));

	data_t* right = (data_t*)xcalloc(right_size, sizeof(data_t));

	for(long long le = 0; le < left_size; le++)
		left[le] = array[first + le];


	for(long long le = 0; le < right_size; le++)
		right[le] = array[mid + 1 + le];

	long long left_index = 0; 
	long long right_index = 0;
	long long array_index = first;

	// Merge two sub arrays
	while( left_index != left_size && right_index != right_size)
	{
		if( pcompare(left[left_index], right[right_index]) )
		{
			array[array_index] = left[left_index];
			left_index++;
		}
		else
		{
			array[array_index] = right[right_index];
			right_index++;
		}
		array_index++;
	}

	// Case 1: when left array is completed but not right
	while( left_index == left_size &&
			right_index != right_size)
	{
		array[array_index] = right[right_index];
		right_index++;
		array_index++;
	}

	// Case 2: When right array is complated but not left
	while( left_index != left_size &&
			right_index == right_size)
	{
		array[array_index] = left[left_index];
		left_index++;
		array_index++;
	}

	if(left)
	{
		free(left);
		left = NULL;
	}

	if(right)
	{
		free(right);
		right = NULL;
	}

}

static void Partition(data_t* array, long first, long last, COMPARE pcompare)
{
	// Code
	if(first < last)
	{
		long long mid = (last - first) / 2 + first;

		Partition(array, first, mid, pcompare);
		Partition(array, mid+1, last, pcompare);
		Merge(array, first, mid, last, pcompare);

	}
}

// User Interface Functions
extern 	void MergeSort(data_t* array, long long size, COMPARE pcompare)
{
	// Code
	Partition(array, 0, size-1, pcompare);

}

