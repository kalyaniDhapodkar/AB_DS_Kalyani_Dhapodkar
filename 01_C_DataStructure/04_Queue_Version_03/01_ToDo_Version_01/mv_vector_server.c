

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mv_vector_header.h"

// Function Declaration
static ret_t error_checking( const int assert_condition,
					 const char* assert_condition_str,
					 const char* file_name,
					 const int line_no,
					 const int error_condition,
					 const char* error_str);

#define  	ERROR_CHECKING( assert_condition, error_condition, error_str) (											\
																				error_checking(assert_condition,	\
																								#assert_condition,	\
																								__FILE__,			\
																								__LINE__,			\
																								error_condition,	\
																								error_str)			\
																			)

// Vector Helper function
static void* xmalloc(size_t nr_of_bytes)
{
	// Code
	void* p = malloc(nr_of_bytes);

	ERROR_CHECKING(1, NULL == p, "ERROR: Out of Memory.\n");

	return(p);
}

static void*  xcalloc(size_t nr_of_elements, size_t nr_of_bytes)
{
	// Code
	void* p = calloc(nr_of_elements, nr_of_bytes);

	ERROR_CHECKING(1, NULL == p, "ERROR: Out Of Memory.\n");

	return(p);
}

static void*  xrealloc(void* p, size_t nr_of_bytes)
{
	// Code
	void* rp = realloc(p, nr_of_bytes);

	ERROR_CHECKING(1, NULL == p, "ERROR: Out of Memory.\n");

	return(rp);
}


/*
	Function Name 	: error_checking
	Description 	: function do assertion if DEBUG is define
					  else error checking
	Input Params 	: 1. assertion condition
					  2. assertion condition string
					  3. File Name
					  4. Line Number
					  5. Error Checking
					  6. Error string
*/

static ret_t error_checking( const int assert_condition,
					 const char* assert_condition_str,
					 const char* file_name,
					 const int line_no,
					 const int error_condition,
					 const char* error_str)
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


	return(status);
}

// Vector Interface Functions

/*
	Function Name 	: mv_create_default_vector
	Description 	: create a vector of default size
	Input Params 	: default size from queue
	Output  		: pointer to a vector
*/

extern  p_mv_vector_t  mv_create_default_vector(size_t default_size)
{
	// Code
	p_mv_vector_t pvec = (p_mv_vector_t)xmalloc(SIZE_MV_VECTOR);
	ERROR_CHECKING( NULL != pvec,
					0,
					NULL);

	pvec->capacity = 2;
	pvec->nr_of_elements = 0;
	pvec->array = (p_data_t)xcalloc(pvec->capacity, SIZE_DATA);
	ERROR_CHECKING( NULL != pvec->array,
					0,
					NULL);

	return(pvec);
}

/*
	Function Name 	: mv_create_custom_vector
	Description 	: create a vector of custom 
	Input Params 	: custom size from queue
	Output  		: pointer to a vector
*/

extern  p_mv_vector_t  mv_create_custom_vector(size_t custom_size)
{
	// Code
	p_mv_vector_t pvec = (p_mv_vector_t)xmalloc(SIZE_MV_VECTOR);
	ERROR_CHECKING( NULL != pvec,
					0,
					NULL);

	pvec->capacity = custom_size;
	pvec->nr_of_elements = 0;
	pvec->array = (p_data_t)xcalloc(pvec->capacity, SIZE_DATA);
	ERROR_CHECKING( NULL != pvec->array,
					0,
					NULL);

	return(pvec);
}


/*
	Function Name 	: mv_vector_push_back
	Description 	: push/adds data in vector
	Input Params 	: 1. pointer to the vectr
					  2. Data to be push
	Output  		: SUCCESS - if pushed/added successfully
					  FAILURE - if failed
*/

extern  ret_t mv_vector_push_back(p_mv_vector_t pvector, data_t data)
{
	// Check for vector's capacity
	if(pvector->nr_of_elements == pvector->capacity)
	{
		// capacity double
		pvector->capacity = pvector->capacity * 2;

		pvector->array = (p_data_t)xrealloc(pvector->array, pvector->capacity * SIZE_DATA);
		ERROR_CHECKING( NULL != pvector->array,
						0, 
						NULL);
	}

	pvector->array[pvector->nr_of_elements] = data;
	pvector->nr_of_elements++;

	return(SUCCESS);
}


/*
	Function Name 	: mv_vector_pop_back
	Description 	: pops last element from the vector
	Input Params 	: 1. pointer to the vector
	Output  		: data - popped data
*/

extern	data_t	mv_vector_pop_back(p_mv_vector_t pvector)
{
	// Code
	//	Remove the data
	pvector->nr_of_elements--;
	data_t to_return_data = pvector->array[ pvector->nr_of_elements ];

	// Reduce the Capacity
	if( pvector->nr_of_elements == pvector->capacity / 2 )
	{
		pvector->capacity /= 2;
		pvector->array = (p_data_t) xrealloc(pvector->array, pvector->capacity * SIZE_DATA);
		ERROR_CHECKING( NULL != pvector->array, 
						0,
						NULL);
	}	

	return(to_return_data);
}

extern	data_t	mv_vector_pop_front(p_mv_vector_t pvector)
{
	// Code
	ret_t status = ERROR_CHECKING( pvector->nr_of_elements != 0,
					pvector->nr_of_elements == 0,
					"ERROR: No Data To Pop.");

	if (FAILURE == status)
		return (NULL);


	data_t to_return_data = pvector->array[0];

	for(size_t le = 0; le < pvector->nr_of_elements-1; le++)
	{
		pvector->array[le] = pvector->array[le+1];
	}

	pvector->nr_of_elements--;

	if(pvector->nr_of_elements < pvector->capacity/2)
	{
		pvector->capacity = pvector->capacity / 2;
		pvector->array = (p_data_t)xrealloc(pvector->array, pvector->capacity * SIZE_DATA);
	}

	return(to_return_data);
}


/*
	Function Name 	: mv_vector_data_at
	Description 	: gives the last element from vector
	Input Params 	: 1. pointer to the vector
					  2. index whose data is needed
	Output  		: data from the given index
*/

extern	data_t	mv_vector_data_at(p_mv_vector_t pvector, size_t index)
{
	// Code
	ret_t status = ERROR_CHECKING( 1,
					index >= pvector->nr_of_elements,
					"ERROR: Index out of bound.\n" );

	if(FAILURE == status)
		return((data_t)0);

	return( pvector->array[ index ] ); 
} 


extern	ret_t 	mv_vector_print_data(p_mv_vector_t pvector, PRINTDATAPROC pprintfunc )
{
	// Code

	fprintf(stdout, "\n{START}");
	for(size_t le = 0; le < pvector->nr_of_elements; le++)
	{
		pprintfunc(pvector->array[le]);
	}
	fprintf(stdout, "{END}\n");

	return(SUCCESS);
}

/*
	Function Name 	: mv_vector_size
	Description 	: gives the size of vector
	Input Params 	: 1. pointer to the vector
	Output  		: size of vector
*/

extern	size_t 	mv_vector_size(p_mv_vector_t pvector)
{
	// Code
	return( pvector->nr_of_elements );
}


/*
	Function Name 	: mv_vector_capacity
	Description 	: gives the capacity of vector
	Input Params 	: 1. pointer to the vector
	Output  		: capacity of vector
*/

extern	size_t 	mv_vector_capacity(p_mv_vector_t pvector)
{
	// Code
	return( pvector->capacity );
}


/*
	Function Name 	: mv_vector_destroy
	Description 	: destroy the given vector
	Input Params 	: 1. address of the vector
	Output  		: SUCCESS - if destroyed successfully
*/

extern	ret_t	mv_vector_destroy(pp_mv_vector_t ppvector)
{
	// Code
	p_mv_vector_t pvector = *ppvector;

	ret_t status = ERROR_CHECKING( NULL != pvector, 
					NULL == pvector,
					"ERROR: Vector Not found\n");

	if(FAILURE == status)
		return(status);

	if( pvector->array )
	{
		free(pvector->array);
		pvector->array = NULL;
		pvector->nr_of_elements = 0;
		pvector->capacity = 0;
	}

	if( pvector )
	{
		free(pvector);
		pvector = NULL;
	} 

	*ppvector = NULL;

	return(SUCCESS);
}
