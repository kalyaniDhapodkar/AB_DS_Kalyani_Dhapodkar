

// Headers
#include <stdio.h>
#include <stdlib.h>

#include "mv_dcll.h"
#include "mv_insertion_sort.h"

void showdata(data_t data)
{
	fprintf(stdout, "{%lld}-", (long long)data);
}

ret_t compare(data_t data1, data_t data2)
{
	if(data1 < data2)
		return(TRUE);

	return(FALSE);
}

int main(void)
{
	p_mv_dcll_t List1 = create_doubly_circular_list();

	for(long long le = 10; le > 0; le--)
	{
		mv_dcll_insert_back(List1, (data_t)le);
	}

	mv_dcll_print_forward(List1, showdata);

	InsertionSort(mv_dcll_get_head(List1), mv_dcll_get_head(List1)->p_next->p_next/*mv_dcll_get_tail(List1)*/, compare);

	mv_dcll_print_forward(List1, showdata);

	exit(0);
}

