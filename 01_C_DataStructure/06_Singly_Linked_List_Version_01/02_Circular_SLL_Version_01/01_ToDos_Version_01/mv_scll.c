//  879

/**
 * @file    mv_singly_list.c
 * @author  MarshallingVoid (marshallingvoid@gmail.com)
 * @brief   This file contains follows
 *          1) List Interface function's definitions
 *          2) List Helper function's definitions
 * @date    04/11/2022
 * @version 1.0
 * 
 * @copyright   Copyrights (c) 2022
 * 
 */

//  Headers
#include    <stdio.h>
#include    <stdlib.h>
#include    <string.h>

#include    "mv_scll.h"
#include    "mv_stack.h"

//  Function Declarations
static ret_t error_checking(const int assert_condition,
                            const char* assert_condition_str,
                            const char* file_name,
                            const long  line_no,
                            const int error_condition,
                            const char* error_str,
                            void*(*p_error_handler)(void*),
                            void* p_error_handler_params);

static p_node_t create_node(data_t new_data);

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

#define CREATE_NODE(new_node, new_data, exit_proc)  \
        {                                           \
            new_node = create_node(new_data);       \
            ERROR_CHECKING( NULL != new_node,       \
                            0,                      \
                            NULL,                   \
                            exit_proc,              \
                            NULL);                  \
        }  

#define RETURN_FAILURE(status)  {                           \
                                    if( FAILURE == status ) \
                                        return(FAILURE);    \
                                }

#define RETURN_NULL(status)     {                           \
                                    if( FAILURE == status ) \
                                        return(NULL);       \
                                }

//////////////////////////////////  List Helper Functions ////////////////////////////////////////////
/**
 * @function:   Checks the error condition OR asserts the conditions
 * @params: 1)  Assert Condition Result
 *          2)  Assert Condition String
 *          3)  File Name in which assertion fails
 *          4)  Line No where assertion fails
 *          5)  Error Condition
 *          6)  Error Condition String
 *          7)  Error Handler
 *          8)  Error Handler's Parameters
 * @returns: Status of condition
 */
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

/**
 * @function: Handling error to exit program
 * @params: NULL
 * @return: NULL
 */
void* exit_program(void* param)
{
    // Code
    exit(FAILURE);

    return(NULL);
}


/**
 * @function:   Memory allocation wrapper function
 * @params: 1) No of bytes
 * @returns:    Valid address if successful or NULL if unsuccessful
 */
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

/**
 * @function:  Creates new node and assign data to it
 * @params: 1)  New data
 * @return: returns valid node OR NULL if node not allocated
 */
static p_node_t create_node(data_t new_data)
{
    // Local Objects
    p_node_t pnew = NULL;

    // Code
    pnew = Xmalloc(SIZE_NODE);

    if( NULL == pnew )
        return(NULL);

    pnew->key = new_data;
    pnew->p_next = pnew;

    return(pnew);
}

/**
 * @function: Creates new list object
 * @params: void
 * @return: returns valid scll Object OR NULL if List Object not allocated.
 */
static p_mv_scll_t create_list(void)
{
    // Local Objects
    p_mv_scll_t plist = NULL;

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

/**
 * @function: Check the list conditions
 * @params: 1) List
 *          2) conditions
 * @returns:    Status of the conditions to be checked
 */
static ret_t check_list_conditions(p_mv_scll_t plist, int check_conditions)
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

/**
 * @function: Adds NEW NODE after the EXISTING NODE
 * @params: 1) List
 *          2) EXISTING NODE
 *          3) NEW NODE
 * @returns: status of insertion
 */
static ret_t generic_insert(p_mv_scll_t plist, p_node_t e_node, p_node_t new_node)
{
    //  Code

    //  connect the new node with the list
    new_node->p_next = e_node->p_next;   

    //  adding the new node into the list after existing node
    e_node->p_next = new_node;

    //  increment no of elements
    plist->size++;

    if( plist->p_head == new_node->p_next )
        plist->p_tail = new_node;

    return(SUCCESS);
}

/**
 * @function: Remove the SUCCESSOR of EXISTING NODE
 * @params: 1) List
 *          2) EXISTING NODE
 * @returns: the remove node's data
 */
static data_t generic_remove(p_mv_scll_t plist, p_node_t e_node)
{
    // Code

    // Get the node to be deleted
    p_node_t delete_node = e_node->p_next;

    // Disconnect the node to be deleted from list by assigning the link of successsor node to
    // predecessor's next 
    e_node->p_next = delete_node->p_next;

    //  Disconnect the successor's link (OPTIONAL)
    delete_node->p_next = NULL;

    //  Get the data fromt to be deleted node
    data_t to_return_data = delete_node->key;

    // Check for tail
    if( delete_node == plist->p_tail )
        plist->p_tail = e_node;

    //  Free the node
    free(delete_node);
    delete_node = NULL;

    //  Decrement size
    plist->size--;

    //  return data
    return(to_return_data);
}

//////////////////////////////////  List Interface Functions ////////////////////////////////////////////
/**
 * @function: Create List Function
 * @params:	void
 * @returns: a pointer to singly list object
 */
extern p_mv_scll_t create_singly_circular_list(void)
{
    //  Code
    return( create_list() ); 
}

//	List Data Insertion Functions
/**
 * @function: Insert data in FRONT of singly list
 * @params:	1)	List
 * 			2)	New Data
 * @returns:	Status of insertion at FRONT
 * 			returns SUCCESS if successful insertion
 * 			OR
 * 			return 	FAILURE for un-successful insertion
 */
extern ret_t mv_scll_insert_front(p_mv_scll_t plist, data_t new_data)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST);

    RETURN_FAILURE(status);

    p_node_t new_node = NULL;

    CREATE_NODE(new_node, new_data, exit_program);

    return( generic_insert( plist, plist->p_head, new_node ) );
}

/**
 * @function: Insert data in BACK of singly list'
 * @params:	1)	List
 * 			2)	New Data
 * @returns:	Status of insertion at BACK
 * 			returns SUCCESS for successful insertion
 * 			OR
 * 			returns FAILURE for un-successful insertion
 */
extern ret_t mv_scll_insert_back(p_mv_scll_t plist, data_t new_data)
{
    // Code
    ret_t status = check_list_conditions(plist, CHECK_LIST);

    RETURN_FAILURE(status);

    p_node_t new_node = NULL;

    CREATE_NODE(new_node, new_data, exit_program);

    //  insert new node to back of list
    status = generic_insert(plist, plist->p_tail, new_node);

   /* //  assign new node to tail
    plist->p_tail = new_node;*/

    return(status);
}

/**
 * @function: Insert Data at a specific INDEX
 * @params:	1) List
 * 			2) New Data
 * 		 	3) INDEX of insertion
 * @returns	: Status of insertion at a specific INDEX
 * 			returns SUCCESS for successful insertion
 * 			OR
 * 			returns FAILURE for un-successful insertion
 */
extern ret_t mv_scll_insert_at(p_mv_scll_t plist, data_t new_data, size_t index)
{
    // Code
    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST) );

    // CODE BLOCK 1
    if( index == plist->size )
        return( mv_scll_insert_back(plist, new_data) );
    else if(0 == index)
        return( mv_scll_insert_front(plist, new_data) );

    RETURN_FAILURE( ERROR_CHECKING( index < plist->size, // hear "index <= plist->size" is also valid only if we use CODE BLOCK 2
                                    index > plist->size,
                                    "ERROR: Index Out Of Bound.",
                                    NULL,
                                    NULL) );

    // Assign the sentinel to runner
    p_node_t prunner = plist->p_head;

    //  Iterate to the (index-1) position
    for( size_t le = 0; le < index; ++le)
        prunner = prunner->p_next;

    p_node_t new_node = NULL;

    //  Create New Node for New Data
    CREATE_NODE(new_node, new_data, exit_program);

    // Insert new node in the list
    ret_t status = generic_insert(plist, prunner, new_node);

    /*
    // CODE BLOCK 2
    if( index == plist->size )
        plist->p_tail = new_node;
    */

    // return status
    return( status );   
}

/**
 * @function: Insert Data BEFORE a specific existing data
 * @params:	1) List
 * 			2) New Data
 * 			3) Existing Data
 * @returns: Status of insertion BEFORE an existing data
 * 			returns SUCCESS for successful insertion
 * 			OR
 * 			returns FAILURE for un-successful insertion
 */
extern ret_t mv_scll_insert_before(p_mv_scll_t plist, data_t new_data, data_t e_data, COMPAREEQUALITYDATAPROC pcompareproc)
{
    // Code
    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    RETURN_FAILURE( ERROR_CHECKING( NULL != pcompareproc,
                                    NULL == pcompareproc,
                                    "ERROR: Compare Callback must not be NULL",
                                    NULL,
                                    NULL) );

    // Assign sentinel to prunner
    p_node_t prunner = plist->p_head;

    // Traverse the list and find the node whose next node is the existing data 
    while(1)    
    {
        if( plist->p_head == prunner->p_next )
        {
            fprintf(stderr, "ERROR: Existing data not found.\n");
            return(FAILURE);
        }

        if( SUCCESS == pcompareproc(prunner->p_next->key, e_data) )
            break;
        
        prunner = prunner->p_next; 
    }

    p_node_t new_node = NULL;

    
    // Creating the new node
    CREATE_NODE(new_node, new_data, exit_program);

    // Inserting the node in the list
    return( generic_insert(plist, prunner, new_node) );
}

/**
 * @function: Insert Data AFTER a specific existing data
 * @params: 1) List
 *          2) New Data
 *          3) Existing Data
 * @returns: Status of insertion AFTER an existing data
 *          returns SUCCESS for successful insertion
 *          OR
 *          returns FAILURE for un-successful insertion
 */
extern ret_t mv_scll_insert_after(p_mv_scll_t plist, data_t new_data, data_t e_data, COMPAREEQUALITYDATAPROC pcompareproc)
{
    // Code
    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    RETURN_FAILURE( ERROR_CHECKING( NULL != pcompareproc,
                                    NULL == pcompareproc,
                                    "ERROR: Compare Callback must not be NULL",
                                    NULL,
                                    NULL));

    // Assign the next of sentinel to runner
    p_node_t prunner = plist->p_head->p_next;

    // Find the node of existing data to insert new node after it
    while(1)
    {
        if( plist->p_head == prunner )
        {
            fprintf(stderr,"ERROR: Existing data not found.\n");
            return(FAILURE);
        }

        if( SUCCESS == pcompareproc(prunner->key, e_data) )
            break;

        prunner = prunner->p_next;
    } 

    // Create new node
    p_node_t new_node = NULL;

    CREATE_NODE(new_node, new_data, exit_program);

    return(generic_insert(plist, prunner, new_node));
}

//	List Data Removal Functions
/**
 * @function: Remove Data from FRONT of the list
 * @params:	1) List
 * @returns: Removed Data from list
 * 			returns a valid data if remove successful
 * 			OR
 * 			return NULL if unsuccessful
 */
extern data_t mv_scll_remove_front(p_mv_scll_t plist)
{
    // Code
    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    return( generic_remove(plist, plist->p_head) );
}

/**
 * @function: Remove Data from BACK of the list
 * @params: 1) List
 * @returns: Removed Data from list
 * 			returns a valid data if remove successful
 * 			OR
 * 			returns NULL if unsuccessful
 */
extern data_t mv_scll_remove_back(p_mv_scll_t plist)
{
    // Code
    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    p_node_t prunner = plist->p_head;

    // Traverse to the node whose next node is TAIL
    for( prunner; prunner->p_next != plist->p_tail; prunner = prunner->p_next );

    return( generic_remove(plist, prunner) );
}

/**
 * @function: Remove Data from a specific INDEX
 * @params: 1) List
 * 			2) INDEX
 * @return: Removed data from list
 * 			returns a valid data if remove successful
 * 			OR
 * 			returns NULL if unsuccessful
 */
extern data_t mv_scll_remove_at(p_mv_scll_t plist, size_t index)
{
    // Code
    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY ) );

    if( index == 0 )
        return( mv_scll_remove_front(plist) );
    else if( index == plist->size-1 ) 
        return( mv_scll_remove_back(plist) ); 

    RETURN_NULL( ERROR_CHECKING( index < plist->size,
                                    index >= plist->size,
                                    "ERROR: Index out of bound.",
                                    NULL,
                                    NULL ) );

    p_node_t prunner = plist->p_head;

    //   Traverse through the list to get a node whose next is to be deleted
    for( size_t le = 0; le < index; ++le )
        prunner = prunner->p_next;

    return( generic_remove(plist, prunner) );
}

/**
 * @function: Remove Data from BEFORE of an existing data
 * @params:	1) List
 * 			2) Existing Data
 * @returns: Removed Data from list
 * 			returns a valid data if remove succssful
 * 			OR
 * 			returns NULL if unsuccessful
 */
extern data_t mv_scll_remove_before(p_mv_scll_t plist, data_t e_data, COMPAREEQUALITYDATAPROC pcompareproc)
{
    // Code

    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    p_node_t prunner_delete_node = plist->p_head;

    if( SUCCESS == pcompareproc(prunner_delete_node->p_next->key, e_data) )
    {
        fprintf(stderr, "ERROR: Nothing Present before HEAD to remove.\n");
        return(NULL);
    }

    //  Find To Delete Node
    while(1)
    {
        if( plist->p_head == prunner_delete_node->p_next )
        {
            fprintf(stderr, "ERROR: Existing data not found.\n");
            return(NULL);
        }

        if( SUCCESS == pcompareproc(prunner_delete_node->p_next->key, e_data) )
            break;

        prunner_delete_node = prunner_delete_node->p_next;
    }

    p_node_t prunner = plist->p_head;

    // To find the node whose next is to be deleted node
    while(1)
    {
        if( SUCCESS == pcompareproc(prunner->p_next->key, prunner_delete_node->key) )
            break;

        prunner = prunner->p_next;
    }

    return( generic_remove(plist, prunner) );
}

/**
 * @function: Remove Data from AFTER of an existing data
 * @params: 1) List
 * 			2) Existing Data
 * @returns: Removed Data from list
 * 			returns a valid data from list if successful
 * 			OR
 * 			returns NULL if unsuccessful
 */
extern data_t mv_scll_remove_after(p_mv_scll_t plist, data_t e_data, COMPAREEQUALITYDATAPROC pcompareproc)
{
    // Code
    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    p_node_t prunner = plist->p_head->p_next;

    while(1)
    {
        if( plist->p_head == prunner )
        {
            fprintf(stderr, "ERROR: Existing data not found.\n");
            return(NULL);
        }

        if( SUCCESS == pcompareproc(prunner->key, e_data) )
            break;

        prunner = prunner->p_next;
    }

    if( plist->p_tail == prunner )
    {
        fprintf(stderr, "ERROR: No data present after TAIL to remove.\n");
        return(NULL);
    }

    return(generic_remove(plist, prunner));
}

//	List Traversal Functions
/**
 * @function: Prints data present in the list in forward manner
 * @params:	1) List
 * 			2) Function Pointer to print data
 * @returns: SUCCESS for successful print
 */
extern ret_t mv_scll_print_forward(p_mv_scll_t plist, SHOWDATAPROC pshowdataproc)
{
    // Code

    fprintf(stdout, "SINGLY LIST:\n");
    fprintf(stdout, "{START}->");
    if( !check_list_conditions(plist, CHECK_LIST_EMPTY) && 
        NULL != pshowdataproc)
    {
        for( p_node_t prunner = plist->p_head->p_next; prunner != plist->p_head; prunner = prunner->p_next )
        {
            pshowdataproc(prunner->key);
        }
    }
    fprintf(stdout,"{END}\n\n");

    return(SUCCESS);
}

/**
 * @function: Prints data present in the list in reverse manner
 * @params: 1) List
 * 			2) Function Pointer to print data
 * @returns: SUCCESS for successful print
 */
extern ret_t mv_scll_print_reverse(p_mv_scll_t plist, SHOWDATAPROC pshowdataproc)
{
    // Code

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    /*
        // This code executes completely fine and gives a correct output. 
        // But is a VERY VERY VERY VERY INEFFICIENT CODE 

        fprintf(stdout, "{START}->\n");
        for( long long le = plist->size-1; le >= 0; --le)
        {
            pshowdataproc( mv_scll_get_data(plist, le) );
        }
        fprintf(stdout, "{END}.\n");
    */

    p_mv_stack_t pstack = create_stack();

    for(p_node_t prunner = plist->p_head->p_next; 
        plist->p_head != prunner;
        prunner = prunner->p_next )
        mv_stack_push(pstack, prunner->key);

    fprintf(stdout, "{START}->");
    while( 0 != mv_stack_size(pstack) )
        pshowdataproc( mv_stack_pop(pstack) );
    fprintf(stdout, "{END}\n");

    mv_stack_destroy(&pstack);
    pstack = NULL;

    return(SUCCESS);
}

//	List Getter Functions
/**
 * @function: Get The FIRST element from list
 * @params: 1) List
 * @returns: FIRST Element if present OR returns NULL
 */
extern data_t mv_scll_get_head(p_mv_scll_t plist)
{
    // Code
    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    return( plist->p_head->p_next->key );
}

/**
 * @function: Get the LAST element from list
 * @params: 1) List
 * @returns: LAST element if present OR returns NULL
 */
extern data_t mv_scll_get_tail(p_mv_scll_t plist)
{
    // Code
    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    return( plist->p_tail->key );
}

/**
 * @function: Get data from specific index
 * @params: 1) List
 * 			2) INDEX
 * @returns: DATA from a specific INDEX of list OR NULL
 */
extern data_t mv_scll_get_data(p_mv_scll_t plist, size_t index)
{
    // Code
    RETURN_NULL( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    RETURN_NULL( ERROR_CHECKING(index < plist->size,
                                index >= plist->size,
                                "ERROR: Index out of bound.\n",
                                NULL,
                                NULL));

    p_node_t prunner = plist->p_head;

    for( size_t le = 0; le <= index; ++le )
        prunner = prunner->p_next;

    return( prunner->key );
}

/**
 * @function: Get the SIZE of list
 * @params: 1) List
 * @returns: Count of elements present in list
 */
extern size_t mv_scll_get_size(p_mv_scll_t plist)
{
    // Code
    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST) );

    return( plist->size );
}

//	List Destroy Function
/**
 * @function: Destroy the existing list
 * @params:	1) Pointer To LIST
 * 			2) Callback function for destroy data
 * @returns: SUCCESS for successful destroy
 * 			 OR
 * 			 FAILURE if no data present
 */
extern ret_t mv_scll_destroy(pp_mv_scll_t pplist, DELETEDATAPROC pdeletedataproc)
{
    // Code
    RETURN_FAILURE( ERROR_CHECKING( NULL != pplist,
                                    NULL == pplist,
                                    "ERROR: No list present to destroy",
                                    NULL,
                                    NULL) );

    p_mv_scll_t plist = *pplist;

    RETURN_FAILURE( check_list_conditions(plist, CHECK_LIST_EMPTY) );

    RETURN_FAILURE( ERROR_CHECKING( NULL != pdeletedataproc,
                                    NULL == pdeletedataproc,
                                    "ERROR: Delete Data Callback must not be NULL",
                                    NULL,
                                    NULL) );
        
    for( p_node_t prunner = plist->p_head->p_next; prunner != plist->p_head;)
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
