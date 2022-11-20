

#ifndef 	_ND_ARRAY_H
#define 	_ND_ARRAY_H

// Constant Literals
#ifndef 		SUCCESS 
#define  	SUCCESS 	0
#endif

#ifndef  	FAILURE
#define  	FAILURE 	1
#endif

// Type definitions
struct array;

typedef  	struct array 	array_t;
typedef  	struct array* 	p_array_t;
typedef  	struct array** 	pp_array_t;

typedef   	void*  			data_t;
typedef   	data_t*  		p_data_t;
typedef  	long*   		p_dimension_t;
typedef  	int 			ret_t;

// Structure Type Definition
struct array
{
	p_data_t ptr; 	// actual array
	size_t   no_of_dimensions; // total no of dimensions
	p_dimension_t  	 pdimension;  // array for storing size of each dimension
	size_t*  to_jump_dimension; 
};
#define  	SIZE_ARRAY  	sizeof(array_t)

// ND Array Interface Functions

extern  p_array_t 	create_array(size_t no_of_dimensions, ...);
extern 	ret_t  		array_set_data(p_array_t parray, data_t data, ...);
extern 	data_t 		array_get_data(p_array_t parray, ...);
extern  long  		array_get_size_of_dimension(p_array_t parray, long index);
extern  ret_t  		array_destroy(pp_array_t pparray);

#endif 		/* _ND_ARRAY_H */

