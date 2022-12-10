

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mv_merge_sort.h"

ret_t  compare(data_t data1, data_t data2)
{
	return(data1 < data2);

	return(FALSE);
}

int main(void)
{
	// Code
	srand(time(0));

	long long no_of_elements = 100000;

	long long* array = (long long*)calloc(no_of_elements, sizeof(long long));

	for(long le = 0; le < no_of_elements; le++)
		array[le] = le + rand() % 20;

	// fprintf(stdout, "Array Before Sort: \n{Start} , ");
	// for(long long le = 0; le < no_of_elements; le++)
	// 	printf("{%lld}, ", (long long)array[le]);
	// fprintf(stdout, "{END}\n\n");

	clock_t start = clock();

	MergeSort((data_t*)array, no_of_elements, compare);

	clock_t end = clock();

	fprintf(stdout, "Time Required to Sort: %f\n", (double)(end - start)/CLOCKS_PER_SEC);

	// fprintf(stdout, "Array After Sort: \nStart, ");
	// for(long long le = 0; le < no_of_elements; le++)
	// 	printf("{%lld}, ", (long long)array[le]);
	// fprintf(stdout, "{END}\n\n");
	exit(0);
}
