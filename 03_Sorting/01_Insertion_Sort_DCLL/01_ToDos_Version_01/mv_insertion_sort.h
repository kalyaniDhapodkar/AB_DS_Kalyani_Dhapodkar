

#ifndef  	_MV_INSERTION_SORT_H
#define  	_MV_INSERTION_SORT_H

// Headers
#include "mv_dcll.h"

// Typedefs
typedef  	void* 	data_t;
typedef  	int  	ret_t;

typedef  	ret_t (*COMPARE)(data_t, data_t);

// Interface Function
extern void  	InsertionSort(p_node_t first, p_node_t last, COMPARE pcompare);

#endif  	/* _MV_INSERTION_SORT_H  */
