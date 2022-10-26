
//  Headers
#include <stdio.h>
#include <stdlib.h>

#include "deque.h"

//  Macros

#define NEW_LINE (fprintf(stdout, "\n\n"))

// typedefinition

struct Demo;

typedef struct Demo demo_t;
typedef struct Demo* p_demo_t;
typedef struct Demo** pp_demo_t;

struct Demo
{
    int inum1;
    long lnum2;
    char ch;
};
#define SIZE_DEMO (sizeof(demo_t))

p_mv_dequeue_t pdequeue_long = NULL;
p_mv_dequeue_t pdequeue_demo = NULL;

// Demo interface functions

static p_demo_t create_demo_object(int inum, long lnum, char ch)
{
    //  Code
    p_demo_t pdemo = (p_demo_t)malloc(SIZE_DEMO);

    if (NULL == pdemo)
    {
        fprintf(stderr, "ERROR: Out Of Memory.\n");
        exit(FAILURE);
    }
    pdemo->inum1 = inum;
    pdemo->lnum2 = lnum;
    pdemo->ch = ch;

    return (pdemo);
}

// Print Data and Delete Data Callbacks

void print_data_long(data_t data)
{
    // Code
    fprintf(stdout, "{%lld}-", (long long)data);
}

void delete_data_long(data_t data)
{
    // Code
    fprintf(stdout, "Deleting - %lld\n", (long long)data);
}

void print_data_demo(data_t data)
{
    // Code
    p_demo_t pdemo = (p_demo_t)data;

    fprintf(stdout, "{ %d | %ld | %c} -- ", pdemo->inum1, pdemo->lnum2, pdemo->ch);
}

void delete_data_demo(data_t data)
{
    // Code
    p_demo_t pdemo = (p_demo_t)data;

    fprintf(stdout, " Deleting = { %d | %ld | %c}\n", pdemo->inum1, pdemo->lnum2, pdemo->ch);

    free(pdemo);
    pdemo = NULL;
}

//  Entry Point Function

int main(void)
{
    // Code
    /***************************************\
     *      Dequeue for Long                *
    \***************************************/

    pdequeue_long = create_default_dequeue();

    // Add Data to back of Dequeue
    fprintf(stdout, "Enqueue Back:\n");
    for (long le = 0; le < 100; ++le)
    {
        mv_dequeue_enqueue_back(pdequeue_long, (data_t)(long long)((le + 1) * 10));
    }
    mv_dequeue_print_data(pdequeue_long, print_data_long);

    NEW_LINE;

    //  Dequeue from front of Dequeue
    fprintf(stdout, "Dequeue Front:\n");
    for (long le = 0; le < 10; ++le)
    {
        fprintf(stdout, "Dequeue Front data:");
        print_data_long(mv_dequeue_dequeue_front(pdequeue_long));
        fprintf(stdout, "\n");
    }
    mv_dequeue_print_data(pdequeue_long, print_data_long);

    NEW_LINE;

    // Add Data to front of Dequeue
    fprintf(stdout, "Enqueue Front:\n");
    for (long le = 0; le < 100; ++le)
    {
        mv_dequeue_enqueue_front(pdequeue_long, (data_t)(long long)((le + 1) * 4));
    }
    mv_dequeue_print_data(pdequeue_long, print_data_long);

    NEW_LINE;

    //  Dequeue from back of Dequeue
    fprintf(stdout, "Dequeue Back:\n");
    for (long le = 0; le < 10; ++le)
    {
        fprintf(stdout, "Dequeue Back data:");
        print_data_long(mv_dequeue_dequeue_back(pdequeue_long));
        fprintf(stdout, "\n");
    }
    mv_dequeue_print_data(pdequeue_long, print_data_long);

    NEW_LINE;

    //  Destroy Dequeue of long
    mv_dequeue_destroy(&pdequeue_long, delete_data_long);

    NEW_LINE;

    /***************************************\
     *     Dequeue for Struct Demo         *
    \***************************************/

    NEW_LINE;

    pdequeue_demo = create_default_dequeue();

    fprintf(stdout, "Enqueue Back:\n");
    for (long le = 0; le < 10; ++le)
    {
        p_demo_t pdemo = create_demo_object(le * 3, (le + 1) * 97, 'A' + le);
        mv_dequeue_enqueue_back(pdequeue_demo, pdemo);
    }
    mv_dequeue_print_data(pdequeue_demo, print_data_demo);
    NEW_LINE;

    fprintf(stdout, "Dequeue Back:\n");
    for (long le = 0; le < 5; ++le)
    {
        p_demo_t pdemo = mv_dequeue_dequeue_back(pdequeue_demo);
        delete_data_demo(pdemo);
        pdemo = NULL;
    }
    mv_dequeue_print_data(pdequeue_demo, print_data_demo);
    NEW_LINE;

    fprintf(stdout, "Enqueue Front:\n");
    for (long le = 0; le < 10; ++le)
    {
        p_demo_t pdemo = create_demo_object(le * 14, (le + 1) * 63, 'z' - le);
        mv_dequeue_enqueue_front(pdequeue_demo, pdemo);
    }
    mv_dequeue_print_data(pdequeue_demo, print_data_demo);
    NEW_LINE;

    fprintf(stdout, "Dequeue Front:\n");
    for (long le = 0; le < 5; ++le)
    {
        p_demo_t pdemo = mv_dequeue_dequeue_front(pdequeue_demo);
        delete_data_demo(pdemo);
        pdemo = NULL;
    }
    mv_dequeue_print_data(pdequeue_demo, print_data_demo);
    NEW_LINE;

    mv_dequeue_destroy(&pdequeue_demo, delete_data_demo);

    NEW_LINE;

    exit(SUCCESS);
}
