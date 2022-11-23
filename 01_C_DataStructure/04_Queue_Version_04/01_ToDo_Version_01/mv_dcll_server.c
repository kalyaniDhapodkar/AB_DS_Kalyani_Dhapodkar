/**
 * @file    mv_dcll_server.c
 * @author  MarshalligVoid  (marshalligvoid@gmail.com)
 * @brief   This file is the implemention/definition of all the interface functions and helper functions
 *          required to implement DOUBLY CIRCULAR LINKED LIST
 * @date    23/11/2022
 * @version 1.0
 * 
 * @copyright   Copyrights (c) 2022
 */

//  Headers
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>

#include    "mv_dcll_header.h"

//  Global Function Declarations
static  ret_t   error_checking( const int assert_condition,
                                const char* assert_condition_str,
                                const char* file_name,
                                const long  line_no,
                                const int error_condition,
                                const char* error_condition_str,
                                void*(*error_handler)(void*),
                                void* error_handler_params);

static p_node_t create_node(data_t new_data);

static void* exit_program(void* param);

// Constant Literals and Macros

#define     CHECK_LIST      0x00000001
#define     CHECK_EMPTY     0x00000002

#define     CHECK_LIST_EMPTY    CHECK_LIST | CHECK_EMPTY

#define ERROR_CHECKING(assert_condition, error_condition, error_condition_str, error_handler, error_handler_params)     \
    (                                           \
        error_checking( assert_condition,       \
                        #assert_condition,      \
                        __FILE__,               \
                        __LINE__,               \
                        error_condition,        \
                        error_condition_str,    \
                        error_handler,          \
                        error_handler_params)   \
    )

#define ASSERTION(assert_condition)             \
    (                                           \
        error_checking( assert_condition,       \
                        #assert_condition,      \
                        __FILE__,               \
                        __LINE__,               \
                        0,                      \
                        NULL,                   \
                        exit_program,           \
                        NULL)                   \
    )

#define     CREATE_NODE(new_node, new_data, exit_program)   \
                    {                                       \
                        new_node = create_node(new_data);   \
                                                            \
                        ERROR_CHECKING( NULL != new_node,   \
                                        0,                  \
                                        NULL,               \
                                        exit_program,       \
                                        NULL);              \
                    }

#define     RETURN_FAILURE(status)  { if(FAILURE == status) {return(FAILURE);} }

#define     RETURN_NULL(status)  { if(FAILURE == status) {return(NULL);} }


//  List Helper Functions

static void* Xmalloc(size_t no_of_bytes)
{
    // Code
    void* p = malloc(no_of_bytes);
        
    ERROR_CHECKING( 0,
                    NULL == p,
                    "ERROR: Out Of Memory",
                    exit_program,
                    NULL);

    return(p);
} 

static  ret_t   error_checking( const int assert_condition,
                                const char* assert_condition_str,
                                const char* file_name,
                                const long  line_no,
                                const int error_condition,
                                const char* error_condition_str,
                                void*(*error_handler)(void*),
                                void* error_handler_params)
{
    // Code

    ret_t status;

    #ifdef DEBUG
        // Assertion
        if( !assert_condition )
        {
            fprintf(stderr, "Assertion Failed: %s, File %s, Line No %ld", assert_condition_str, file_name, line_no);
            fprintf(stderr, "\n");
            status = FAILURE;
        }
    #else
        // Error Checking
        if( error_condition )
        {
            if(error_condition_str)
            {
                fprintf(stderr, error_condition_str);
                fprintf(stderr, "\n");
            }

            status = FAILURE;
        }
    #endif

    if( FAILURE == status   &&
        NULL != error_handler )
    {
        error_handler(error_handler_params);
    }

    return(status);
}

static void* exit_program(void* param)
{
    // Code
    exit(FAILURE);

    return(NULL);
}

// static Node Creation Function
static p_node_t create_node(data_t new_data)
{
    // Code
    p_node_t new_node = (p_node_t)Xmalloc(SIZE_NODE);

    if( NULL == new_node )
        return(new_node);

    new_node->key = new_data;

    new_node->p_next = new_node;
    new_node->p_prev = new_node;

    return(new_node);
}

// Static List Creation Function
static p_mv_dcll_t create_list(void)
{
    // Code

    //  Create new DCLL
    p_mv_dcll_t plist = (p_mv_dcll_t)Xmalloc(SIZE_DCLL);

    if( NULL == plist )
        return(plist);

    p_node_t sentinel = NULL;

    CREATE_NODE(sentinel, NULL, exit_program);

    plist->p_head = sentinel;
    plist->p_tail = sentinel;
    plist->size = 0;

    return(plist);
}

// Static Generic Insert Function
static ret_t mv_dcll_generic_insert(p_mv_dcll_t plist, p_node_t first,  p_node_t mid, p_node_t last)
{
    //  Code

    mid->p_prev = first;
    mid->p_next = last;

    first->p_next = mid;
    last->p_prev = mid;

    plist->p_tail = plist->p_head->p_prev;

    plist->size++;

    return(SUCCESS);
}

// Static Generic Removal Function
static data_t mv_dcll_generic_remove(p_mv_dcll_t plist, p_node_t d_node)
{
    // Code
    p_node_t prev_node = d_node->p_prev;
    p_node_t next_node = d_node->p_next;

    prev_node->p_next = next_node;
    next_node->p_prev = prev_node;

    d_node->p_next = NULL;
    d_node->p_prev = NULL;

    data_t to_return_data = d_node->key;

    free(d_node);
    d_node = NULL;

    plist->size--;

    plist->p_tail = plist->p_head->p_prev;

    return(to_return_data);
}

// Static List Checking Function
static ret_t check_list_conditions(p_mv_dcll_t plist, int conditions)
{
    // Code
    if( CHECK_LIST & conditions )
    {
        RETURN_FAILURE( ERROR_CHECKING( 1,
                                        NULL == plist,
                                        "ERROR: List not found",
                                        NULL,
                                        NULL) );
    }

    if( CHECK_EMPTY & conditions )
    {
        RETURN_FAILURE( ERROR_CHECKING( 1,
                                        plist->p_head == plist->p_tail,
                                        "ERROR: List is empty",
                                        NULL,
                                        NULL) ); 
    }

    return(SUCCESS);
}

//  List Interface Functions

// List Creation Function
extern p_mv_dcll_t  create_doubly_circular_list()
{
    // Code 
    return( create_list() );
}

//  List Data Insertion Functions

// List Insetion Data Node In Front
extern ret_t mv_dcll_insert_back(p_mv_dcll_t plist, data_t new_data)
{
    // Code
    #ifdef  DEBUG
    ASSERTION( NULL != plist );
    #endif

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST) );

    p_node_t new_node = NULL;

    CREATE_NODE(new_node, new_data, exit_program);

    return( mv_dcll_generic_insert(plist, plist->p_tail, new_node, plist->p_tail->p_next ) );
}

// List Insertion Data Node at the back of list
extern ret_t mv_dcll_insert_front(p_mv_dcll_t plist, data_t new_data)
{
    // Code
    #ifdef  DEBUG
    ASSERTION( NULL != plist );
    #endif

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST) );

    p_node_t new_node = NULL;

    CREATE_NODE(new_node, new_data, exit_program);

    return( mv_dcll_generic_insert(plist, plist->p_head, new_node, plist->p_head->p_next) );
}

// List Insertion Data Node at the specific index/position
extern ret_t mv_dcll_insert_at(p_mv_dcll_t plist, data_t new_data, size_t index)
{
    //  Code
    #ifdef DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    if( 0 == index )
        return( mv_dcll_insert_front(plist, new_data) );
    else if( index == plist->size )
        return( mv_dcll_insert_back(plist, new_data) );


    RETURN_FAILURE( ERROR_CHECKING( index < plist->size,
                                    index > plist->size,
                                    "ERROR: Index Out Of Bound.",
                                    NULL,
                                    NULL) ); 

    p_node_t prunner = plist->p_head;

    for( size_t le = 0; le < index; ++le)
        prunner = prunner->p_next;

    p_node_t new_node = NULL;

    CREATE_NODE(new_node, new_data, exit_program);

    return( mv_dcll_generic_insert(plist, prunner, new_node, prunner->p_next ) );
}
 
 // List Insertion Data Node before the given data 
extern ret_t mv_dcll_insert_before(p_mv_dcll_t plist, data_t new_data, data_t e_data, COMPAREDATAPROC  pcomparedataproc)
{
    // Code

    #ifdef  DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    RETURN_FAILURE( ERROR_CHECKING( NULL != pcomparedataproc,
                                    NULL == pcomparedataproc,
                                    "ERROR: Compare Callback must not be NULL",
                                    NULL,
                                    NULL) ); 

    p_node_t prunner = plist->p_head->p_next;

    while(1)
    {
        RETURN_FAILURE( ERROR_CHECKING( 1,
                                        prunner == plist->p_head,
                                        "ERROR: Existing Data no found",
                                        NULL,
                                        NULL) );

        if( SUCCESS == pcomparedataproc(prunner->key, e_data) )
            break;

        prunner = prunner->p_next;
    }

    p_node_t new_node = NULL;

    CREATE_NODE(new_node, new_data, exit_program);

    return( mv_dcll_generic_insert(plist,prunner->p_prev, new_node, prunner) );
}

 // List Insertion Data Node after the given data 
extern ret_t mv_dcll_insert_after(p_mv_dcll_t plist, data_t new_data, data_t e_data, COMPAREDATAPROC pcomparedataproc)
{
    // Code

    #ifdef  DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    RETURN_FAILURE( ERROR_CHECKING( NULL != pcomparedataproc,
                                    NULL == pcomparedataproc,
                                    "ERROR: Compare Callback must not be NULL",
                                    NULL,
                                    NULL) ); 

    p_node_t prunner = plist->p_head->p_next;

    while(1)
    {
        RETURN_FAILURE( ERROR_CHECKING( 1,
                                        prunner == plist->p_head,
                                        "ERROR: Existing Data no found",
                                        NULL,
                                        NULL) );

        if( SUCCESS == pcomparedataproc(prunner->key, e_data) )
            break;

        prunner = prunner->p_next;
    }

    p_node_t new_node = NULL;

    CREATE_NODE(new_node, new_data, exit_program);

    return( mv_dcll_generic_insert(plist, prunner, new_node, prunner->p_next) );
}

//  List Data Removal Functions

// List Remove Data Node from Back
extern data_t mv_dcll_remove_back(p_mv_dcll_t plist)
{

    // Code
    #ifdef DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    return( mv_dcll_generic_remove(plist, plist->p_tail) );
}

// List Remove Data Node from front
extern data_t mv_dcll_remove_front(p_mv_dcll_t plist)
{
    // Code
    #ifdef DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    return( mv_dcll_generic_remove(plist, plist->p_head->p_next) );
}

// List Remove Data Node from given index/position
extern data_t mv_dcll_remove_at(p_mv_dcll_t plist, size_t index)
{
    // Code
    #ifdef DEBUG
    ASSERTION( NULL != plist );
    #endif

    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY ));

    RETURN_NULL( ERROR_CHECKING(index < plist->size,
                                index >= plist->size,
                                "ERROR: Index Out Of Bound.",
                                NULL,
                                NULL) );

    p_node_t prunner = plist->p_head->p_next;

    for( size_t le = 0; le < index; ++le )
        prunner = prunner->p_next;

    return( mv_dcll_generic_remove(plist, prunner) ); 
}

// List Remove Data Node before the given data
extern data_t mv_dcll_remove_before(p_mv_dcll_t plist, data_t e_data, COMPAREDATAPROC pcomparedataproc)
{
    // Code
    #ifdef  DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    RETURN_NULL( ERROR_CHECKING(NULL != pcomparedataproc,
                                NULL == pcomparedataproc,
                                "ERROR: Compare Callback must not be NULL",
                                NULL,
                                NULL) ); 

    p_node_t prunner = plist->p_head->p_next;

    while(1)
    {
        RETURN_NULL( ERROR_CHECKING(1,
                                    prunner == plist->p_head,
                                    "ERROR: Existing Data no found",
                                    NULL,
                                    NULL) );

        if( SUCCESS == pcomparedataproc(prunner->key, e_data) )
            break;

        prunner = prunner->p_next;
    }

    if( prunner->p_prev == plist->p_head )
        prunner = plist->p_head;

    return( mv_dcll_generic_remove(plist, prunner) );
}

// List Remove Data Node after the given data
extern data_t mv_dcll_remove_after(p_mv_dcll_t plist, data_t e_data, COMPAREDATAPROC pcomparedataproc)
{
    // Code
    #ifdef  DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    RETURN_NULL( ERROR_CHECKING(NULL != pcomparedataproc,
                                NULL == pcomparedataproc,
                                "ERROR: Compare Callback must not be NULL",
                                NULL,
                                NULL) ); 

    p_node_t prunner = plist->p_head->p_next;

    while(1)
    {
        RETURN_NULL( ERROR_CHECKING(1,
                                    prunner == plist->p_head,
                                    "ERROR: Existing Data no found",
                                    NULL,
                                    NULL) );

        if( SUCCESS == pcomparedataproc(prunner->key, e_data) )
            break;

        prunner = prunner->p_next;
    }

    if( prunner == plist->p_tail )
        prunner = plist->p_head;

    return( mv_dcll_generic_remove(plist, prunner) );
}


//  List Data Getter Functions

extern data_t mv_dcll_get_head(p_mv_dcll_t plist)
{
    // Code
    #ifdef DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    return( plist->p_head->p_next->key );
}

extern data_t mv_dcll_get_tail(p_mv_dcll_t plist)
{
    // Code
    #ifdef DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    return( plist->p_tail->key );
}

extern size_t mv_dcll_get_size(p_mv_dcll_t plist)
{
    // Code
    #ifdef DEBUG
    ASSERTION( NULL != plist )
    #endif

    if( FAILURE == check_list_conditions(plist, CHECK_LIST) )
        return(0);

    return( plist->size );
}

extern bool_t mv_dcll_empty(p_mv_dcll_t plist)
{
    if( NULL == plist   ||
        plist->p_head == plist->p_tail )
        return(TRUE);
    
    return(FALSE);
}

//  List Show Data Functions

extern ret_t mv_dcll_print_forward(p_mv_dcll_t plist, SHOWDATAPROC pshowdataproc)
{
    // Code
    #ifdef DEBUG
    ASSERTION( NULL != plist)
    #endif

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST) );

    RETURN_FAILURE( ERROR_CHECKING( NULL != pshowdataproc,
                                    NULL == pshowdataproc,
                                    "ERROR: Show Data Proc must not be NULL.",
                                    NULL,
                                    NULL) );

    p_node_t prunner = plist->p_head->p_next;

    fprintf(stdout, "{START}->");
    for( prunner; prunner != plist->p_head; prunner = prunner->p_next )
        pshowdataproc(prunner->key);
    fprintf(stdout, "{END}\n");

    return(SUCCESS);
}


extern ret_t mv_dcll_print_reverse(p_mv_dcll_t plist, SHOWDATAPROC pshowdataproc)
{
    // Code
    #ifdef DEBUG
    ASSERTION( NULL != plist)
    #endif

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST) );

    RETURN_FAILURE( ERROR_CHECKING( NULL != pshowdataproc,
                                    NULL == pshowdataproc,
                                    "ERROR: Show Data Proc must not be NULL.",
                                    NULL,
                                    NULL) );

    p_node_t prunner = plist->p_tail;

    fprintf(stdout, "{START}->");
    for( prunner; prunner != plist->p_head; prunner = prunner->p_prev )
        pshowdataproc(prunner->key);
    fprintf(stdout, "{END}\n");

    return(SUCCESS);
}


extern ret_t mv_dcll_destroy(pp_mv_dcll_t pplist, DELETEDATAPROC pdeletedataproc)
{
    // Code
    #ifdef DEBUG
    ASSERTION( NULL != pplist)
    #endif

    p_mv_dcll_t plist = *pplist;

    #ifdef DEBUG
    ASSERTION( NULL != plist)
    #endif

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST) );

    RETURN_FAILURE( ERROR_CHECKING( NULL != pdeletedataproc,
                                    NULL == pdeletedataproc,
                                    "ERROR: Delete Data Proc must not be NULL.",
                                    NULL,
                                    NULL) );

    p_node_t prunner = plist->p_head->p_next;

    for( prunner; prunner != plist->p_head;)
    {
        p_node_t prunner_next = prunner->p_next;

        pdeletedataproc(prunner->key);
        fprintf(stdout, "\n");
        prunner->key = NULL;

        free(prunner);
        prunner = prunner_next;
    }

    if( plist->p_head )
    {
        free(plist->p_head);
        plist->p_head = NULL;
    }

    if( plist )
    {
        free(plist);
        plist = NULL;
    }

    *pplist = NULL;

    return(SUCCESS);
}
