

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

	mv_sll_insert_at(plist, (data_t)(long long)1234, 0);
	mv_sll_insert_at(plist, (data_t)(long long)2345, 4);
	mv_sll_insert_at(plist, (data_t)(long long)3456, 22);
	mv_sll_insert_at(plist, (data_t)(long long)3456, 99);

	fprintf(stdout, "After List insert At:\n");
	mv_sll_print_forward(plist, print_long_data);

	mv_sll_insert_before(plist, (data_t)(long long)1111, (data_t)(long long)1234);
	mv_sll_insert_before(plist, (data_t)(long long)2222, (data_t)(long long)2345);
	mv_sll_insert_before(plist, (data_t)(long long)3333, (data_t)(long long)3456);

	fprintf(stdout, "After List insert Before:\n");
	mv_sll_print_forward(plist, print_long_data);

	mv_sll_insert_after(plist, (data_t)(long long)1111, (data_t)(long long)1234);
	mv_sll_insert_after(plist, (data_t)(long long)2222, (data_t)(long long)2345);
	mv_sll_insert_after(plist, (data_t)(long long)3333, (data_t)(long long)3456);

	fprintf(stdout, "After List insert After:\n");
	mv_sll_print_forward(plist, print_long_data);

	mv_sll_remove_front(plist);
	mv_sll_remove_front(plist);
	mv_sll_remove_front(plist);
	mv_sll_remove_front(plist);

	fprintf(stdout, "After List Remove Front:\n");
	mv_sll_print_forward(plist, print_long_data);

	mv_sll_remove_back(plist);
	mv_sll_remove_back(plist);
	mv_sll_remove_back(plist);
	mv_sll_remove_back(plist);

	fprintf(stdout, "After List Remove Back:\n");
	mv_sll_print_forward(plist, print_long_data);

	mv_sll_remove_at(plist, 0);
	mv_sll_remove_at(plist, 99);
	mv_sll_remove_at(plist, 19);
	mv_sll_remove_at(plist, 15);

	fprintf(stdout, "After List Remove At:\n");
	mv_sll_print_forward(plist, print_long_data);

	mv_sll_remove_before(plist, (data_t)(long long)3456);
	mv_sll_remove_before(plist, (data_t)(long long)189);
	mv_sll_remove_before(plist, (data_t)(long long)12);
	mv_sll_remove_before(plist, (data_t)(long long)216);

	fprintf(stdout, "After List Remove Before:\n");
	mv_sll_print_forward(plist, print_long_data);

	mv_sll_remove_after(plist, (data_t)(long long)3456);
	mv_sll_remove_after(plist, (data_t)(long long)189);
	mv_sll_remove_after(plist, (data_t)(long long)12);
	mv_sll_remove_after(plist, (data_t)(long long)96);

	fprintf(stdout, "After List Remove After:\n");
	mv_sll_print_forward(plist, print_long_data);

	mv_sll_destroy(&plist, print_long_data);

	exit(SUCCESS);
}