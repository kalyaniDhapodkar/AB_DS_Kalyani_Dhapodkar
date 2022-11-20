
// Headers
#include <stdio.h>
#include <stdlib.h>

#include "mv_queue_header.h"
#include "mv_vector_header.h"


#define 	DEFAULT_QUEUE_SIZE 		10

//	Function Declaration

static ret_t error_checking(const int assert_condition,
							const char *assert_condition_str,
							const char *file_name,
							const long line_no,
							const int error_condition,
							const char *error_str,
							void *(*perror_handler)(void *),
							void *error_handler_params);


#define ERROR_CHECKING(assert_condition, error_condition, error_str, error_handler, error_handler_params) ( \
	error_checking(assert_condition,                                                                        \
				   #assert_condition,                                                                       \
				   __FILE__,                                                                                \
				   __LINE__,                                                                                \
				   error_condition,                                                                         \
				   error_str,                                                                               \
				   error_handler,                                                                           \
				   error_handler_params))


static ret_t error_checking(const int assert_condition,
							const char *assert_condition_str,
							const char *file_name,
							const long line_no,
							const int error_condition,
							const char *error_str,
							void *(*perror_handler)(void *),
							void *error_handler_params)
{
	//	Code
	ret_t status = SUCCESS;

#ifdef MV_DEBUG
	// Assertion
	if (!assert_condition)
	{
		fprintf(stderr,
				"Assertion Failed: %s, File %s, Line %ld.\n",
				assert_condition_str,
				file_name,
				line_no);
		status = FAILURE;
	}
#else
	// Error Checking
	if (error_condition)
	{
		fprintf(stderr, error_str);
		status = FAILURE;
	}
#endif

	if (FAILURE == status)
	{
		if (NULL != perror_handler)
		{
			perror_handler(error_handler_params);
		}
	}

	return (status);
}


//	Queue Auxillary Functions
static void *Xmalloc(size_t nr_of_bytes)
{
	// Code
	void *p = malloc(nr_of_bytes);

	ret_t status = ERROR_CHECKING(1,
								  NULL == p,
								  "ERROR: Out of memory.\n",
								  NULL,
								  NULL);

	return (p);
}

static void *Xcalloc(size_t nr_of_elements, size_t size_of_element)
{
	// Code
	void *p = calloc(nr_of_elements, size_of_element);

	ret_t status = ERROR_CHECKING(1,
								  NULL == p,
								  "ERROR: Out Of Memory",
								  NULL,
								  NULL);

	return (p);
}


static void *Xrealloc(void* p, size_t nr_of_bytes)
{
	// Code
	void* rp = realloc(p, nr_of_bytes);
	
	ERROR_CHECKING( 1, 
					NULL == p, 
					"ERROR: Out Of Memory.\n" , 
					NULL, 
					NULL);
	
	return(rp);
}

void *deallocate_pqueue(void *param)
{
	//	Code
	pp_mv_queue_t ppqueue = (pp_mv_queue_t)param;
	p_mv_queue_t pqueue = *ppqueue;

	if (pqueue)
	{
		free(pqueue);
		pqueue = NULL;
	}

	*ppqueue = NULL;

	exit(FAILURE);

	return (NULL);
}

extern	p_mv_queue_t 	mv_create_default_queue(void)
{
	// Code
	p_mv_queue_t pqueue = (p_mv_queue_t)Xmalloc(SIZE_QUEUE);

	ret_t status = ERROR_CHECKING( NULL != pqueue,
									0,
									NULL,
									NULL,
									NULL);

	if(FAILURE == status)
		return(NULL);

	pqueue->head = 0;
	pqueue->tail = 0;

	pqueue->pvector = mv_create_default_vector(DEFAULT_QUEUE_SIZE);

	return(pqueue);
}

extern	p_mv_queue_t	mv_create_custom_queue(size_t no_of_elements)
{
	// Code
	p_mv_queue_t pqueue = (p_mv_queue_t)Xmalloc(SIZE_QUEUE);

	ret_t status = ERROR_CHECKING( NULL != pqueue,
									0,
									NULL,
									NULL,
									NULL);

	if(FAILURE == status)
		return(NULL);

	pqueue->head = 0;
	pqueue->tail = 0;

	pqueue->pvector = mv_create_custom_vector(no_of_elements);

	return(pqueue);

}

extern	ret_t 	mv_queue_enqueue(p_mv_queue_t pqueue, data_t data)
{
	// Code
	ret_t status = SUCCESS;
	status = ERROR_CHECKING( NULL != pqueue || NULL != pqueue->pvector,
					NULL == pqueue || NULL == pqueue->pvector,
					"ERROR: Queue Not Found.", 
					NULL,
					NULL);

	if( FAILURE == status)
		return(status);

	return(mv_vector_push_back(pqueue->pvector, data));
}

extern	data_t 	mv_queue_dequeue(p_mv_queue_t pqueue)
{
	// Code
	ret_t status = SUCCESS;
	status = ERROR_CHECKING( NULL != pqueue || NULL != pqueue->pvector,
					NULL == pqueue || NULL == pqueue->pvector,
					"ERROR: Queue Not Found.", 
					NULL,
					NULL);

	if (FAILURE == status)
		return (NULL);

	data_t to_return_data = (data_t)(long long)mv_vector_pop_front(pqueue->pvector);

	pqueue->tail--;

	return(to_return_data);
}

extern	ret_t 	mv_queue_print_data(p_mv_queue_t pqueue, PRINTDATAPROC pprintfunc )
{
	// Code
	ret_t status = SUCCESS;
	status = ERROR_CHECKING( NULL != pqueue || NULL != pqueue->pvector,
					NULL == pqueue || NULL == pqueue->pvector,
					"ERROR: Queue Not Found.", 
					NULL,
					NULL);

	if (FAILURE == status)
		return (FAILURE);

	mv_vector_print_data(pqueue->pvector, pprintfunc);

	return(SUCCESS);
}

extern	size_t 	mv_queue_length(p_mv_queue_t pqueue)
{
	// Code
	ret_t status = SUCCESS;
	status = ERROR_CHECKING( NULL != pqueue || NULL != pqueue->pvector,
					NULL == pqueue || NULL == pqueue->pvector,
					"ERROR: Queue Not Found.", 
					NULL,
					NULL);

	if (FAILURE == status)
		return (FAILURE);


	return(mv_vector_size(pqueue->pvector));
}

extern	ret_t	mv_queue_destroy( pp_mv_queue_t ppqueue, DELETEDATAPROC pdeletefunc )
{
	ret_t status = SUCCESS;
	status = ERROR_CHECKING( NULL != ppqueue,
					NULL == ppqueue,
					"ERROR: Queue Not Found.",
					NULL,
					NULL);

	if (FAILURE == status)
		return (FAILURE);


	status = ERROR_CHECKING( NULL != pdeletefunc,
					NULL == pdeletefunc,
					"ERROR: Delete Function Not Found.",
					NULL,
					NULL);

	if (FAILURE == status)
		return (FAILURE);

	p_mv_queue_t pqueue = *ppqueue;

	fprintf(stdout, "\nDestroying Queue: \n");
	fprintf(stdout, "\n{START}\n");
	for(size_t le = 0; le < pqueue->pvector->nr_of_elements; le++)
	{
		pdeletefunc(pqueue->pvector->array[le]);
	}
	fprintf(stdout, "{END}\n");

	mv_vector_destroy((pp_mv_vector_t)pqueue);

	if(pqueue)
	{
		free(pqueue);
		pqueue = NULL;
	}

	ppqueue = NULL;

	return(SUCCESS);
}


