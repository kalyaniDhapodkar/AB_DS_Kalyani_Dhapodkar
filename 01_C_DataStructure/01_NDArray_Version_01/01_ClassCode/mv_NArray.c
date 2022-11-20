
// Headers 
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>

#include "mv_NDArray.h"

// Array Helper Function

/*
	Function Name 	: xmalloc
	Description 	: alloacate memory of given size
	Input Params 	: 1. no_of_bytes
	Return  		: pointer to allocated memory block
*/

static void*  xmalloc(size_t no_of_bytes)
{
	// Code
	void* p = malloc(no_of_bytes);
	if( NULL == p)
	{
		fprintf(stderr, "ERROR: Out Of Memory.\n");
		exit(FAILURE);
	}

	return(p);
}

/*
	Function Name 	: xcalloc
	Description 	: alloacate continous memory of given size
	Input Params 	: 1. no_of_elements
					  2. no_of_bytes
	Return  		: pointer to allocated memory block
*/

static void*  	xcalloc(size_t no_of_elements, size_t no_of_bytes)
{
	// Code 
	void* p = calloc(no_of_elements, no_of_bytes);
	if(NULL == p)
	{
		fprintf(stderr, "ERROR: Out Of Memory.\n");
		exit(FAILURE);
	}

	return(p);
}

// Array Interface Function

/*
	Function Name 	: create_array
	Description 	: creates a array of given no. of dimension
	Input Params 	: 1. no_of_dimensions
					  2. ... (ellipses) (size of each dimension)
	Return  		: pointer to array created
*/

extern  p_array_t  	create_array(size_t no_of_dimensions, ...)
{
	// Code

	// Test Case
	#ifdef  MY_DEBUG
		assert( 0 != no_of_dimensions);
	#else
		if( 0 == no_of_dimensions)
		{
			fprintf(stderr, "0 dimension array not possible.\n");
			return(NULL);
		}
	#endif

		p_array_t parray = (p_array_t)xmalloc(SIZE_ARRAY);

		parray->no_of_dimensions = no_of_dimensions;

		parray->pdimension = (p_dimension_t)xcalloc(no_of_dimensions, sizeof(long));

		va_list arg;

		va_start(arg, no_of_dimensions);
		for(long le = 0; le < no_of_dimensions; le++)
		{
			parray->pdimension[le] = va_arg(arg, long);
		}
		va_end(arg);

		size_t no_of_elements = parray->pdimension[0];

		for(long le = 1; le < no_of_dimensions; le++)
			no_of_elements = no_of_elements * parray->pdimension[le];

		parray->ptr = (p_data_t)xcalloc(no_of_elements, sizeof(void*));

		memset(parray->ptr, 0, no_of_elements * sizeof(void*));

		parray->to_jump_dimension = (size_t*)xcalloc(no_of_dimensions, sizeof(size_t));

		parray->to_jump_dimension[no_of_dimensions - 1] = 1;

		for(long le = no_of_dimensions-2; le >= 0; --le)
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

extern ret_t  	array_set_data(p_array_t parray, data_t data, ...)
{
	// Code
	long* indices = NULL;

	// ERROR Checking
	#ifdef MY_DEBUG
		assert(NULL != parray);
	#else
		if(NULL == parray)
		{
			fprintf(stderr, "ERROR: No Array Found.\n");
			return(FAILURE);
		}
	#endif

	// Allocating array to store indices
	indices = (long*)xcalloc(parray->no_of_dimensions, sizeof(long));

	// Get indices from input parameters
	va_list arg;

	va_start(arg, data);
	for(long le = 0; le < parray->no_of_dimensions; le++)
	{
		long index = va_arg(arg, long);

		#ifdef  MY_DEBUG
			assert(index >= 0 && index < parray->pdimension[le])
		#else
			if(index < 0 || index >= parray->pdimension[le])
			{
				fprintf(stderr, "ERROR: Index Out Of Bound.\n");
				va_end(arg);
				free(indices);
				return(FAILURE);
			}
		#endif

		indices[le] = index;
	}

	va_end(arg);

	// Calculating the final index
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

extern  data_t  	array_get_data(p_array_t parray, ...)
{
	// Code
	long* indices = NULL;

	// ERROR Checking 
	#ifdef	MY_DEBUG
		assert(NULL != parray);
	#else
		if(NULL == parray)
		{
			fprintf(stderr, "ERROR: No Array Found.\n");
			return(NULL);
		}
	#endif

	// Allocate array for indices
	indices = (long*) xcalloc(parray->no_of_dimensions, sizeof(long));

	// Assign indices value
	va_list arg;
	va_start(arg, parray);
	for(long le = 0; le < parray->no_of_dimensions; le++)
	{
		long index = va_arg(arg, long);

		#ifdef  MY_DEBUG
			assert(index >= 0 && index < parray->pdimension[le])
		#else
			if(index < 0 || index >= parray->pdimension[le])
			{
				fprintf(stderr, "ERROR: Index Out of Bound.\n");
				va_end(arg);
				free(indices);
				return(NULL);
			}
		#endif

		indices[le] = index;
	}
	va_end(arg);

	// Calculate Final index
	size_t final_index = 0;
	for(long le = 0; le < parray->no_of_dimensions; le++)
	{
		final_index = final_index + parray->to_jump_dimension[le] * indices[le];
	}

	// Get the value
	data_t to_return_data = parray->ptr[final_index];

	// Free indices
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

extern  long 	array_get_size_of_dimension(p_array_t parray, long index)
{
	#ifdef MY_DEBUG
		assert( NULL != parray)
	#else
		if( NULL == parray)
		{
			fprintf(stderr, "ERROR: No Array Found.\n");
			return(0);
		}
	#endif

	return(parray->pdimension[index]);
}

/*
	Function Name 	: array_destroy
	Description 	: destroys the given array
	Input Params 	: 1. address of the  array to be destory
	Return  		: SUCCESS - if destroyed successfully
*/

extern  ret_t  	array_destroy(pp_array_t pparray)
{
	// Code
	p_array_t parray = *pparray;

	#ifdef MY_DEBUG
		assert(NULL != parray)
	#else
		if( NULL == parray)
		{
			fprintf(stderr, "ERROR: No Array Found To Destroy.\n");
			return(FAILURE);
		}
	#endif

	// Free the data array
		if(parray->ptr)
		{
			free(parray->ptr);
			parray->ptr = NULL;
		}

	// Free the Size of each dimension array
		if(parray->pdimension)
		{
			free(parray->pdimension);
			parray->pdimension = NULL;
		}

	// Free the struct object
		if(parray)
		{
			free(parray);
			parray = NULL;
		}

	// Assign NULL to the Client side pointer
		*pparray = NULL;
		
		return(SUCCESS);
}

