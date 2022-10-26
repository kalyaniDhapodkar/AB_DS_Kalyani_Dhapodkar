
//	Headers

#include	<stdio.h>
#include	<stdlib.h>
#include	<assert.h>

#include	"vector.h"

void print_data(data_t data)
{
	fprintf(stdout, "{%lld}-", (long long)data);
}

void delete_data(data_t data)
{
	fprintf(stdout, "Popped Data: %lld\n", (long long)data);
}

int main(void)
{
	// Code
	p_mv_vector_t pvector = create_vector();

	mv_vector_push_back(pvector, (size_t)4, (data_t)10, (data_t)20, (data_t)30, (data_t)40);
	mv_vector_push_back(pvector, (size_t)4, (data_t)100, (data_t)200, (data_t)300, (data_t)400);
	mv_vector_push_back(pvector, (size_t)4, (data_t)1000, (data_t)2000, (data_t)3000, (data_t)4000);

	forward_print_data(pvector);
	backward_print_data(pvector);
	printf("pvector size = %llu\n", mv_vector_size(pvector));
	printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector));

	mv_vector_pop_back(pvector, 2);

	print_data(pvector);
	printf("pvector size = %llu\n", mv_vector_size(pvector));
	printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector));

	mv_vector_pop_back(pvector, 4);

	forward_print_data(pvector);
	backward_print_data(pvector);

	printf("pvector size = %llu\n", mv_vector_size(pvector));
	printf("pvector Capacity = %llu\n", mv_vector_capacity(pvector));

	mv_vector_destroy(&pvector);

	exit(0);
}

