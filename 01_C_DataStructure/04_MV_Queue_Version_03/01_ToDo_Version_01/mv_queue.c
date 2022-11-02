
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

extern	p_mv_queue_t 	create_default_queue(void)
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

	pqueue->pvector = create_vector();

	pqueue->pvector->nr_of_elements = 0;
	pqueue->pvector->capacity = DEFAULT_QUEUE_SIZE;

	pqueue->pvector->array = (p_data_t)Xcalloc(DEFAULT_QUEUE_SIZE, SIZE_DATA);

	status = ERROR_CHECKING(NULL != pqueue->pvector->array,
							0,
							NULL,
							NULL,
							NULL);

	return(pqueue);
}

extern	p_mv_queue_t	create_custom_queue(size_t no_of_elements)
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

	pqueue->pvector = create_vector();

	pqueue->pvector->nr_of_elements = 0;
	pqueue->pvector->capacity = no_of_elements;
	pqueue->pvector->array = (p_data_t)Xcalloc(no_of_elements, SIZE_DATA);

	status = ERROR_CHECKING(NULL != pqueue->pvector->array,
							0,
							NULL,
							NULL,
							NULL);

	return(pqueue);

}

extern	ret_t 	mv_queue_enqueue(p_mv_queue_t pqueue, data_t data)
{
	// Code
	ret_t status = SUCCESS;
	status = ERROR_CHECKING( NULL != pqueue || NULL != pqueue->pvector || NULL != pqueue->pvector->array,
					NULL == pqueue || NULL == pqueue->pvector || NULL == pqueue->pvector->array,
					"ERROR: Queue Not Found.", 
					NULL,
					NULL);

	if( FAILURE == status)
		return(status);

	pqueue->pvector->array[pqueue->tail] = data;
	pqueue->tail++;

	if(pqueue->tail == pqueue->pvector->capacity)
	{
		pqueue->pvector->capacity = pqueue->pvector->capacity * 2;
		pqueue->pvector->array = (p_data_t)Xrealloc(pqueue->pvector->array, pqueue->pvector->capacity * SIZE_DATA);
	}

	pqueue->pvector->nr_of_elements++;

	return(SUCCESS);
}

extern	data_t 	mv_queue_dequeue(p_mv_queue_t pqueue)
{
	// Code
	ret_t status = SUCCESS;
	status = ERROR_CHECKING( NULL != pqueue || NULL != pqueue->pvector || NULL != pqueue->pvector->array,
					NULL == pqueue || NULL == pqueue->pvector || NULL == pqueue->pvector->array,
					"ERROR: Queue Not Found.", 
					NULL,
					NULL);

	if (FAILURE == status)
		return (NULL);

	status = ERROR_CHECKING( pqueue->pvector->nr_of_elements != 0,
					pqueue->pvector->nr_of_elements == 0,
					"ERROR: No Data To Pop.", 
					NULL,
					NULL);

	if (FAILURE == status)
		return (NULL);


	data_t to_return_data = pqueue->pvector->array[0];

	for(size_t le = 0; le < pqueue->pvector->nr_of_elements-1; le++)
	{
		pqueue->pvector->array[le] = pqueue->pvector->array[le+1];
	}

	pqueue->pvector->nr_of_elements--;

	if(pqueue->pvector->nr_of_elements < pqueue->pvector->capacity/2)
	{
		pqueue->pvector->capacity = pqueue->pvector->capacity / 2;
		pqueue->pvector->array = (p_data_t)Xrealloc(pqueue->pvector->array, pqueue->pvector->capacity * SIZE_DATA);
	}

	pqueue->tail--;

	return(to_return_data);
}

extern	ret_t 	mv_queue_print_data(p_mv_queue_t pqueue, PRINTDATAPROC pprintfunc )
{
	// Code
	ret_t status = SUCCESS;
	status = ERROR_CHECKING( NULL != pqueue || NULL != pqueue->pvector || NULL != pqueue->pvector->array,
					NULL == pqueue || NULL == pqueue->pvector || NULL == pqueue->pvector->array,
					"ERROR: Queue Not Found.", 
					NULL,
					NULL);

	if (FAILURE == status)
		return (FAILURE);


	fprintf(stdout, "\n{START}");
	for(size_t le = 0; le < pqueue->pvector->nr_of_elements; le++)
	{
		pprintfunc(pqueue->pvector->array[le]);
	}
	fprintf(stdout, "{END}\n");

	return(SUCCESS);
}

extern	size_t 	mv_queue_length(p_mv_queue_t pqueue)
{
	// Code

	// Code
	ret_t status = SUCCESS;
	status = ERROR_CHECKING( NULL != pqueue || NULL != pqueue->pvector,
					NULL == pqueue || NULL == pqueue->pvector,
					"ERROR: Queue Not Found.", 
					NULL,
					NULL);

	if (FAILURE == status)
		return (FAILURE);


	return(pqueue->pvector->nr_of_elements);
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

	if(pqueue->pvector->array)
	{
		free(pqueue->pvector->array);
		pqueue->pvector->array = NULL;
	}

	if(pqueue->pvector)
	{
		free(pqueue->pvector);
		pqueue->pvector = NULL;
	}

	if(pqueue)
	{
		free(pqueue);
		pqueue = NULL;
	}

	ppqueue = NULL;

	return(SUCCESS);
}


