

// Headers
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

#include "NDArray.h"

// TODO Function - replaces assertion and error_checking by 
// 					error_checking macro 

static ret_t  	error_checking( const int assert_condition,
								const char* assert_condition_str,
								const char* file_name,
								const long line_no,
								const int error_condition,
								const char* error_str);

// Macros
#define  	ERROR_CHECKING( assert_condition, error_condition, error_str) (									\
																			error_checking( assert_condition,	\
																							#assert_condition,	\
																							__FILE__,			\
																							__LINE__,			\
																							error_condition,	\
																							error_str)			\
																		)

// Array Helper Function

/*
	Function Name 	: xmalloc
	Description 	: alloacate memory of given size
	Input Params 	: 1. no_of_bytes
	Return  		: pointer to allocated memory block
*/

static void*  	xmalloc(size_t no_of_bytes)
{	
	ret_t status = SUCCESS;

	// Code
	void* p = malloc(no_of_bytes);
	status = ERROR_CHECKING( 1, NULL == p, "ERROR: Out Of Memory.\n" );

	if(status == FAILURE)
		exit(FAILURE);

	return(p);
}

/*
	Function Name 	: xcalloc
	Description 	: alloacate continous memory of given size
	Input Params 	: 1. no_of_elements
					  2. no_of_bytes
	Return  		: pointer to allocated memory block
*/

static  void*  	xcalloc(size_t no_of_elements, size_t no_of_bytes)
{
	ret_t status = SUCCESS;

	// Code
	void* p = calloc(no_of_elements, no_of_bytes);
	status = ERROR_CHECKING(1, NULL == p, "ERROR: Out Of Memory.\n");

	if(status == FAILURE)
		exit(FAILURE);

	return(p);
}

/*
	Function 
		identifire :Error_checking
		input  :
			1. assertion codition
			2. assertion condition string
			3. File Name
			4. Line no
			5. error checking
			6. const str*
*/

static ret_t  	error_checking( const int assert_condition,
						const char* assert_condition_str,
						const char* file_name,
						const long line_no,
						const int error_condition,
						const char* error_str)
{
	ret_t status = SUCCESS;

	// Code
	#ifdef DEBUG 
		// Check Assertion
	if(!assert_condition)
	{
		fprintf(stderr, 
				"Assertion Failed : %s, File %s, Line no %d\n", 
				assert_condition_str, 
				file_name, 
				line_no);
		status = FAILURE;
	}
	#else
		// Error Checking
		if(error_condition)
		{
			fprintf(stderr, error_str);
			status = FAILURE;
		}
	#endif

	return(status);
}

// Array Interface Function

/*
	Function Name 	: create_array
	Description 	: creates a array of given no. of dimension
	Input Params 	: 1. no_of_dimensions
					  2. ... (ellipses) (size of each dimension)
	Return  		: pointer to array created
*/

extern 	p_array_t 	create_array(size_t no_of_dimensions, ...)
{
	ret_t status = SUCCESS;

	// Code
	status = ERROR_CHECKING( 0 != no_of_dimensions,
							 0 == no_of_dimensions,
							"ERROR: 0 dimension array not possible.\n");

	if(status == FAILURE)
		return(NULL);

		p_array_t parray = (p_array_t)xmalloc(SIZE_ARRAY);

		/*
			Step 1: Initialize the n of dimensions for array
		*/

		parray->no_of_dimensions = no_of_dimensions;

		/*
			Step 2: Allocate an array to store the size of every dimension
					with 'no_of_dimension' as no of elements.
		*/

		// Initialize size of each dimension
		parray->pdimension = (p_dimension_t)xcalloc(no_of_dimensions, sizeof(long));
		
		/*
			Step 3: Get the size of every dimension from variadic input parameters and
					store it in the allocated array from step 2.
		*/

		// Storing all the sizes of each dimension
		va_list arg;

		va_start(arg, no_of_dimensions);
		for(long le = 0; le < no_of_dimensions; ++le)
		{
			parray->pdimension[le] = va_arg(arg, long);
		}
		va_end(arg);

		/*
			step 4: Calculating the total no of elements for the data array by multiplying sizes of each
					dimension
		*/

		// Allocatinf memory to array
		size_t no_of_elements = parray->pdimension[0];

		// Calculating no of elements
		for(long le = 1; le < no_of_dimensions; le++)
			no_of_elements = no_of_elements * parray->pdimension[le];

		/*
			Step 5: Allocate the data array.
		*/
		parray->ptr = (p_data_t)xcalloc(no_of_elements, sizeof(void*));

		/*
			Step 6: Initialize all the bytes of allocated array to '0' .
		*/
		memset(parray->ptr, 0, no_of_elements * sizeof(void*));

		parray->to_jump_dimension = (size_t*)xcalloc( no_of_dimensions, sizeof(size_t));

		parray->to_jump_dimension[ no_of_dimensions - 1] = 1;

		for( long le = no_of_dimensions-2; le >= 0; --le)
		{
			parray->to_jump_dimension[le] = parray->pdimension[le+1] * parray->to_jump_dimension[le+1];
		}

		return(parray);
}

/*
	Function Name 	: array_set_data
	Description 	: add gievn data in array
	Input Params 	: 1. pointer to an array
					  2. data to be inserted
					  3. indexes on which data to be inserted
	Return  		: SUCCESS - if added successfully
*/

extern 	ret_t  		array_set_data(p_array_t parray, data_t data, ...)
{
	ret_t status = SUCCESS;

	// Code
	long* indices = NULL;

	// Error Checking
	status = ERROR_CHECKING( NULL != parray,
					NULL == parray,
					"ERROR: No Array Found.\n");

	if( status ==  FAILURE)
		return(FAILURE);

	// Allocate array to store indices
	indices = (long*)xcalloc(parray->no_of_dimensions, sizeof(long));

	// Get indices from input parameters
	va_list arg;

	va_start(arg, data);
	for(long le = 0; le < parray->no_of_dimensions; le++)
	{
		long index = va_arg(arg, long);

		status = ERROR_CHECKING( index >= 0 && index < parray->pdimension[le],
						index < 0 || index >= parray->pdimension[le],
						"ERROR: Index Out Of Bound.\n");

		if(status == FAILURE)
		{
			va_end(arg);
			free(indices);
			return(FAILURE);
		}

		indices[le] = index;
	}

	va_end(arg);

	// Calculate the final index
	size_t final_index = 0;
	for(long le = 0; le < parray->no_of_dimensions; le++)
	{
		final_index = final_index + parray->to_jump_dimension[le] * indices[le];
	}

	// Set the value 
	parray->ptr[final_index] = data;

	// Free the indices array
	free(indices);
	indices = NULL;

	return(SUCCESS);
}


/*
	Function Name 	: array_get_data
	Description 	: given data from given indexes
	Input Params 	: 1. pointer to a array
					  3. indexes from which data to be returned
	Return  		: data
*/

extern 	data_t 		array_get_data(p_array_t parray, ...)
{
	// Code
	long* indices = NULL;
	ret_t status = SUCCESS;

	status = ERROR_CHECKING( NULL != parray,
					NULL == parray,
					"ERROR: No Array Found.\n");

	if(status == FAILURE)
		return(NULL);

	// Allocate array for indices
	indices = (long*) xcalloc(parray->no_of_dimensions, sizeof(long));

	// Assign indices value
	va_list arg;
	va_start(arg, parray);
	for(long le = 0; le < parray->no_of_dimensions; le++)
	{
		long index = va_arg(arg, long);

		status = ERROR_CHECKING( index >= 0 && index < parray->pdimension[le],
									index < 0 || index >= parray->pdimension[le],
									"ERROR: Index Out of Bound.\n");

		if(status == FAILURE)
		{
			va_end(arg);
			free(indices);
			return(NULL);
		}

		indices[le] = index;
	}
	va_end(arg);

	// Calculate final index 
	size_t final_index = 0;
	for(long le = 0; le < parray->no_of_dimensions; le++)
	{
		final_index = final_index + parray->to_jump_dimension[le] * indices[le];
	}

	// Get the value 
	data_t to_return_data = parray->ptr[final_index];

	// free indices
	free(indices);

	// Return Data
	return(to_return_data);
}

/*
	Function Name 	: array_get_size_of_dimension
	Description 	: gets the size of given dimension
	Input Params 	: 1. pointer to a array
					  2. data to be inserted
					  3. indexes on which data to be inserted
	Return  		: size of dimension
*/

extern  long  		array_get_size_of_dimension(p_array_t parray, long index)
{
		ret_t status = SUCCESS;

		status = ERROR_CHECKING( NULL != parray, 
								 NULL == parray,
								 "ERROR: No Array Found.\n");
		if(status == FAILURE)
			return(0);

		status = ERROR_CHECKING( index < parray->no_of_dimensions,
								 index >= parray->no_of_dimensions,
								 "ERROR: Dimension does not exits.\n");
		if(status == FAILURE)
			return(0);

		return( parray->pdimension[index] );
}

/*
	Function Name 	: array_destroy
	Description 	: destroys the given array
	Input Params 	: 1. address of the  array to be destory
	Return  		: SUCCESS - if destroyed successfully
*/

extern  ret_t  		array_destroy(pp_array_t pparray)
{
	// Code
	p_array_t parray = *pparray;
	ret_t status = SUCCESS;

		status = ERROR_CHECKING( NULL != parray,
								 NULL == parray,
								 "ERROR: No Array found to Destory.\n");

		if(status == FAILURE)
		return(FAILURE);

	// Free the data array
		if(parray->ptr)
		{
			free(parray->ptr);
			parray->ptr = NULL;
		}

		// Free the size of each dimension array
		if(parray->pdimension)
		{
			free(parray->pdimension);
			parray->pdimension = NULL;
		} 

		// Free the struct object
		if( parray )
		{
			free(parray);
			parray = NULL;
		}

		// Assign NULL to the client side pointer 
		*pparray = NULL;

		return(SUCCESS);
}

