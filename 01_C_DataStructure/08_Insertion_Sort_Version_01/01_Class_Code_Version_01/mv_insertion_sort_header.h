

/**
 * @file	mv_insertion_sort.h
 * @author	MarshallingVoid	(marshallingvoid@gmail.com)
 * @breif	The interface function declaration for Generic Insertion Sort function implementation
 * @date	29/11/2022
 * @version	1.0
 * 
 * @copyright	Copyright (c) 2022
 */

#ifndef  	_MV_INSERTION_SORT_H
#define  	_MV_INSERTION_SORT_H

#ifndef  	SUCCESS 	
#define  	SUCCESS  	0
#endif

#ifndef  	FAILURE
#define  	FAILURE  	1
#endif

// Typedef
typedef  	void*  	data_t;
typedef  	int   	ret_t;

typedef  	ret_t(*COMPAREDATAPROC)(data_t, data_t);

// Interface Function Declarations

extern ret_t 	mv_insertion_sort( data_t* array, long long array_size, COMPAREDATAPROC pcompareproc);

#endif  	/* _MV_INSERTION_SORT_H */

