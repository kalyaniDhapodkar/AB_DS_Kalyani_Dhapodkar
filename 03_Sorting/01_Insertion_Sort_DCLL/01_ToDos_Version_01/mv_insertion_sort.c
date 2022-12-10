

// Headers
#include "mv_insertion_sort.h"
#include "mv_dcll.h"

extern void  	InsertionSort(p_node_t one, p_node_t two, COMPARE pcompare)
{
	// Code
	p_node_t first = one;
	p_node_t last = two->p_next;

	p_node_t prunner1 = first->p_next;
	for( ; prunner1 != last; prunner1 = prunner1->p_next)
	{
		data_t data = prunner1->key;

		p_node_t prunner2 = prunner1->p_prev;
		while(prunner2 != first->p_prev && pcompare(data, prunner2->key))
		{
			prunner2->p_next->key = prunner2->key;
			prunner2 = prunner2->p_prev;
		}

		prunner2->p_next->key = data;
	}

	printf("3\n");
}

