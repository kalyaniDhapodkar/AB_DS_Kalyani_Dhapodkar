
//	Headers
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_queue.h"


p_mv_queue_t pqueue = NULL;

void print_data(data_t data)
{
	// Code
	long long lnum = (long long)data;

	fprintf(stdout, "{%lld}-", lnum);
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

	mv_queue_enqueue(pqueue, (data_t) 100);
	mv_queue_enqueue(pqueue, (data_t) 200);
	mv_queue_enqueue(pqueue, (data_t) 300);
	mv_queue_enqueue(pqueue, (data_t) 400);
	mv_queue_enqueue(pqueue, (data_t) 500);
	mv_queue_enqueue(pqueue, (data_t) 600);
	mv_queue_enqueue(pqueue, (data_t) 700);
	mv_queue_enqueue(pqueue, (data_t) 800);
	mv_queue_enqueue(pqueue, (data_t) 900);
	mv_queue_enqueue(pqueue, (data_t) 1000);

	mv_queue_print_data(pqueue, print_data);

	/*fprintf(stdout,"Dequeue kelela data:");
	print_data(mv_queue_dequeue(pqueue));
	fprintf(stdout,"\n");
	fprintf(stdout,"Dequeue kelela data:");
	print_data(mv_queue_dequeue(pqueue));
	fprintf(stdout,"\n");
	fprintf(stdout,"Dequeue kelela data:");
	print_data(mv_queue_dequeue(pqueue));
	fprintf(stdout,"\n");
	fprintf(stdout,"Dequeue kelela data:");
	print_data(mv_queue_dequeue(pqueue));
	fprintf(stdout,"\n");
	mv_queue_print_data(pqueue, print_data);
	*/
	mv_queue_destroy( &pqueue, delete_data);

	exit(SUCCESS);
}