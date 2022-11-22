

/**
 * @file	client.c
 * @author	MarshallingVoid	(marshallingvoid@gmail.com)
 * @brief	This file contains the client side usage of DOUBLY CIRCULAR LINKED LIST
 * @date	06/11/2022
 * @version	1.0
 * 
 * @copyright	Copyrights (c) 2022
 */

// 	Headers
#include	<stdio.h>
#include	<stdlib.h>
#include	<string.h>

#include	"mv_dcll.h"

#define		NEW_LINE		(fprintf(stdout, "\n\n"))

p_mv_dcll_t	plist = NULL;

void print_long_data(data_t data)
{
	// Code
	fprintf(stdout, "{%lld}->", (long long)data);
}

int main(void)
{
	// Code
	plist = create_doubly_circular_list();

	NEW_LINE;

	for( int le = 1; le <= 20; ++le  )
	{
		mv_dcll_insert_back( plist, (data_t)(long long)( le * 13 ) );
	} 
	
	fprintf(stdout, "DCLL After List Insert Front:\n");
	mv_dcll_print_forward(plist, print_long_data);
	mv_dcll_print_reverse(plist, print_long_data);
	
	NEW_LINE;
	
	for( int le = 1; le <= 20; ++le  )
	{
		mv_dcll_insert_front( plist, (data_t)(long long)( le * 59 ) );
	} 
	
	fprintf(stdout, "DCLL After List Insert Front:\n");
	mv_dcll_print_forward(plist, print_long_data);
	mv_dcll_print_reverse(plist, print_long_data);

	NEW_LINE;
	
	mv_dcll_insert_at(plist, (data_t)(long long)(12345), 0);
	mv_dcll_insert_at(plist, (data_t)(long long)(56789), 5);
	mv_dcll_insert_at(plist, (data_t)(long long)(90123), 12);
	mv_dcll_insert_at(plist, (data_t)(long long)(128934), 18);
	mv_dcll_insert_at(plist, (data_t)(long long)(98763412), 22);
	mv_dcll_insert_at(plist, (data_t)(long long)(123123123), 99);
	
	fprintf(stdout, "DCLL After List Insert At:\n");
	mv_dcll_print_forward(plist, print_long_data);
	mv_dcll_print_reverse(plist, print_long_data);

	// HW: Use and Call the rest of the functions here

	mv_dcll_destroy(&plist, print_long_data);

	exit(EXIT_SUCCESS);
}
