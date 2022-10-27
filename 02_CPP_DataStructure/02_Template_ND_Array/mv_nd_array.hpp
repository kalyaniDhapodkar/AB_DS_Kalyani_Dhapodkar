

#pragma once

// Heaaders
#include <cstdarg>

// Constant Literals
#ifndef  	SUCCESS 
#define  	SUCCESS 	0
#endif

#ifndef  	FAILURE
#define  	FAILURE 	1
#endif

// Type Declaration
typedef  	int ret_t;

// Type Definition
template<typename T>
class MVArray
{
private:
	T* data_array;
	size_t* dimension_array;
	size_t 	no_of_dimensions;
	size_t* to_jump_dimension_array;
	size_t  no_of_elements;

public:
	// Parameterized Constructor
	MVArray(size_t no_of_dimensions, ...)
	{
		// Code
		if(0 == no_of_dimensions)
		{
			std::cerr << "ERROR: 0 Dimension Array not possible." << std::endl;
			return;
		}

		this->no_of_dimensions = no_of_dimensions;

		// Allocate Dimension Array
		this->dimension_array = new size_t[no_of_dimensions];

		va_list args;

		va_start(args, no_of_dimensions);
		for(long le = 0; le < no_of_dimensions; le++)
		{
			this->dimension_array[le] = va_arg(args, long);
		}
		va_end(args);

		// Allocate Data Array
		size_t no_of_elements = 1;
		for(long le = 0; le < no_of_dimensions; le++)
		{
			no_of_elements = no_of_elements * this->dimension_array[le];
		}
		this->no_of_elements = no_of_elements;

		this->data_array = new T[no_of_elements];

		// Allocate to Jump Array
		this->to_jump_dimension_array = new size_t[no_of_dimensions];

		this->to_jump_dimension_array[no_of_dimensions-1] = 1;

		for(long le = no_of_dimensions-2; le >= 0; le--)
		{
			this->to_jump_dimension_array[le] = this->to_jump_dimension_array[le+1] * this->dimension_array[le+1];
		}
	}

	~MVArray()
	{
		// Code
		if(this->to_jump_dimension_array)
		{
			delete[] to_jump_dimension_array;
		}

		if(this->data_array)
		{
			delete[] data_array;
		}

		if(this->dimension_array)
		{
			delete[] dimension_array;
		}
	}

	ret_t SetData(T data, ...)
	{
		// Code
		long* indices = new long[no_of_dimensions];

		va_list args;

		va_start(args, data);
		for(long le = 0; le < no_of_dimensions; le++)
		{
			indices[le] = va_arg(args, long);

			if(indices[le] >= dimension_array[le])
			{
				std::cerr << "ERROR: Index Out of Bound." << std::endl;
				delete[] indices;
				return(FAILURE);
			}
		}
		va_end(args);

		// Calculate Required Index
		long required_index = 0;
		for(long le = 0; le < no_of_dimensions; le++)
		{
			required_index = required_index + indices[le] * to_jump_dimension_array[le];
		}

		data_array[required_index] = data;

		delete[] indices;

		return(SUCCESS);
	}

	T GetData(...)
	{
		// Code
		long* indices = new long[no_of_dimensions];

		va_list args;

		va_start(args, this);
		for(long le = 0; le < no_of_dimensions; le++)
		{
			indices[le] = va_arg(args, long);

			if(indices[le] >= dimension_array[le])
			{
				std::cerr << "ERROR: Index Out of Bound." << std::endl;
				delete[] indices;
				return((T)0);
			}
		}
		va_end(args);

		// Calculate Required Index
		long required_index = 0;
		for(long le = 0; le < no_of_dimensions; le++)
		{
			required_index = required_index + indices[le] * to_jump_dimension_array[le];
		}

		T to_return_data = data_array[required_index];

		delete[] indices;

		return(to_return_data);
	}

	size_t GetDimensionSize(size_t index)const
	{
		// Code
		return(this->dimension_array[index]);
	}

	size_t GetSize()const
	{
		// Code
		return(this->no_of_elements);
	}

	T operator[](const long index)
	{
		// Code
		if(index >= no_of_elements)
		{
			std::cerr << "ERROR: Index Out of Bound." << std::endl;
			return((T)0);
		}

		return(data_array[index]);
	}

};

