

/**
 * @file	mv_insertion_sort_server.c
 * @author	MarshallingVoid	(marshallingvoid@gmail.com)
 * @breif	The interface function definition for Generic Insertion Sort.
 * @date	29/11/2022
 * @version	1.0
 * 
 * @copyright	Copyright (c) 2022
 */

#include <stdio.h>
#include <stdlib.h>

#include "mv_insertion_sort_header.h"

// Insertion Sort Helper Function
static void assign_value(char* dest, char* src, size_t no_of_bytes)
{
    // Code
    for(size_t le = 0; le < no_of_bytes; le++)
    {
        dest[le] = src[le];
    }
}

// Insertion Sort Interface Function
extern ret_t  mv_insertion_sort(data_t* array,
                                long long array_size,
                                size_t element_size,
                                COMPAREDATAPROC pcompareproc)
{
    // Code
    for(long long ole = 1; ole < array_size; ++ole)
    {
        void* key = malloc(element_size);

        void* source_address_from_array = (((char*)array) + ole * element_size);
        assign_value(key, source_address_from_array, element_size);

        long long ile = ole-1;

        while(ile >- 0 && SUCCESS == pcompareproc((((char*)array) + ile * element_size), key) )
        {
            void* dest = (((char*)array) +(ile+1) * element_size);
            void* src = (((char*)array) + ile * element_size);

            assign_value(dest, src, element_size);

            ile--;
        }

        assign_value((((char*)array) + (ile+1) * element_size), key, element_size);

        if(key)
        {
            free(key);
            key = NULL;
        }
    }

    return(SUCCESS);
}


