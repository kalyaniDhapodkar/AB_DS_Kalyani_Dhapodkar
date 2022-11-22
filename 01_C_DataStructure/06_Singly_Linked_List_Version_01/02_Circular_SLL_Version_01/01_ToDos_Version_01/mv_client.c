/**
 * 	No of lines = 252 + 53 + 56 + 879 + 195 + 235 
 * 				= 1670
 */

//	Headers
#include	<stdio.h>
#include	<stdlib.h>
#include	<assert.h>

#include	"mv_scll.h"

//	Constant Literals

//	Macros

//	Global Function Declarations

//	Global Object Declarations/Definitions

p_mv_scll_t plist = NULL;

void print_long_data(data_t data)
{
	// Code
	fprintf(stdout, "{%lld}->", (long long)data);
}

ret_t compare_data(data_t data1, data_t data2)
{
	// Code
	if( (long long)data1 == (long long)data2 )
		return(SUCCESS);

	return(FAILURE);
}


int main(void)
{
	// Code

	plist = create_singly_circular_list();

	for(long le = 0; le < 10; ++le)
		mv_scll_insert_back(plist, (data_t)(long long)((le+1) * 12));

	fprintf(stdout, "\nAfter List insert back:\n");
	mv_scll_print_forward(plist, print_long_data);

	for(long le = 0; le < 10; ++le)
		mv_scll_insert_front(plist, (data_t)(long long)((le+1) * 27));

	fprintf(stdout, "\nAfter List insert front:\n");
	mv_scll_print_forward(plist, print_long_data);

	mv_scll_insert_at(plist, (data_t)(long long)(1234), 5);
	mv_scll_insert_at(plist, (data_t)(long long)(5678), 10);
	mv_scll_insert_at(plist, (data_t)(long long)(9087), 22);
	mv_scll_insert_at(plist, (data_t)(long long)(6534), 0);
	mv_scll_insert_at(plist, (data_t)(long long)(2190), 77);

	fprintf(stdout, "\nAfter List insert At Particular index:\n");
	mv_scll_print_forward(plist, print_long_data);

	mv_scll_insert_before(plist, (data_t)(long long)(1235), (data_t)(long)(1234), compare_data);
	mv_scll_insert_before(plist, (data_t)(long long)(9999), (data_t)(long)(5678), compare_data);
	mv_scll_insert_before(plist, (data_t)(long long)(2323), (data_t)(long)(9087), compare_data);
	mv_scll_insert_before(plist, (data_t)(long long)(5555), (data_t)(long)(6534), compare_data);
	mv_scll_insert_before(plist, (data_t)(long long)(8768), (data_t)(long)(2190), compare_data);

	fprintf(stdout, "\nAfter List insert Before:\n");
	mv_scll_print_forward(plist, print_long_data);

	mv_scll_insert_after(plist, (data_t)(long long)(2222), (data_t)(long)(1235), compare_data);
	mv_scll_insert_after(plist, (data_t)(long long)(1111), (data_t)(long)(9999), compare_data);
	mv_scll_insert_after(plist, (data_t)(long long)(6566), (data_t)(long)(2323), compare_data);
	mv_scll_insert_after(plist, (data_t)(long long)(82), (data_t)(long)(27), compare_data);
	mv_scll_insert_after(plist, (data_t)(long long)(2121), (data_t)(long)(120), compare_data);

	fprintf(stdout, "\nAfter List insert After:\n");
	mv_scll_print_forward(plist, print_long_data);


	fprintf(stdout, "Removed Front Data: %lld\n",(long long) mv_scll_remove_front(plist) );
	fprintf(stdout, "Removed Front Data: %lld\n",(long long) mv_scll_remove_front(plist) );
	fprintf(stdout, "Removed Front Data: %lld\n",(long long) mv_scll_remove_front(plist) );
	fprintf(stdout, "Removed Front Data: %lld\n",(long long) mv_scll_remove_front(plist) );

	fprintf(stdout, "\nAfter List Remove Front:\n");
	mv_scll_print_forward(plist, print_long_data);


	fprintf(stdout, "Removed Back Data: %lld\n",(long long) mv_scll_remove_back(plist) );
	fprintf(stdout, "Removed Back Data: %lld\n",(long long) mv_scll_remove_back(plist) );
	fprintf(stdout, "Removed Back Data: %lld\n",(long long) mv_scll_remove_back(plist) );
	fprintf(stdout, "Removed Back Data: %lld\n",(long long) mv_scll_remove_back(plist) );

	fprintf(stdout, "\nAfter List Remove Back:\n");
	mv_scll_print_forward(plist, print_long_data);


	fprintf(stdout, "Removed Back Data At %d: %lld\n", 0, (long long) mv_scll_remove_at(plist, 0) );
	fprintf(stdout, "Removed Back Data At %d: %lld\n", 12, (long long) mv_scll_remove_at(plist, 12) );
	fprintf(stdout, "Removed Back Data At %d: %lld\n", 5, (long long) mv_scll_remove_at(plist, 5) );
	fprintf(stdout, "Removed Back Data At %d: %lld\n", 99, (long long) mv_scll_remove_at(plist, 99) );

	fprintf(stdout, "\nAfter List Remove Data At:\n");
	mv_scll_print_forward(plist, print_long_data);


	fprintf(stdout, "Removed Back Data Before %lld: %lld\n", (long long)2222, (long long) mv_scll_remove_before(plist, (data_t)(long long)2222, compare_data) );
	fprintf(stdout, "Removed Back Data Before %lld: %lld\n", (long long)1111, (long long) mv_scll_remove_before(plist, (data_t)(long long)1111, compare_data) );
	fprintf(stdout, "Removed Back Data Before %lld: %lld\n", (long long)82, (long long) mv_scll_remove_before(plist, (data_t)(long long)82, compare_data) );
	fprintf(stdout, "Removed Back Data Before %lld: %lld\n", (long long)2121, (long long) mv_scll_remove_before(plist, (data_t)(long long)2121, compare_data) );
	fprintf(stdout, "Removed Back Data Before %lld: %lld\n", (long long)189, (long long) mv_scll_remove_before(plist, (data_t)(long long)189, compare_data) );

	fprintf(stdout, "\nAfter List Remove Data Before:\n");
	mv_scll_print_forward(plist, print_long_data);

	fprintf(stdout, "Removed Back Data After %lld: %lld\n", (long long)120, (long long) mv_scll_remove_after(plist, (data_t)(long long)120, compare_data) );
	fprintf(stdout, "Removed Back Data After %lld: %lld\n", (long long)108, (long long) mv_scll_remove_after(plist, (data_t)(long long)108, compare_data) );
	fprintf(stdout, "Removed Back Data After %lld: %lld\n", (long long)82, (long long) mv_scll_remove_after(plist, (data_t)(long long)82, compare_data) );
	fprintf(stdout, "Removed Back Data After %lld: %lld\n", (long long)60, (long long) mv_scll_remove_after(plist, (data_t)(long long)60, compare_data) );
	fprintf(stdout, "Removed Back Data After %lld: %lld\n", (long long)1234, (long long) mv_scll_remove_after(plist, (data_t)(long long)1234, compare_data) );

	fprintf(stdout, "\nAfter List Remove Data After:\n");
	mv_scll_print_forward(plist, print_long_data);

	fprintf(stdout, "Size = %zd:\n", mv_scll_get_size(plist));

	fprintf(stdout, "List Forward Print:\n");
	mv_scll_print_forward(plist, print_long_data);
	
	fprintf(stdout, "List Reverse Print:\n");
	mv_scll_print_reverse(plist, print_long_data);

	mv_scll_destroy(&plist, print_long_data);

	exit(SUCCESS);
}