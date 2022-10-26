
// Headers
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdarg.h>
#include <string.h>

#include "vector.h"

// Function Declaration
void 	error_checking( const int assert_condition,
						const char* assert_condition_str, 
						const char* file_name,
						const int line_no,
						const int error_condition,
						const char* error_str);

// Macros
#define 	ERROR_CHECKING( assert_condition, error_condition, error_str)	{										\
																				error_checking( assert_condition,	\
																								#assert_condition, 	\
																								__FILE__,			\
																								__LINE__,			\
																								error_condition,	\
																								error_str);			\
																			}

			
//	Vector Helper Functions
static	void* xmalloc(size_t nr_of_bytes)
{
	// Code
	void*	p = malloc(nr_of_bytes);

	ERROR_CHECKING( 1, NULL == p, "ERROR: Out Of Memory.\n" );
		
	return(p);
}

static	void* xcalloc(size_t nr_of_elements, size_t nr_of_bytes)
{
	// Code
	void* p = calloc(nr_of_elements, nr_of_bytes);

	ERROR_CHECKING( 1, NULL == p, "ERROR: Out Of Memory.\n" );
	
	return(p);
}

static	void* xrealloc(void* p, size_t nr_of_bytes)
{
	// Code
	void* rp = realloc(p, nr_of_bytes);
	
	ERROR_CHECKING( 1, NULL == p, "ERROR: Out Of Memory.\n" );
	
	return(rp);
}


/*
	Function
		identifire : Error_checking
		input :
			1. assertion condition
			2. assertion condition string
			3. File Name
			4. Line no
			5. error checking
			6. const char*
*/

void 	error_checking( const int assert_condition,
						const char* assert_condition_str,
						const char* file_name,
						const int line_no,
						const int error_condition,
						const char* error_str)
{
	// Code
	#ifdef DEBUG
		// Check Assertion
	if(!assert_condition)
	{
		fprintf(stderr, "Asserrtion Failed : %s, File %s, Line no %d\n", assert_condition_str, file_name, line_no);
	}
	#else
		// Error Checking 
		if(error_condition)
		{
			if(NULL != error_str)
			{
				fprintf(stderr, error_str);
			}
			exit(FAILURE);
		}
	#endif
}

// Vector Interface function

/*
	Function Name 	: create_vector
	Description 	: create a vector
	Input Params 	: void - NULL
	Output  		: pointer to a vector
*/

extern p_mv_vector_t create_vector(void)
{
	// Code
	p_mv_vector_t pvec = (p_mv_vector_t)xmalloc(SIZE_MV_VECTOR);
	ERROR_CHECKING( NULL != pvec,
					0, 
					NULL);

	pvec->capacity = 2;
	pvec->nr_of_elements = 0;
	pvec->array = (p_data_t)xcalloc(pvec->capacity, SIZE_DATA);
	ERROR_CHECKING(NULL != pvec->array, 
					0, 
					NULL);

	return(pvec);
}

/*
	Function Name 	: mv_vector_push_back
	Description 	: push/adds data in vector
	Input Params 	: 1. pointer to the vectr
					  2. No of Data to be pushed
					  3. ...(ellipses) data to be push
	Output  		: SUCCESS - if pushed/added successfully
					  FAILURE - if failed
*/

extern ret_t 	mv_vector_push_back(p_mv_vector_t pvector, size_t no_of_data, ...)
{
	// Code 
	ERROR_CHECKING( NULL != pvector, 
					NULL == pvector,
					"ERROR: Vector Not Found.\n");

	ERROR_CHECKING( 0 != no_of_data,
					0 == no_of_data,
					"ERROR: No. of data cannot be zero.\n");

	data_t add_data;
	va_list arg;

	va_start(arg, no_of_data);
	for( size_t le = 0; le < no_of_data; le++)
	{
		// Check for vectors capacity
		if(pvector->nr_of_elements == pvector->capacity)
		{	
			// Double the capacity
			pvector->capacity *= 2;
			pvector->array = (p_data_t)xrealloc(pvector->array, pvector->capacity * SIZE_DATA);
			ERROR_CHECKING( NULL != pvector->array,
							0, 
							NULL);
		}

		add_data = va_arg(arg, data_t);
		pvector->array[ pvector->nr_of_elements ] = add_data;
		pvector->nr_of_elements++;
	}

	va_end(arg);

	return(SUCCESS);
}


/*
	Function Name 	: mv_vector_pop_back
	Description 	: pops last element from the vector
	Input Params 	: 1. pointer to the vector
					  2. no of data to be popped
	Output  		: data - popped data
*/

extern data_t  	mv_vector_pop_back(p_mv_vector_t pvector, size_t no_of_data)
{
	// Code
	ERROR_CHECKING(	NULL != pvector,
					NULL == pvector || 
					0 == pvector->nr_of_elements,
					"ERROR: Vector Not Found.\n");

	ERROR_CHECKING( 0 != no_of_data,
					0 == no_of_data,
					"ERROR: No. of data cannot be zero.\n" );

	data_t to_return_data = NULL;		

	for(size_t le = 0; le < no_of_data; le++)
	{
		// Remove the data 
		pvector->nr_of_elements--;
		to_return_data = pvector->array[ pvector->nr_of_elements ];
	
		// Reduce the capacity
		if( pvector->nr_of_elements == pvector->capacity / 2)
		{
			pvector->capacity /= 2;
			pvector->array = (p_data_t)xrealloc(pvector->array, pvector->capacity * SIZE_DATA);
			ERROR_CHECKING( NULL != pvector->array,
							0, 
							NULL);
		}

		delete_data(to_return_data);
	}

	return(NULL);
}


/*
	Function Name 	: mv_vector_data_at
	Description 	: gives the last element from vector
	Input Params 	: 1. pointer to the vector
					  2. index whose data is needed
	Output  		: data from the given index
*/

extern data_t  	mv_vector_data_at(p_mv_vector_t pvector, size_t index)
{
	// Code
	ERROR_CHECKING( NULL != pvector,
					NULL == pvector ||
					0 == pvector->nr_of_elements,
					"ERROR: Vector Not Found.\n");

	ERROR_CHECKING( 1, 
					index >= pvector->nr_of_elements,
					"ERROR: Index out of bound.\n");

	return( pvector->array[ index ] );
}


/*
	Function Name 	: mv_vector_size
	Description 	: gives the size of vector
	Input Params 	: 1. pointer to the vector
	Output  		: size of vector
*/

extern size_t  	mv_vector_size(p_mv_vector_t pvector)
{
	// Code 
	ERROR_CHECKING( NULL != pvector,
					NULL == pvector,
					"ERROR: Vector Not Found.\n");

	return( pvector->nr_of_elements);
}


/*
	Function Name 	: mv_vector_capacity
	Description 	: gives the capacity of vector
	Input Params 	: 1. pointer to the vector
	Output  		: capacity of vector
*/

extern size_t  	mv_vector_capacity(p_mv_vector_t pvector)
{
	// Code
	ERROR_CHECKING( NULL != pvector,
					NULL == pvector,
					"ERROR: Vector Not Found.\n");

	return(pvector->capacity);
}


/*
	Function Name 	: forward_print_data
	Description 	: prints data from forward way
	Input Params 	: 1. pointer to the vector
	Output  		: void
*/

extern void forward_print_data(p_mv_vector_t pvector)
{
	//	Code
	fprintf(stdout, "\nForward Print\n{START}-");
	for( long le = 0; le < mv_vector_size(pvector); le++)
	{
		print_data(mv_vector_data_at(pvector, le));
	}
	fprintf(stdout,"{END}\n");
}


/*
	Function Name 	: backward_print_data
	Description 	: prints data from backward way
	Input Params 	: 1. pointer to the vector
	Output  		: void
*/

extern void backward_print_data(p_mv_vector_t pvector)
{
	//	Code
	fprintf(stdout, "\nBackward Print\n{START}-");
	for( long le = mv_vector_size(pvector); le > 0 ; le--)
	{
		print_data(mv_vector_data_at(pvector, le-1));
	}
	fprintf(stdout,"{END}\n");
}


/*
	Function Name 	: mv_vector_destroy
	Description 	: destroy the given vector
	Input Params 	: 1. address of the vector
	Output  		: SUCCESS - if destroyed successfully
*/

extern ret_t  	mv_vector_destroy(pp_mv_vector_t ppvector)
{
	// Code
	ERROR_CHECKING( NULL != ppvector,
					NULL == ppvector,
					"ERROR: Vector Not Found.\n");

	p_mv_vector_t pvector = *ppvector;

	ERROR_CHECKING( NULL != pvector,
					NULL == pvector,
					"ERROR: Vector Not Found.\n");

	if( pvector->array )
	{
		free(pvector->array);
		pvector->array = NULL;
		pvector->nr_of_elements = 0;
		pvector->capacity = 0;
	}

	if(pvector)
	{
		free(pvector);
		pvector = NULL;
	}

	*ppvector = NULL;

	return(SUCCESS); 
}

