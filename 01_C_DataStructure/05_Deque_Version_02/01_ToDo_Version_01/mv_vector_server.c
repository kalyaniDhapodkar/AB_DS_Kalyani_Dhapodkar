

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "mv_vector_header.h"

// Function Declaration
void error_checking( const int assert_condition,
					 const char* assert_condition_str,
					 const char* file_name,
					 const int line_no,
					 const int error_condition,
					 const char* error_str);

#define  	ERROR_CHECKING( assert_condition, error_condition, error_str) {											\
																				error_checking(assert_condition,	\
																								#assert_condition,	\
																								__FILE__,			\
																								__LINE__,			\
																								error_condition,	\
																								error_str);			\
																			}

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

void error_checking( const int assert_condition,
					 const char* assert_condition_str,
					 const char* file_name,
					 const int line_no,
					 const int error_condition,
					 const char* error_str)
{
	// Code
	#ifdef DEBUG 	
		// Checking Assertion
		if(!assert_condition)
		{
			fprintf(stderr, "Assertion failed : %s, File %s Line no %d\n", assert_condition_str, file_name, line_no);
		}
	#else
		// Error Checking
		if( error_condition)
		{
			if(NULL != error_str)
			{
				fprintf(stderr, error_str);
			}
			exit(FAILURE);
		}
	#endif
}

// Vector Interface Functions

/*
	Function Name 	: create_vector
	Description 	: create a vector
	Input Params 	: void - NULL
	Output  		: pointer to a vector
*/

extern  p_mv_vector_t  mv_create_default_vector(size_t default_size)
{
	// Code
	p_mv_vector_t pvec = (p_mv_vector_t)xmalloc(SIZE_MV_VECTOR);
	ERROR_CHECKING( NULL != pvec,
					0,
					NULL);

	pvec->capacity = default_size;
	pvec->nr_of_elements = 0;
	pvec->array = (p_data_t)xcalloc(pvec->capacity, SIZE_DATA);
	ERROR_CHECKING( NULL != pvec->array,
					0,
					NULL);

	return(pvec);
}

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
	Description 	: push/adds data in vector at back
	Input Params 	: 1. pointer to the vectr
					  2. Data to be push
	Output  		: SUCCESS - if pushed/added successfully
					  FAILURE - if failed
*/

extern  ret_t mv_vector_push_back(p_mv_vector_t pvector, data_t data)
{
	ERROR_CHECKING( NULL != pvector,
					NULL == pvector,
					"ERROR: Vector Not Found.\n");

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
	Function Name 	: mv_vector_push_front
	Description 	: push/adds data in vector in front
	Input Params 	: 1. pointer to the vectr
					  2. Data to be push
	Output  		: SUCCESS - if pushed/added successfully
					  FAILURE - if failed
*/

extern  ret_t mv_vector_push_front(p_mv_vector_t pvector, data_t data)
{
	ERROR_CHECKING( NULL != pvector,
					NULL == pvector,
					"ERROR: Vector Not Found.\n");

	// Check for vector's capacity
	if(pvector->nr_of_elements >= pvector->capacity)
	{
		// capacity double
		pvector->capacity = pvector->capacity * 2;

		pvector->array = (p_data_t)xrealloc(pvector->array, pvector->capacity * SIZE_DATA);
		ERROR_CHECKING( NULL != pvector->array,
						0, 
						NULL);
	}

	pvector->nr_of_elements++;

    for(long le = pvector->nr_of_elements-1; le > 0; le--)
    {
        pvector->array[le] = pvector->array[le-1];
    }

    pvector->array[0] = data;

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

	ERROR_CHECKING( NULL != pvector, 
					NULL == pvector ||
					0 == pvector->nr_of_elements,
					"ERROR: Vector Not found\n");

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


/*
	Function Name 	: mv_vector_pop_front
	Description 	: pops front element from the vector
	Input Params 	: 1. pointer to the vector
	Output  		: data - popped data
*/

extern	data_t	mv_vector_pop_front(p_mv_vector_t pvector)
{
	// Code

	ERROR_CHECKING( NULL != pvector, 
					NULL == pvector ||
					0 == pvector->nr_of_elements,
					"ERROR: Vector Not found\n");

    for(size_t le = 0; le < pvector->nr_of_elements-1; le++)
    {
        pvector->array[le] = pvector->array[le+1];
    }

    pvector->nr_of_elements--;

    if(pvector->nr_of_elements < pvector->capacity/2)
    {
        pvector->capacity = pvector->capacity / 2;
        pvector->array = (p_data_t)xrealloc(pvector->array, pvector->capacity * SIZE_DATA);
	    ERROR_CHECKING( NULL != pvector->array, 
						0,
	 					NULL);
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

extern	data_t	mv_vector_data_at(p_mv_vector_t pvector, size_t index)
{
	// Code

	ERROR_CHECKING( NULL != pvector, 
					NULL == pvector ||
					0 == pvector->nr_of_elements,
					"ERROR: Vector Not found\n");
	
	ERROR_CHECKING( 1,
					index >= pvector->nr_of_elements,
					"ERROR: Index out of bound.\n" );

	return( pvector->array[ index ] ); 
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
	ERROR_CHECKING( NULL != pvector, 
					NULL == pvector,
					"ERROR: Vector Not found\n");

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
	ERROR_CHECKING( NULL != pvector, 
					NULL == pvector,
					"ERROR: Vector Not found\n");

	return( pvector->capacity );
}


/*
	Function Name 	: mv_vector_print_data
	Description 	: prints the data present in vector
	Input Params 	: 1. pointer to a vector
	Output  		: SUCCESS - if printed successfully
*/

extern ret_t mv_vector_print_data(p_mv_vector_t pvector, PRINTDATAPROC pprintfunc)
{
	// Code
	ERROR_CHECKING( NULL != pvector, 
					NULL == pvector,
					"ERROR: Vector Not found\n");


    fprintf(stdout, "{START}-");
    for (long long le = 0; le < mv_vector_size(pvector); ++le)
    {
        pprintfunc(pvector->array[le]);
    }
    fprintf(stdout, "{END}\n");

    return(SUCCESS);
}

/*
	Function Name 	: mv_vector_destroy
	Description 	: destroy the given vector
	Input Params 	: 1. address of the vector
	Output  		: SUCCESS - if destroyed successfully
*/

extern	ret_t	mv_vector_destroy(pp_mv_vector_t ppvector, DELETEDATAPROC pdeletefunc)
{
	// Code
	ERROR_CHECKING( NULL != ppvector, 
					NULL == ppvector,
					"ERROR: Vector Not found\n");

	p_mv_vector_t pvector = *ppvector;

	ERROR_CHECKING( NULL != pvector, 
					NULL == pvector,
					"ERROR: Vector Not found\n");

	fprintf(stdout, "{START}\n");
    for (long long le = 0; le < mv_vector_size(pvector); ++le)
    {
        pdeletefunc(pvector->array[le]);
        pvector->array[le] = NULL;
    }
    fprintf(stdout, "{END}\n");


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
