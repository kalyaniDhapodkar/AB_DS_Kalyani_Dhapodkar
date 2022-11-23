

/**
 * @file    client.c
 * @author  MarshallingVoid (marshallingvoid@gmail.com)
 * @brief   This file contains the client side usage of DOUBLY CIRCULAR LINKED LIST
 * @date    06/11/2022
 * @version 1.0
 * 
 * @copyright   Copyrights (c) 2022
 */

//  Headers
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>

#include    "mv_dll.h"

#define     NEW_LINE        (fprintf(stdout, "\n\n"))

p_mv_dll_t plist = NULL;

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
    plist = create_doubly_list();

    NEW_LINE;

    for( int le = 1; le <= 20; ++le  )
    {
        mv_dll_insert_back( plist, (data_t)(long long)( le * 13 ) );
    } 
    
    fprintf(stdout, "\nDLL After List Insert Back:\n");
    mv_dll_print_forward(plist, print_long_data);
    mv_dll_print_reverse(plist, print_long_data);
    
    NEW_LINE;
    
    for( int le = 1; le <= 20; ++le  )
    {
        mv_dll_insert_front( plist, (data_t)(long long)( le * 59 ) );
    } 
    
    fprintf(stdout, "\nDLL After List Insert Front:\n");
    mv_dll_print_forward(plist, print_long_data);
    mv_dll_print_reverse(plist, print_long_data);

    NEW_LINE;
    
    mv_dll_insert_at(plist, (data_t)(long long)(12345), 0);
    mv_dll_insert_at(plist, (data_t)(long long)(56789), 5);
    mv_dll_insert_at(plist, (data_t)(long long)(90123), 12);
    mv_dll_insert_at(plist, (data_t)(long long)(128934), 18);
    mv_dll_insert_at(plist, (data_t)(long long)(98763412), 22);

    NEW_LINE;

    fprintf(stdout, "DLL After List Insert At:\n");
    mv_dll_print_forward(plist, print_long_data);
    mv_dll_print_reverse(plist, print_long_data);

    mv_dll_insert_before(plist, (data_t)(long long)(1111), (data_t)(long long)(12345), compare_data);
    mv_dll_insert_before(plist, (data_t)(long long)(2222), (data_t)(long long)(1003), compare_data);
    mv_dll_insert_before(plist, (data_t)(long long)(3333), (data_t)(long long)(234), compare_data);
    mv_dll_insert_before(plist, (data_t)(long long)(4444), (data_t)(long long)(78), compare_data);
    mv_dll_insert_before(plist, (data_t)(long long)(5555), (data_t)(long long)(9999), compare_data);

    NEW_LINE;

    fprintf(stdout, "DLL After List Insert Before:\n");
    mv_dll_print_forward(plist, print_long_data);
    mv_dll_print_reverse(plist, print_long_data);

    mv_dll_insert_after(plist, (data_t)(long long)(6666), (data_t)(long long)(12345), compare_data);
    mv_dll_insert_after(plist, (data_t)(long long)(7777), (data_t)(long long)(1003), compare_data);
    mv_dll_insert_after(plist, (data_t)(long long)(8888), (data_t)(long long)(234), compare_data);
    mv_dll_insert_after(plist, (data_t)(long long)(9999), (data_t)(long long)(78), compare_data);
    mv_dll_insert_after(plist, (data_t)(long long)(9191), (data_t)(long long)(9999), compare_data);

    NEW_LINE;

    fprintf(stdout, "DLL After List Insert After:\n");
    mv_dll_print_forward(plist, print_long_data);
    mv_dll_print_reverse(plist, print_long_data);

    mv_dll_remove_front(plist);
    mv_dll_remove_front(plist);
    mv_dll_remove_front(plist);

    NEW_LINE;

    fprintf(stdout, "DLL After List Remove Front:\n");
    mv_dll_print_forward(plist, print_long_data);
    mv_dll_print_reverse(plist, print_long_data);

    mv_dll_remove_back(plist);
    mv_dll_remove_back(plist);
    mv_dll_remove_back(plist);

    NEW_LINE;

    fprintf(stdout, "DLL After List Remove Back:\n");
    mv_dll_print_forward(plist, print_long_data);
    mv_dll_print_reverse(plist, print_long_data);

    mv_dll_remove_at(plist,  0);
    mv_dll_remove_at(plist,  5);
    mv_dll_remove_at(plist,  12);
    mv_dll_remove_at(plist,  18);
    mv_dll_remove_at(plist,  22);
    mv_dll_remove_at(plist,  99);

    NEW_LINE;

    fprintf(stdout, "DLL After List Remove At:\n");
    mv_dll_print_forward(plist, print_long_data);
    mv_dll_print_reverse(plist, print_long_data);
    
    mv_dll_remove_before(plist, (data_t)(long long)(1111), compare_data);
    mv_dll_remove_before(plist, (data_t)(long long)(2222), compare_data);
    mv_dll_remove_before(plist, (data_t)(long long)(3333),  compare_data);
    mv_dll_remove_before(plist, (data_t)(long long)(4444),  compare_data);
    mv_dll_remove_before(plist, (data_t)(long long)(5555),  compare_data);

    NEW_LINE;

    fprintf(stdout, "DLL After List Remove Before:\n");
    mv_dll_print_forward(plist, print_long_data);
    mv_dll_print_reverse(plist, print_long_data);

    mv_dll_remove_after(plist, (data_t)(long long)(1111), compare_data);
    mv_dll_remove_after(plist, (data_t)(long long)(2222), compare_data);
    mv_dll_remove_after(plist, (data_t)(long long)(3333),  compare_data);
    mv_dll_remove_after(plist, (data_t)(long long)(4444),  compare_data);
    mv_dll_remove_after(plist, (data_t)(long long)(5555),  compare_data);

    NEW_LINE;

    fprintf(stdout, "DLL After List Remove After:\n");
    mv_dll_print_forward(plist, print_long_data);
    mv_dll_print_reverse(plist, print_long_data);


    mv_dll_destroy(&plist, print_long_data);

    exit(EXIT_SUCCESS);
}
