

//  Headers
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>

#include    "mv_dll.h"

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

static p_node_t create_node(data_t new_data)
{
    // Code
    p_node_t new_node = (p_node_t)Xmalloc(SIZE_NODE);

    if( NULL == new_node )
        return(new_node);

    //  Assign new data to key of new node
    new_node->key = new_data;

    //  Assign self to next and previous pointers of self
    new_node->p_next = NULL;
    new_node->p_prev = NULL;

    return(new_node);
}

static p_mv_dll_t create_list(void)
{
    // Code

    //  Create new dll
    p_mv_dll_t plist = (p_mv_dll_t)Xmalloc(SIZE_DLL);

    if( NULL == plist )
        return(plist);

    p_node_t sentinel = NULL;

    //  Create a sentinel with no data node
    CREATE_NODE(sentinel, NULL, exit_program);

    //  Assign the sentinel as the head of the new dll
    plist->p_head = sentinel;
    plist->p_tail = sentinel;
    plist->size = 0;

    return(plist);
}

static ret_t mv_dll_generic_insert(p_mv_dll_t plist, p_node_t first,  p_node_t mid, p_node_t last)
{
    //  Code

    //  Add the new node(mid) in the list
    mid->p_prev = first;
    mid->p_next = last;

    // Manipulate the list pointer to incorporate the new node
    first->p_next = mid;

    if(last != NULL)
        last->p_prev = mid;

    if(plist->p_tail == first)
        plist->p_tail = mid;

    //  Increment the size
    plist->size++;

    return(SUCCESS);
}

static data_t mv_dll_generic_remove(p_mv_dll_t plist, p_node_t d_node)
{
    // Code
    p_node_t prev_node = d_node->p_prev;
    p_node_t next_node = d_node->p_next;

    // Disconnet the d_node from list
    prev_node->p_next = next_node;

    if(NULL != next_node)
        next_node->p_prev = prev_node;

    // NIL the pointer of d_node (OPTIONAL)
    d_node->p_next = NULL;
    d_node->p_prev = NULL;

    //  Get the data to return
    data_t to_return_data = d_node->key;

    //  Assign new tail
    if(plist->p_tail == d_node)
    plist->p_tail = prev_node;

    free(d_node);
    d_node = NULL;

    // Decrement the size
    plist->size--;

    return(to_return_data);
}

static ret_t check_list_conditions(p_mv_dll_t plist, int conditions)
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

extern p_mv_dll_t  create_doubly_list()
{
    // Code
    return( create_list() );
}

extern ret_t mv_dll_insert_front(p_mv_dll_t plist, data_t new_data)
{
    // Code
    #ifdef  DEBUG
    ASSERTION( NULL != plist );
    #endif

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST) );

    p_node_t new_node = NULL;

    CREATE_NODE(new_node, new_data, exit_program);

    return( mv_dll_generic_insert(plist, plist->p_head, new_node, plist->p_head->p_next) );
}

//  List Data Insertion Functions

extern ret_t mv_dll_insert_back(p_mv_dll_t plist, data_t new_data)
{
    // Code
    #ifdef  DEBUG
    ASSERTION( NULL != plist );
    #endif

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST) );

    p_node_t new_node = NULL;

    CREATE_NODE(new_node, new_data, exit_program);

    return( mv_dll_generic_insert(plist, plist->p_tail, new_node, plist->p_tail->p_next ) );
}
    
extern ret_t mv_dll_insert_at(p_mv_dll_t plist, data_t new_data, size_t index)
{
    //  Code
    #ifdef DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    if( 0 == index )
        return( mv_dll_insert_front(plist, new_data) );
    else if( index == plist->size )
        return( mv_dll_insert_back(plist, new_data) );


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

    return( mv_dll_generic_insert(plist, prunner, new_node, prunner->p_next ) );
}

extern ret_t mv_dll_insert_before(p_mv_dll_t plist, data_t new_data, data_t e_data, COMPAREDATAPROC  pcomparedataproc)
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
                                        prunner == NULL,
                                        "ERROR: Existing Data no found",
                                        NULL,
                                        NULL) );

        if( SUCCESS == pcomparedataproc(prunner->key, e_data) )
            break;

        prunner = prunner->p_next;
    }

    p_node_t new_node = NULL;

    CREATE_NODE(new_node, new_data, exit_program);

    return( mv_dll_generic_insert(plist,prunner->p_prev, new_node, prunner) );
}

extern ret_t mv_dll_insert_after(p_mv_dll_t plist, data_t new_data, data_t e_data, COMPAREDATAPROC pcomparedataproc)
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
                                        prunner == NULL,
                                        "ERROR: Existing Data no found",
                                        NULL,
                                        NULL) );

        if( SUCCESS == pcomparedataproc(prunner->key, e_data) )
            break;

        prunner = prunner->p_next;
    }

    p_node_t new_node = NULL;

    CREATE_NODE(new_node, new_data, exit_program);

    return( mv_dll_generic_insert(plist, prunner, new_node, prunner->p_next) );
}

//  List Data Removal Functions

extern data_t mv_dll_remove_front(p_mv_dll_t plist)
{
    // Code
    #ifdef DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    return( mv_dll_generic_remove(plist, plist->p_head->p_next) );
}

extern data_t mv_dll_remove_back(p_mv_dll_t plist)
{

    // Code
    #ifdef DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    return( mv_dll_generic_remove(plist, plist->p_tail) );
}

extern data_t mv_dll_remove_at(p_mv_dll_t plist, size_t index)
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

    return( mv_dll_generic_remove(plist, prunner) ); 
}

extern data_t mv_dll_remove_before(p_mv_dll_t plist, data_t e_data, COMPAREDATAPROC pcomparedataproc)
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
                                    prunner == NULL,
                                    "ERROR: Existing Data no found",
                                    NULL,
                                    NULL) );

        if( SUCCESS == pcomparedataproc(prunner->key, e_data) )
            break;

        prunner = prunner->p_next;
    }

    RETURN_NULL( ERROR_CHECKING(1,
                                prunner->p_prev == plist->p_head,
                                "ERROR: No Data Present Before.\n",
                                NULL,
                                NULL) );

    return( mv_dll_generic_remove(plist, prunner) );
}

extern data_t mv_dll_remove_after(p_mv_dll_t plist, data_t e_data, COMPAREDATAPROC pcomparedataproc)
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
                                    prunner == NULL,
                                    "ERROR: Existing Data no found",
                                    NULL,
                                    NULL) );

        if( SUCCESS == pcomparedataproc(prunner->key, e_data) )
            break;

        prunner = prunner->p_next;
    }

    
    RETURN_NULL( ERROR_CHECKING(1,
                                prunner == plist->p_tail,
                                "ERROR: No Data Present After.\n",
                                NULL,
                                NULL) );

    return( mv_dll_generic_remove(plist, prunner) );
}


//  List Data Getter Functions

extern data_t mv_dll_get_head(p_mv_dll_t plist)
{
    // Code
    #ifdef DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    return( plist->p_head->p_next->key );
}

extern data_t mv_dll_get_tail(p_mv_dll_t plist)
{
    // Code
    #ifdef DEBUG
    ASSERTION( NULL != plist )
    #endif

    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    return( plist->p_tail->key );
}

extern size_t mv_dll_get_size(p_mv_dll_t plist)
{
    // Code
    #ifdef DEBUG
    ASSERTION( NULL != plist )
    #endif

    if( FAILURE == check_list_conditions(plist, CHECK_LIST) )
        return(0);

    return( plist->size );
}

extern bool_t mv_dll_empty(p_mv_dll_t plist)
{
    if( NULL == plist   ||
        plist->p_head == plist->p_tail )
        return(TRUE);
    
    return(FALSE);
}

//  List Show Data Functions
extern ret_t mv_dll_print_forward(p_mv_dll_t plist, SHOWDATAPROC pshowdataproc)
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

    fprintf(stdout, "\nDOUBLY LIST FORWARD:\n");
    fprintf(stdout, "{START}->");
    for( prunner; prunner != NULL; prunner = prunner->p_next )
        pshowdataproc(prunner->key);
    fprintf(stdout, "{END}\n");

    return(SUCCESS);
}

extern ret_t mv_dll_print_reverse(p_mv_dll_t plist, SHOWDATAPROC pshowdataproc)
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

    fprintf(stdout, "\nDOUBLY LIST REVERSE:\n");
    fprintf(stdout, "{START}->");
    for( prunner; prunner != plist->p_head; prunner = prunner->p_prev )
        pshowdataproc(prunner->key);
    fprintf(stdout, "{END}\n");

    return(SUCCESS);
}

extern ret_t mv_dll_destroy(pp_mv_dll_t pplist, DELETEDATAPROC pdeletedataproc)
{
    // Code
    #ifdef DEBUG
    ASSERTION( NULL != pplist)
    #endif

    p_mv_dll_t plist = *pplist;

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

    fprintf(stdout, "\nDESTROYING DOUBLY LIST:\n");
    for( prunner; prunner != NULL;)
    {
        p_node_t prunner_next = prunner->p_next;

        fprintf(stdout, "\nDESTROYING: ");
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
