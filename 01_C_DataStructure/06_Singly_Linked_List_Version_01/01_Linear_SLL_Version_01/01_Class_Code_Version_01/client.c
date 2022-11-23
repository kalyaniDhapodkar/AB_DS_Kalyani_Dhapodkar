

//	Headers
#include	<stdio.h>
#include	<stdlib.h>
#include	<assert.h>

#include	"mv_singly_list.h"

p_mv_sll_t plist = NULL;

print_long_data(data_t data)
{
	// Code
	fprintf(stdout, "{%lld}->", (long long)data);
}

int main(void)
{
	// Code

	plist = create_singly_list();

	for(long le = 0; le < 10; ++le)
		mv_sll_insert_back(plist, (data_t)(long long)((le+1) * 12));

	fprintf(stdout, "After List insert back:\n");
	mv_sll_print_forward(plist, print_long_data);

	for(long le = 0; le < 10; ++le)
		mv_sll_insert_front(plist, (data_t)(long long)((le+1) * 27));

	fprintf(stdout, "After List insert front:\n");
	mv_sll_print_forward(plist, print_long_data);

	mv_sll_destroy(&plist, print_long_data);

	exit(SUCCESS);
}