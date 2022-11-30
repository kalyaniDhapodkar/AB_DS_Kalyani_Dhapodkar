


//  Headers
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>

#include    "mv_singly_list.h"

//  Function Declarations
static ret_t error_checking(const int assert_condition,
                            const char* assert_condition_str,
                            const char* file_name,
                            const long  line_no,
                            const int error_condition,
                            const char* error_str,
                            void*(*p_error_handler)(void*),
                            void* p_error_handler_params);

//  Constant Literals and Macros

#define     CHECK_LIST  0x00000001
#define     CHECK_EMPTY 0x00000002

#define     CHECK_LIST_EMPTY    CHECK_LIST | CHECK_EMPTY


#define ERROR_CHECKING( assert_condition, error_condition, error_str, error_handler, error_params ) \
        (   error_checking( assert_condition,   \
                            #assert_condition,  \
                            __FILE__,           \
                            __LINE__,           \
                            error_condition,    \
                            error_str,          \
                            error_handler,      \
                            error_params))      


#define RETURN_FAILURE(status)  {                           \
                                    if( FAILURE == status ) \
                                        return(FAILURE);    \
                                }

#define RETURN_NULL(status)     {                           \
                                    if( FAILURE == status ) \
                                        return(NULL);       \
                                }

//////////////////////////////////  List Helper Functions ////////////////////////////////////////////
static ret_t error_checking(const int assert_condition,
                            const char* assert_condition_str,
                            const char* file_name,
                            const long  line_no,
                            const int error_condition,
                            const char* error_str,
                            void*(*p_error_handler)(void*),
                            void* p_error_handler_params)
{
    // Code
    ret_t status = SUCCESS;

    #ifdef  DEBUG
        // Assertion
        if( !assert_condition )
        {
            fprintf(stderr, 
                    "Assertion Failed: %s, File %s, Line %ld\n", 
                    assert_condition_str,
                    file_name,
                    line_no);
            status = FAILURE;
        }
    #else   
        // Error Checking
        if( error_condition )
        {
            if( error_str )
            {
                fprintf(stderr, 
                        error_str);
                fprintf(stderr, 
                        "\n");
            }
            status = FAILURE;
        }
    #endif

    if( FAILURE == status   &&
        NULL != p_error_handler)
    {
        p_error_handler(p_error_handler_params);
    }

    return(status);
}

void* exit_program(void* param)
{
    // Code
    exit(FAILURE);

    return(NULL);
}


static void* Xmalloc(size_t no_of_bytes)
{
    // Code
    void* p = malloc(no_of_bytes);

    ERROR_CHECKING( 1,
                    NULL == p,
                    "ERROR: Out Of Memory.\n",
                    exit_program,
                    NULL);

    return(p);
}

static p_node_t create_node(data_t new_data)
{
    // Local Objects
    p_node_t pnew = NULL;

    // Code
    pnew = Xmalloc(SIZE_NODE);

    if( NULL == pnew )
        return(NULL);

    pnew->key = new_data;
    pnew->p_next = NULL;

    return(pnew);
}

static p_mv_sll_t create_list(void)
{
    // Local Objects
    p_mv_sll_t plist = NULL;

    // Code
    plist = Xmalloc(SIZE_LIST);

    ERROR_CHECKING( NULL != plist,
                    0,
                    NULL,
                    exit_program,
                    NULL);

    plist->size = 0;

    p_node_t sentinel = create_node(NULL);

    plist->p_head = sentinel;
    plist->p_tail = sentinel;

    return(plist);
}

static ret_t check_list_conditions(p_mv_sll_t plist, int check_conditions)
{
    // Code

    ret_t status = SUCCESS;

    if( CHECK_LIST & check_conditions )
    {
        status = ERROR_CHECKING( 1,
                                NULL == plist, 
                                "ERROR: list not found",
                                NULL, 
                                NULL);

        RETURN_FAILURE(status);
    }

    if( CHECK_EMPTY & check_conditions )
    {
        status = ERROR_CHECKING( 1,
                                plist->p_head == plist->p_tail, 
                                "ERROR: list underflow",
                                NULL, 
                                NULL);

        RETURN_FAILURE(status);
    }

    return(status);
}

static ret_t generic_insert(p_mv_sll_t plist, p_node_t e_node, p_node_t new_node)
{
    //  Code
    new_node->p_next = e_node->p_next;   

    e_node->p_next = new_node;

    plist->size++;

    return(SUCCESS);
}

static data_t generic_remove(p_mv_sll_t plist, p_node_t e_node)
{
    // Code
    p_node_t delete_node = e_node->p_next;
 
    e_node->p_next = delete_node->p_next;

    delete_node->p_next = NULL;

    data_t to_return_data = delete_node->key;

    free(delete_node);
    delete_node = NULL;

    plist->size--;

    return(to_return_data);
}

//////////////////////////////////  List Interface Functions ////////////////////////////////////////////
extern p_mv_sll_t create_singly_list(void)
{
    //  Code
    return( create_list() ); 
}

//	List Data Insertion Functions
extern ret_t mv_sll_insert_front(p_mv_sll_t plist, data_t new_data)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST);

    RETURN_FAILURE(status);

    p_node_t new_node = create_node(new_data);

    status = ERROR_CHECKING(NULL != new_node,
                            0,
                            NULL,
                            exit_program,
                            NULL);

    return( generic_insert( plist, plist->p_head, new_node ) );
}

extern ret_t mv_sll_insert_back(p_mv_sll_t plist, data_t new_data)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST);

    RETURN_FAILURE(status);

    p_node_t new_node = create_node(new_data);

    status = ERROR_CHECKING(NULL != new_node,
                            0,
                            NULL,
                            exit_program,
                            NULL);

    status = generic_insert(plist, plist->p_tail, new_node);

    plist->p_tail = new_node;

    return(status);
}

extern ret_t mv_sll_insert_at(p_mv_sll_t plist, data_t new_data, long index)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST);

    RETURN_FAILURE(status);

    p_node_t new_node = create_node(new_data);

    status = ERROR_CHECKING(NULL != new_node,
                            0,
                            NULL,
                            exit_program,
                            NULL);

    status = ERROR_CHECKING(index <= plist->size,
                            index > plist->size,
                            "ERROR: Index Out of Bound.\n",
                            NULL,
                            NULL);

       RETURN_FAILURE(status);


   if( 0 == index )
        return( mv_sll_insert_front(plist, new_data) );
    else if( plist->size == index )
        return( mv_sll_insert_back(plist, new_data) );

        p_node_t prunner = plist->p_head;

        for( long le = 0; le < index; ++le)
            prunner = prunner->p_next;

       return( generic_insert(plist, prunner, new_node) );
}

extern ret_t mv_sll_insert_before(p_mv_sll_t plist, data_t new_data, data_t e_data)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST);

    RETURN_FAILURE(status);

    p_node_t new_node = create_node(new_data);

    status = ERROR_CHECKING(NULL != new_node,
                            0,
                            NULL,
                            exit_program,
                            NULL);
    if( 0 == plist->size )
        return(FAILURE);

    p_node_t prunner = plist->p_head;

    while( NULL != prunner->p_next )
    {
        if( e_data == prunner->p_next->key )
            break;

        prunner = prunner->p_next;
    }

    status = ERROR_CHECKING(NULL != prunner->p_next,
                            NULL == prunner->p_next,
                            "ERROR: Existing Data Not found.\n",
                            NULL,
                            NULL);

       RETURN_FAILURE(status);


    return( generic_insert(plist, prunner, new_node) );
}

extern ret_t mv_sll_insert_after(p_mv_sll_t plist, data_t new_data, data_t e_data)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST);

    RETURN_FAILURE(status);

    p_node_t new_node = create_node(new_data);

    status = ERROR_CHECKING(NULL != new_node,
                            0,
                            NULL,
                            exit_program,
                            NULL);
    if( 0 == plist->size )
        return(FAILURE);

    p_node_t prunner = plist->p_head;

    while( NULL != prunner->p_next )
    {
        if( e_data == prunner->p_next->key )
            break;

        prunner = prunner->p_next;
    }

    status = ERROR_CHECKING(NULL != prunner->p_next,
                            NULL == prunner->p_next,
                            "ERROR: Existing Data Not found.\n",
                            NULL,
                            NULL);

       RETURN_FAILURE(status);


    return( generic_insert(plist, prunner->p_next, new_node) );
}

//	List Data Removal Functions
extern data_t mv_sll_remove_front(p_mv_sll_t plist)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST);

    RETURN_NULL(status);

    status = ERROR_CHECKING(0 != plist->size,
                            0 == plist->size,
                            "ERROR: List Not Present.\n",
                            NULL,
                            NULL);

    RETURN_NULL(status);

    return( generic_remove(plist, plist->p_head) );
}

extern data_t mv_sll_remove_back(p_mv_sll_t plist)
{

    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST);

    RETURN_NULL(status);

    status = ERROR_CHECKING(0 != plist->size,
                            0 == plist->size,
                            "ERROR: List Not Present.\n",
                            NULL,
                            NULL);

    RETURN_NULL(status);

    p_node_t prunner = plist->p_head;

    while(prunner->p_next->p_next)
        prunner = prunner->p_next;

    return( generic_remove(plist, prunner) );
}

extern data_t mv_sll_remove_at(p_mv_sll_t plist, long index)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST);

    RETURN_NULL(status);

    status = ERROR_CHECKING(index < plist->size,
                            index >= plist->size,
                            "ERROR: Index Out of Bound.\n",
                            NULL,
                            NULL);

    RETURN_NULL(status);

   if( 0 == index )
        return( mv_sll_remove_front(plist) );
    else if( plist->size-1 == index )
        return( mv_sll_remove_back(plist) );

    p_node_t prunner = plist->p_head;

    for( long le = 0; le < index; ++le)
        prunner = prunner->p_next;

   return( generic_remove(plist, prunner) );
}

extern data_t mv_sll_remove_before(p_mv_sll_t plist, data_t e_data)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST_EMPTY);

    RETURN_NULL(status);

    status = ERROR_CHECKING(e_data != plist->p_head->p_next->key,
                            e_data == plist->p_head->p_next->key,
                            "ERROR: No Data To Remove.\n",
                            NULL,
                            NULL);

    RETURN_NULL(status);

    p_node_t prunner = plist->p_head;

    while( NULL != prunner->p_next->p_next )
    {
        if( e_data == prunner->p_next->p_next->key )
            break;

        prunner = prunner->p_next;
    }

    status = ERROR_CHECKING(NULL != prunner->p_next->p_next,
                            NULL == prunner->p_next->p_next,
                            "ERROR: Existing Data Not found.\n",
                            NULL,
                            NULL);

    RETURN_NULL(status);


    return( generic_remove(plist, prunner) );
}

extern data_t mv_sll_remove_after(p_mv_sll_t plist, data_t e_data)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST_EMPTY);

    RETURN_NULL(status);

    p_node_t prunner = plist->p_head;

    while( NULL != prunner )
    {
        if( e_data == prunner->key )
            break;

        prunner = prunner->p_next;
    }

    status = ERROR_CHECKING(NULL != prunner,
                            NULL == prunner,
                            "ERROR: Existing Data Not Found.\n",
                            NULL,
                            NULL);

    RETURN_NULL(status);

    status = ERROR_CHECKING(NULL != prunner->p_next,
                            NULL == prunner->p_next,
                            "ERROR: No Data to Remove After.\n",
                            NULL,
                            NULL);

    RETURN_NULL(status);


    return( generic_remove(plist, prunner) );
}

//	List Traversal Functions
extern ret_t mv_sll_print_forward(p_mv_sll_t plist, SHOWDATAPROC pshowdataproc)
{
    // Code

    fprintf(stdout, "SINGLY LIST:\n");
    fprintf(stdout, "{START}->");
    if( !check_list_conditions(plist, CHECK_LIST_EMPTY) && 
        NULL != pshowdataproc)
    {
        for( p_node_t prunner = plist->p_head->p_next; prunner != NULL; prunner = prunner->p_next )
        {
            pshowdataproc(prunner->key);
        }
    }
    fprintf(stdout,"{END}\n\n");

    return(SUCCESS);
}

//	List Getter Functions
extern data_t mv_sll_get_head(p_mv_sll_t plist)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST_EMPTY);

    RETURN_NULL(status);

    return(plist->p_head->p_next->key);
}

extern data_t mv_sll_get_tail(p_mv_sll_t plist)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST_EMPTY);

    RETURN_NULL(status);

    return(plist->p_tail->key);
}

extern data_t mv_sll_get_data(p_mv_sll_t plist, long index)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST);

    RETURN_NULL(status);

    status = ERROR_CHECKING(index < plist->size,
                            index >= plist->size,
                            "ERROR: Index Out of Bound.\n",
                            NULL,
                            NULL);

    RETURN_NULL(status);

    p_node_t prunner = plist->p_head->p_next;

    for( long le = 0; le < index; ++le)
        prunner = prunner->p_next;

   return( prunner->key );
}

extern size_t mv_sll_get_size(p_mv_sll_t plist)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST_EMPTY);

    RETURN_NULL(status);

    return(plist->size);
}

//	List Destroy Function
extern ret_t mv_sll_destroy(pp_mv_sll_t pplist, DELETEDATAPROC pdeletedataproc)
{
    // Code
    RETURN_FAILURE( ERROR_CHECKING( NULL != pplist,
                                    NULL == pplist,
                                    "ERROR: No list present to destroy",
                                    NULL,
                                    NULL) );

    p_mv_sll_t plist = *pplist;

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    RETURN_FAILURE( ERROR_CHECKING( NULL != pdeletedataproc,
                                    NULL == pdeletedataproc,
                                    "ERROR: Delete Data Callback must not be NULL",
                                    NULL,
                                    NULL) );
        
    for( p_node_t prunner = plist->p_head->p_next; prunner != NULL;)
    {
        p_node_t prunner_next = prunner->p_next;

        fprintf(stdout,"Deleting:");
        pdeletedataproc(prunner->key);
        fprintf(stdout,"\n");
        prunner->key = NULL;
        free(prunner);

        prunner = prunner_next;
    }

    free(plist->p_head);
    plist->p_head = NULL;
    plist->p_tail = NULL;
    plist->size = 0;

    free(plist);

    *pplist = NULL;

    return(SUCCESS);
}
