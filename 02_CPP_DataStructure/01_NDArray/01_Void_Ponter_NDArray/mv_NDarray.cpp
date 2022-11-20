
// Headers
#include <iostream>
#include <cstdarg>

#include "mv_NDarray.hpp"

// Class Function Definition

// Parameterizer Constructor
MVArray::MVArray(size_t no_of_dimension, ...)
{
	// Code
	if( 0 == no_of_dimension)
	{
		std::cerr << "ERROR: No of Dimension cannot be 0 or less than o." << std::endl;
		return;
	}

	// Set no of DImensions
	this->no_of_dimension = no_of_dimension;

	// Allocate Array to store each dimension
	this->dimension_array = new size_t[no_of_dimension];

	va_list args;

	va_start(args, no_of_dimension);
	for(long le = 0; le < no_of_dimension; le++)
	{
		this->dimension_array[le] = va_arg(args, long);
	}
	va_end(args);

	// Find Total no of elements
	size_t no_of_elements = dimension_array[0];
	for(long le = 1; le < no_of_dimension; le++)
	{
		no_of_elements = no_of_elements * dimension_array[le];		
	}

	// Allocate Data Array
	this->data_array = new data_t[no_of_elements];

	// Allocate to jump Array
	this->to_jump_dimension_array = new size_t[no_of_dimension];

	this->to_jump_dimension_array[no_of_dimension-1] =  1;

	// Set to Jump Array
	for(long le = no_of_dimension-2; le >= 0; --le)
	{
		this->to_jump_dimension_array[le] = this->to_jump_dimension_array[le+1] * this->dimension_array[le+1];
	}
}

//Destructor
MVArray::~MVArray()
{
	// Code
	if(this->to_jump_dimension_array)
	{
		delete[] this->to_jump_dimension_array;
	}

	if(this->data_array)
	{
		delete[] this->data_array;
	}

	if(this->dimension_array)
	{
		delete[] this->dimension_array;
	}
}

// Setter Member Function
ret_t  	MVArray::SetData(data_t data, ...)
{
	// Code
	size_t* indices = new size_t[no_of_dimension];

	va_list args;

	va_start(args, data);
	for(long le = 0; le < no_of_dimension; le++)
	{
		indices[le] = va_arg(args, long);
	}
	va_end(args);

	// Calculate the required index
	size_t required_index = 0;
	for(long le = 0; le < no_of_dimension; le++)
	{
		required_index = required_index + indices[le] * to_jump_dimension_array[le];
	}

	data_array[required_index] = data;

	delete[] indices;

	return(SUCCESS);
}

// Getter Member Function
data_t 	MVArray::GetData(...)
{
	// Code
	size_t* indices = new size_t[no_of_dimension];

	va_list args;

	va_start(args, this);
	for(long le = 0; le <no_of_dimension; le++)
	{
		indices[le] = va_arg(args, long);
	}
	va_end(args);

	long required_index = 0;
	for(long le = 0; le < no_of_dimension; le++)
	{
		required_index = required_index + indices[le] * to_jump_dimension_array[le];
	}

	data_t to_return_data = data_array[required_index];

	delete[] indices;

	return(to_return_data);
}

// Get Size of Dimension
size_t  MVArray::GetDimensionSize(size_t index) const
{
	// Code
	return(this->dimension_array[index]);
}