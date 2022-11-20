
//  Headers

#include <stdio.h>
#include <stdlib.h>

#include "mv_deque_header.h"

//  Function Declaration
static ret_t error_checking(const int assert_condition,
                            const char *assert_condition_str,
                            const char *file_name,
                            const long line_no,
                            const int error_condition,
                            const char *error_str,
                            ERROR_HANDLER perrorhandler,
                            void *error_handler_param);

// Constant Literals and Macros

#define ERROR_CHECKING(assert_condition, error_condition, error_str, error_handler, error_params) \
    (                                                                                             \
        error_checking(assert_condition,                                                          \
                       #assert_condition,                                                         \
                       __FILE__,                                                                  \
                       __LINE__,                                                                  \
                       error_condition,                                                           \
                       error_str,                                                                 \
                       error_handler,                                                             \
                       error_params))

#define DEQUEUE_DEFAULT_SIZE 512

#define CHECK_OBJECT 0x00000001
 

#define RETURN_NULL(status)    \
    {                          \
        if (FAILURE == status) \
        {                      \
            return (NULL);     \
        }                      \
    }

#define RETURN_FAILURE(status) \
    {                          \
        if (FAILURE == status) \
        {                      \
            return (status);   \
        }                      \
    }

#define _EXIT_FAILURE(status)  \
    {                          \
        if (FAILURE == status) \
        {                      \
            exit(FAILURE);     \
        }                      \
    }

//  Dequeue Helper Functions
static void *Xmalloc(size_t nr_of_bytes)
{
    // Code
    void *p = malloc(nr_of_bytes);

    ret_t status = ERROR_CHECKING(1,
                                  NULL == p,
                                  "ERROR: Out Of Memory\n",
                                  NULL,
                                  NULL);

    return (p);
}

static void *Xcalloc(size_t nr_of_elements, size_t size_of_element)
{
    // Code
    void *p = calloc(nr_of_elements, size_of_element);

    ret_t status = ERROR_CHECKING(1,
                                  NULL == p,
                                  "ERROR: Out of Memory.\n",
                                  NULL,
                                  NULL);
    return (p);
}

static void *Xrealloc(void* p, size_t nr_of_bytes)
{
    // Code
    void* rp = realloc(p, nr_of_bytes);
    
    ERROR_CHECKING( 1, 
                    NULL == p, 
                    "ERROR: Out Of Memory.\n" , 
                    NULL, 
                    NULL);
    
    return(rp);
}

static ret_t error_checking(const int assert_condition,
                            const char *assert_condition_str,
                            const char *file_name,
                            const long line_no,
                            const int error_condition,
                            const char *error_str,
                            ERROR_HANDLER perrorhandler,
                            void *error_handler_params)
{
    // Code
    ret_t status = SUCCESS;

#ifdef MV_DEBUG
    //  Assertion
    if (!assert_condition)
    {
        fprintf(stderr, "Condition %s, File %s, Line no %ld.\n", assert_condition_str, file_name, line_no);
        status = FAILURE;
    }
#else
    // Error Checking
    if (error_condition)
    {
        if (NULL != error_str)
            fprintf(stderr, error_str);
        status = FAILURE;
    }
#endif

    if (FAILURE == status)
    {
        if (NULL != perrorhandler)
        {
            perrorhandler(error_handler_params);
        }
    }

    return (status);
}

static void *deallocate_dequeue(void *param)
{
    //  Code
    pp_mv_dequeue_t ppdequeue = (pp_mv_dequeue_t)param;
    p_mv_dequeue_t pdequeue = *ppdequeue;

    if (pdequeue)
    {
        free(pdequeue);
        pdequeue = NULL;
    }

    *ppdequeue = NULL;

    exit(FAILURE);

    return (NULL);
}

static ret_t check_dequeue_conditions(p_mv_dequeue_t pdequeue, int condition_to_check)
{
    // Code
    ret_t status = SUCCESS;

    //  Check for struct object
    if (condition_to_check & CHECK_OBJECT)
    {
        status = ERROR_CHECKING(NULL != pdequeue,
                                NULL == pdequeue,
                                "ERROR: Queue Not Found",
                                NULL,
                                NULL);

        RETURN_FAILURE(status);
    }

    return (status);
}

//  Dequeue Interface Functions

//  Data Structure Creation
extern p_mv_dequeue_t mv_create_default_dequeue(void)
{
    //  Code
    p_mv_dequeue_t pdequeue = (p_mv_dequeue_t)Xmalloc(SIZE_DEQUEUE);

    ret_t status = ERROR_CHECKING(NULL != pdequeue,
                                  NULL == pdequeue,
                                  "ERROR: DeQueue Cannot be created",
                                  NULL,
                                  NULL);

    _EXIT_FAILURE(status);

    pdequeue->pvector = mv_create_default_vector(DEQUEUE_DEFAULT_SIZE);

    pdequeue->head = 0;
    pdequeue->tail = 0;

    return (pdequeue);
}

extern p_mv_dequeue_t mv_create_custom_dequeue(size_t custom_size)
{
    //  Code
    p_mv_dequeue_t pdequeue = (p_mv_dequeue_t)Xmalloc(SIZE_DEQUEUE);

    ret_t status = ERROR_CHECKING(NULL != pdequeue,
                                  NULL == pdequeue,
                                  "ERROR: DeQueue Cannot be created",
                                  NULL,
                                  NULL);

    _EXIT_FAILURE(status);

    pdequeue->pvector = mv_create_custom_vector(custom_size);

    pdequeue->head = 0;
    pdequeue->tail = 0;

    return (pdequeue);
}

extern ret_t mv_dequeue_enqueue_front(p_mv_dequeue_t pdequeue, data_t data)
{
    // Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT );

    RETURN_FAILURE(status);

    status = ERROR_CHECKING(NULL != data,
                            NULL == data,
                            "ERROR: Data not found to add.\n",
                            NULL,
                            NULL);
    RETURN_FAILURE(status);

    status = mv_vector_push_front(pdequeue->pvector, data);

    if(status == SUCCESS)
    pdequeue->tail++;

    return (SUCCESS);
}

extern ret_t mv_dequeue_enqueue_back(p_mv_dequeue_t pdequeue, data_t data)
{
    // Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT);

    RETURN_FAILURE(status);

    status = ERROR_CHECKING(NULL != data,
                            NULL == data,
                            "ERROR: Data not found to add",
                            NULL,
                            NULL);

    RETURN_FAILURE(status);

    status = mv_vector_push_back(pdequeue->pvector, data);

    if(status == SUCCESS)
    pdequeue->tail++;

    return (SUCCESS);
}

extern data_t mv_dequeue_dequeue_front(p_mv_dequeue_t pdequeue)
{
    //  Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT );

    RETURN_NULL(status);

    data_t to_return_data = pdequeue->pvector->array[0];
  
    mv_vector_pop_front(pdequeue->pvector);

    pdequeue->tail--;

    return(to_return_data);
}

extern data_t mv_dequeue_dequeue_back(p_mv_dequeue_t pdequeue)
{
    //  Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT);

    RETURN_NULL(status);

    data_t to_return_data = mv_vector_pop_back(pdequeue->pvector);

    pdequeue->tail--;

    return(to_return_data);
}

//  Queue capacity
extern size_t mv_dequeue_size(p_mv_dequeue_t pdequeue)
{
    // Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT);

    RETURN_FAILURE(status);

    return (mv_vector_capacity(pdequeue->pvector));
}

//  Queue No of elements
extern size_t mv_dequeue_no_of_elements(p_mv_dequeue_t pdequeue)
{
    // Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT);

    RETURN_FAILURE(status);

    return (mv_vector_size(pdequeue->pvector));
}

//  Data Print
extern ret_t mv_dequeue_print_data(p_mv_dequeue_t pdequeue, PRINTDATAPROC pprintfunc)
{
    // Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT);
    RETURN_FAILURE(status);

    status = ERROR_CHECKING(NULL != pprintfunc,
                            NULL == pprintfunc,
                            "ERROR: Print callback must be provided",
                            NULL,
                            NULL);
    RETURN_FAILURE(status);

    fprintf(stdout, "\nDequeue:\n");
    mv_vector_print_data(pdequeue->pvector, pprintfunc);

    return (SUCCESS);
}

//  Destroy Dequeue
extern ret_t mv_dequeue_destroy(pp_mv_dequeue_t ppdequeue, DELETEDATAPROC pdeletefunc)
{
    // Code
    ret_t status = SUCCESS;

    status = ERROR_CHECKING(NULL != ppdequeue,
                            NULL == ppdequeue,
                            "ERROR: DeQueue not found.\n",
                            NULL,
                            NULL);
    RETURN_FAILURE(status);

    p_mv_dequeue_t pdequeue = *ppdequeue;

    status = check_dequeue_conditions(pdequeue, CHECK_OBJECT);
    RETURN_FAILURE(status);

    status = ERROR_CHECKING(NULL != pdeletefunc,
                            NULL == pdeletefunc,
                            "ERROR: Print callback must be provided",
                            NULL,
                            NULL);
    RETURN_FAILURE(status);

    fprintf(stdout, "\nDeleting Data of Dequeue:\n");
 
    mv_vector_destroy(&pdequeue->pvector, pdeletefunc);

    // Deallocate Struct object
    if (pdequeue)
    {
        free(pdequeue);
        pdequeue = NULL;
    }

    *ppdequeue = NULL;

    return (SUCCESS);
}
