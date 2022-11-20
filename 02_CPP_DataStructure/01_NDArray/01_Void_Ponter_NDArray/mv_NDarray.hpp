

#pragma once

// Constant Literals
#ifndef  	SUCCESS 
#define 	SUCCESS  	0
#endif

#ifndef  	FAILURE 
#define  	FAILURE  	1
#endif

// Type Definition
class MVArray; 	// Class Type Declaration

/*
typedef  	MVArray  	mv_array_t;
typedef  	MVArray*  	p_mv_array_t;
typedef  	MVArray** 	pp_mv_array_t	
*/

typedef  	void*  	data_t;
typedef  	int  	ret_t;

// Class Type Definition
/*
	Data Object : 	Class Data Member
	Function  	:  	Class Member Function
*/
class MVArray
{
private:
	data_t*  	data_array;
	size_t*  	dimension_array;
	size_t  	no_of_dimension;
	size_t*  	to_jump_dimension_array;

public:
	// Parameterizer Constructor
	MVArray(size_t no_of_dimension, ...);

	//Destructor
	~MVArray();

	// Setter Member Function
	ret_t  	SetData(data_t, ...);

	// Getter Member Function
	data_t 	GetData(...);

	// Get Size of Dimension
	size_t  GetDimensionSize(size_t index)const;
};

