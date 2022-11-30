

// /**
//  * @file	mv_client.c
//  * @author	MarshallingVoid	(marshallingvoid@gmail.com)
//  * @breif	The Client implementation to use the Generic InsertionSort.
//  * @date	29/11/2022
//  * @version	1.0
//  * 
//  * @copyright	Copyright (c) 2022
//  */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "mv_insertion_sort_header.h"

#define     NEW_LINE    fprintf(stdout, "\n\n")

struct Demo
{
    long long llnum1;
    long long llnum2;
    long long llnum3;
    long long llnum4;
    long long llnum5;
    int inum;
    char ch;
};

struct Demo* darr = NULL;

ret_t  compare_proc(data_t data1, data_t data2)
{
    // Code

    // Sorting Condition
    if( ((struct Demo*)data1)->llnum1 > ((struct Demo*)data2)->llnum1 ||
        ((struct Demo*)data1)->inum > ((struct Demo*)data2)->inum ||
        ((struct Demo*)data1)->ch > ((struct Demo*)data2)->ch)
        return(SUCCESS);

    return(FAILURE);
}

int main(void)
{
    // Code
    srand(time(0));

    long long no_of_elements = 20;

    darr = (struct Demo*) calloc(no_of_elements, sizeof(struct Demo));

    for( long long le = 0; le < no_of_elements; le++)
    {
        darr[le].llnum1 = 1 + rand() % 20;
        darr[le].llnum2 = 1 + rand() % 20;
        darr[le].llnum3 = 1 + rand() % 20;
        darr[le].llnum4 = 1 + rand() % 20;
        darr[le].llnum5 = 1 + rand() % 20;
        darr[le].inum = 1 + rand() % 50;
        darr[le].ch = 65 + rand() % 26;
    }

    clock_t start = clock();
    mv_insertion_sort((data_t*)darr, no_of_elements, sizeof(struct Demo), compare_proc);
    clock_t end = clock();

    double time_for_sorting = ( (double)(end - start) ) / CLOCKS_PER_SEC;

    fprintf(stdout, "Time of Sorting: %lf\n", time_for_sorting);

    NEW_LINE;

    fprintf(stdout, "After Sort:\n");
    fprintf(stdout, "No Of Elements: %lld\n", no_of_elements);
    fprintf(stdout, "[START]\n");
    for( long long le = 0; le < no_of_elements; ++le )
    {
        fprintf(stdout, 
                "[%lld | %lld | %lld | %lld | %lld | %d | %c]\n", 
                darr[le].llnum1, 
                darr[le].llnum2, 
                darr[le].llnum3, 
                darr[le].llnum4, 
                darr[le].llnum5, 
                darr[le].inum, 
                darr[le].ch);
    }
    fprintf(stdout, "[END]");

    NEW_LINE;

    if( darr )
    {
        free(darr);
        darr = NULL;
    }

    exit(EXIT_SUCCESS);
}


