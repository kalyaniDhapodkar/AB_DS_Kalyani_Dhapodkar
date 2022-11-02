
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
#define CHECK_ARRAY 0x00000002

#define CHECK_OBJECT_ARRAY CHECK_OBJECT | CHECK_ARRAY

#define CHECK_OVERFLOW 0x0000004
#define CHECK_UNDERFLOW 0x00000008

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

    //  Check for array
    if (condition_to_check & CHECK_ARRAY)
    {
        status = ERROR_CHECKING(NULL != pdequeue->pvector->array,
                                NULL == pdequeue->pvector->array,
                                "ERROR: Queue Not Found",
                                deallocate_dequeue,
                                (void *)&pdequeue);

        RETURN_FAILURE(status);
    }

    //  Dequeue Overflow
    if (condition_to_check & CHECK_OVERFLOW)
    {
        status = ERROR_CHECKING(pdequeue->no_of_elements != pdequeue->capacity,
                                pdequeue->no_of_elements == pdequeue->capacity,
                                "ERROR: Dequeue Overflow",
                                NULL,
                                NULL);
        RETURN_FAILURE(status);
    }

    //  Dequeue Underflow
    if (condition_to_check & CHECK_UNDERFLOW)
    {
        status = ERROR_CHECKING(0 != pdequeue->no_of_elements,
                                0 == pdequeue->no_of_elements,
                                "ERROR: Dequeue Underflow",
                                NULL,
                                NULL);
        RETURN_FAILURE(status);
    }

    return (status);
}

//  Dequeue Interface Functions

//  Data Structure Creation
extern p_mv_dequeue_t create_default_dequeue()
{
    //  Code
    p_mv_dequeue_t pdequeue = (p_mv_dequeue_t)Xmalloc(SIZE_DEQUEUE);

    ret_t status = ERROR_CHECKING(NULL != pdequeue,
                                  NULL == pdequeue,
                                  "ERROR: DeQueue Cannot be created",
                                  NULL,
                                  NULL);

    _EXIT_FAILURE(status);

    pdequeue->pvector = create_vector();

    pdequeue->pvector->array = (p_data_t)Xcalloc(DEQUEUE_DEFAULT_SIZE, SIZE_DATA);

    status = ERROR_CHECKING(NULL != pdequeue->pvector->array,
                            NULL == pdequeue->pvector->array,
                            "ERROR: DeQueue Cannot be created",
                            deallocate_dequeue,
                            (void *)&pdequeue);

    pdequeue->head = 0;
    pdequeue->tail = 0;
    pdequeue->capacity = DEQUEUE_DEFAULT_SIZE;
    pdequeue->no_of_elements = 0;

    return (pdequeue);
}

extern p_mv_dequeue_t create_custom_dequeue(size_t nr_of_elements)
{
    //  Code
    p_mv_dequeue_t pdequeue = (p_mv_dequeue_t)Xmalloc(SIZE_DEQUEUE);

    ret_t status = ERROR_CHECKING(NULL != pdequeue,
                                  NULL == pdequeue,
                                  "ERROR: DeQueue Cannot be created",
                                  NULL,
                                  NULL);

    _EXIT_FAILURE(status);

    pdequeue->pvector = create_vector();

    pdequeue->pvector->array = (p_data_t)Xcalloc(nr_of_elements, SIZE_DATA);

    status = ERROR_CHECKING(NULL != pdequeue->pvector->array,
                            NULL == pdequeue->pvector->array,
                            "ERROR: DeQueue Cannot be created",
                            deallocate_dequeue,
                            (void *)&pdequeue);

    pdequeue->head = 0;
    pdequeue->tail = 0;
    pdequeue->capacity = nr_of_elements;
    pdequeue->no_of_elements = 0;

    return (pdequeue);
}

extern ret_t mv_dequeue_enqueue_front(p_mv_dequeue_t pdequeue, data_t data)
{
    // Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT_ARRAY | CHECK_OVERFLOW);

    RETURN_FAILURE(status);

    status = ERROR_CHECKING(NULL != data,
                            NULL == data,
                            "ERROR: Data not found to add.\n",
                            NULL,
                            NULL);
    RETURN_FAILURE(status);

    pdequeue->no_of_elements++;

    if (pdequeue->capacity >= pdequeue->no_of_elements)
    {
         pdequeue->capacity =  pdequeue->capacity * 2;
         pdequeue->pvector->array = (p_data_t)realloc( pdequeue->pvector->array,  pdequeue->capacity * SIZE_DATA);
    }

    for(long le = pdequeue->no_of_elements-1; le > 0; le--)
    {
        pdequeue->pvector->array[le] = pdequeue->pvector->array[le-1];
    }

    pdequeue->pvector->array[0] = data;
    pdequeue->tail++;

    return (SUCCESS);
}

extern ret_t mv_dequeue_enqueue_back(p_mv_dequeue_t pdequeue, data_t data)
{
    // Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT_ARRAY | CHECK_OVERFLOW);

    RETURN_FAILURE(status);

    status = ERROR_CHECKING(NULL != data,
                            NULL == data,
                            "ERROR: Data not found to add",
                            NULL,
                            NULL);

    RETURN_FAILURE(status);

    pdequeue->pvector->array[pdequeue->tail] = data;
    pdequeue->tail++;

    if (pdequeue->capacity == pdequeue->tail)
    {
         pdequeue->pvector->capacity =  pdequeue->pvector->capacity * 2;
         pdequeue->pvector->array = (p_data_t)Xrealloc( pdequeue->pvector->array,  pdequeue->pvector->capacity * SIZE_DATA);
    }

    pdequeue->no_of_elements++;

    return (SUCCESS);
}

extern data_t mv_dequeue_dequeue_front(p_mv_dequeue_t pdequeue)
{
    //  Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT_ARRAY | CHECK_UNDERFLOW);

    RETURN_NULL(status);

    data_t to_return_data = pdequeue->pvector->array[0];

    for(size_t le = 0; le < pdequeue->no_of_elements-1; le++)
    {
        pdequeue->pvector->array[le] = pdequeue->pvector->array[le+1];
    }

    pdequeue->no_of_elements--;

    if(pdequeue->no_of_elements < pdequeue->capacity/2)
    {
        pdequeue->capacity = pdequeue->capacity / 2;
        pdequeue->pvector->array = (p_data_t)Xrealloc(pdequeue->pvector->array, pdequeue->capacity * SIZE_DATA);
    }

    pdequeue->tail--;

    return(to_return_data);
}

extern data_t mv_dequeue_dequeue_back(p_mv_dequeue_t pdequeue)
{
    //  Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT_ARRAY | CHECK_UNDERFLOW);

    RETURN_NULL(status);

    data_t to_return_data = pdequeue->pvector->array[pdequeue->no_of_elements-1];

    pdequeue->no_of_elements--;

    if(pdequeue->no_of_elements < pdequeue->capacity/2)
    {
        pdequeue->capacity = pdequeue->capacity / 2;
        pdequeue->pvector->array = (p_data_t)Xrealloc(pdequeue->pvector->array, pdequeue->capacity * SIZE_DATA);
    }

    pdequeue->tail--;

    return(to_return_data);
}

//  Queue capacity
extern size_t mv_dequeue_size(p_mv_dequeue_t pdequeue)
{
    // Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT_ARRAY);

    RETURN_FAILURE(status);

    return (pdequeue->pvector->capacity);
}

//  Queue No of elements
extern size_t mv_dequeue_no_of_elements(p_mv_dequeue_t pdequeue)
{
    // Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT_ARRAY);

    RETURN_FAILURE(status);

    return (pdequeue->no_of_elements);
}

//  Data Print
extern ret_t mv_dequeue_print_data(p_mv_dequeue_t pdequeue, PRINTDATAPROC pprintfunc)
{
    // Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT_ARRAY);
    RETURN_FAILURE(status);

    status = ERROR_CHECKING(NULL != pprintfunc,
                            NULL == pprintfunc,
                            "ERROR: Print callback must be provided",
                            NULL,
                            NULL);
    RETURN_FAILURE(status);

    fprintf(stdout, "\nDequeue:\n");
    fprintf(stdout, "{START}-");
    for (long long le = 0; le < pdequeue->no_of_elements; ++le)
    {
        pprintfunc(pdequeue->pvector->array[le]);
    }
    fprintf(stdout, "{END}\n");

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

    status = check_dequeue_conditions(pdequeue, CHECK_OBJECT_ARRAY);
    RETURN_FAILURE(status);

    status = ERROR_CHECKING(NULL != pdeletefunc,
                            NULL == pdeletefunc,
                            "ERROR: Print callback must be provided",
                            NULL,
                            NULL);
    RETURN_FAILURE(status);

    fprintf(stdout, "\nDeleting Data of Dequeue:\n");
    fprintf(stdout, "{START}\n");
    for (long long le = pdequeue->head; le != pdequeue->tail; ++le)
    {
        if (le == pdequeue->capacity)
            le = 0;

        pdeletefunc(pdequeue->pvector->array[le]);
        pdequeue->pvector->array[le] = NULL;
    }
    fprintf(stdout, "{END}\n");

    // Deallocate array
    if (pdequeue->pvector->array)
    {
        free(pdequeue->pvector->array);
        pdequeue->pvector->array = NULL;
    }

    // Deallocate Struct object
    if (pdequeue)
    {
        free(pdequeue);
        pdequeue = NULL;
    }

    *ppdequeue = NULL;

    return (SUCCESS);
}
