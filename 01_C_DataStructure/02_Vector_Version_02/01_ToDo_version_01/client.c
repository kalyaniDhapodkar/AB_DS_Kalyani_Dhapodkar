

//	Headers

#include	<stdio.h>
#include	<stdlib.h>
#include	<assert.h>

#include	"header.h"

p_mv_vector_t	pvector_1 =  NULL;
p_mv_vector_t	pvector_2 =  NULL;

void print_data(p_mv_vector_t pvector)
{
	//	Code
	fprintf(stdout, "\n{START}-");
	for( long le = 0; le < mv_vector_size(pvector); ++le)
	{
		fprintf(stdout, "{%lld}-", (long long)mv_vector_data_at(pvector, le));
	}
	fprintf(stdout,"{END}\n");
}

int main(void)
{
	// Code
	pvector_1 = create_vector();
	pvector_2 = create_vector();

	mv_vector_push_back(pvector_1, (data_t)10);
	mv_vector_push_back(pvector_1, (data_t)20);
	mv_vector_push_back(pvector_1, (data_t)30);
	mv_vector_push_back(pvector_1, (data_t)40);

	printf("Pvector_1: \n");
	print_data(pvector_1);
	printf("pvector size = %llu\n", mv_vector_size(pvector_1));
	printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector_1));
	
	printf("Pvector_2: \n");
	print_data(pvector_2);
	printf("pvector size = %llu\n", mv_vector_size(pvector_2));
	printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector_2));

	mv_vector_push_back(pvector_2, (data_t)50);
	mv_vector_push_back(pvector_2, (data_t)60);
	mv_vector_push_back(pvector_2, (data_t)70);
	mv_vector_push_back(pvector_2, (data_t)80);
	mv_vector_push_back(pvector_2, (data_t)90);
	mv_vector_push_back(pvector_2, (data_t)100);

	printf("\nMerge pvector_2 in pvector_1: \n");

	printf("\nPvector_1 (Before Merge) : \n");
	print_data(pvector_1);
	printf("pvector size = %llu\n", mv_vector_size(pvector_1));
	printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector_1));

	printf("\n Pvector_2 (Before Merge) : \n");
	print_data(pvector_2);
	printf("pvector size = %llu\n", mv_vector_size(pvector_2));
	printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector_2));

	mv_vector_merge(pvector_1, pvector_2);

	printf("\nPvector_1 (After Merge) : \n");
	print_data(pvector_1);
	printf("pvector size = %llu\n", mv_vector_size(pvector_1));
	printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector_1));

	printf("\nPvector_2 (After Merge) : \n");
	print_data(pvector_2);
	printf("pvector size = %llu\n", mv_vector_size(pvector_2));
	printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector_2));

	printf("\nMerge pvector_1 in pvector_2: \n\n");

	mv_vector_merge(pvector_2, pvector_1);

	printf("\nPvector_1 (After Merge) : \n");
	print_data(pvector_1);
	printf("pvector size = %llu\n", mv_vector_size(pvector_1));
	printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector_1));

	printf("\nPvector_2 (After Merge) : \n");
	print_data(pvector_2);
	printf("pvector size = %llu\n", mv_vector_size(pvector_2));
	printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector_2));

	mv_vector_pop_back(pvector_1);
	mv_vector_pop_back(pvector_1);
	mv_vector_pop_back(pvector_1);
	
	printf("\nPvector_1: \n");
	print_data(pvector_1);
	printf("pvector size = %llu\n", mv_vector_size(pvector_1));
	printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector_1));

	mv_vector_destroy(&pvector_1);
	mv_vector_destroy(&pvector_2);

	exit(0);
}

