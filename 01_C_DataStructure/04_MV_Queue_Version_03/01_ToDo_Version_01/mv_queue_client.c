

//	Headers
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_queue_header.h"


p_mv_queue_t pqueue = NULL;

void print_data(data_t data)
{
	// Code
	long long lnum = (long long)data;

	fprintf(stdout, "{%lld}", lnum);
}

void delete_data(data_t data)
{
	// Code
	long long lnum = (long long)data;

	fprintf(stdout, "deleting : %lld\n", lnum);
}

int main(void)
{
	// Code
	pqueue = create_default_queue();

	mv_queue_enqueue(pqueue, (data_t) 1000);
	mv_queue_enqueue(pqueue, (data_t) 2000);
	mv_queue_enqueue(pqueue, (data_t) 3000);
	mv_queue_enqueue(pqueue, (data_t) 4000);
	mv_queue_enqueue(pqueue, (data_t) 5000);
	mv_queue_enqueue(pqueue, (data_t) 6000);
	mv_queue_enqueue(pqueue, (data_t) 7000);
	mv_queue_enqueue(pqueue, (data_t) 8000);
	mv_queue_enqueue(pqueue, (data_t) 9000);
	mv_queue_enqueue(pqueue, (data_t) 10000);

	printf("%lld\n", (long long)pqueue->pvector->nr_of_elements);

	mv_queue_print_data(pqueue, print_data);

	printf("\n\n");
	fprintf(stdout,"Dequeued data:");
	print_data(mv_queue_dequeue(pqueue));
	fprintf(stdout,"\n");

	fprintf(stdout,"Dequeued data:");
	print_data(mv_queue_dequeue(pqueue));
	fprintf(stdout,"\n");

	fprintf(stdout,"Dequeued data:");
	print_data(mv_queue_dequeue(pqueue));
	fprintf(stdout,"\n");

	fprintf(stdout,"Dequeued data:");
	print_data(mv_queue_dequeue(pqueue));
	fprintf(stdout,"\n");

	mv_queue_print_data(pqueue, print_data);

	mv_queue_destroy( &pqueue, delete_data);


	exit(SUCCESS);
}

