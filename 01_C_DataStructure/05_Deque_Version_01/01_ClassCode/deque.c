
//  Headers

#include <stdio.h>
#include <stdlib.h>

#include "deque.h"

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
        status = ERROR_CHECKING(NULL != pdequeue->dequeue,
                                NULL == pdequeue->dequeue,
                                "ERROR: Queue Not Found",
                                deallocate_dequeue,
                                (void *)&pdequeue);

        RETURN_FAILURE(status);
    }

    //  Dequeue Overflow
    if (condition_to_check & CHECK_OVERFLOW)
    {
        status = ERROR_CHECKING(pdequeue->no_of_elements != pdequeue->length,
                                pdequeue->no_of_elements == pdequeue->length,
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

    pdequeue->dequeue = (p_data_t)Xcalloc(DEQUEUE_DEFAULT_SIZE, SIZE_DATA);

    status = ERROR_CHECKING(NULL != pdequeue->dequeue,
                            NULL == pdequeue->dequeue,
                            "ERROR: DeQueue Cannot be created",
                            deallocate_dequeue,
                            (void *)&pdequeue);

    pdequeue->head = 0;
    pdequeue->tail = 0;
    pdequeue->length = DEQUEUE_DEFAULT_SIZE;
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

    pdequeue->dequeue = (p_data_t)Xcalloc(nr_of_elements, SIZE_DATA);

    status = ERROR_CHECKING(NULL != pdequeue->dequeue,
                            NULL == pdequeue->dequeue,
                            "ERROR: DeQueue Cannot be created",
                            deallocate_dequeue,
                            (void *)&pdequeue);

    pdequeue->head = 0;
    pdequeue->tail = 0;
    pdequeue->length = nr_of_elements;
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

    pdequeue->head--;

    if (-1 == pdequeue->head)
    {
        pdequeue->head = pdequeue->length - 1;
    }

    pdequeue->dequeue[pdequeue->head] = data;

    pdequeue->no_of_elements++;

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

    pdequeue->dequeue[pdequeue->tail] = data;
    pdequeue->tail++;

    if (pdequeue->length == pdequeue->tail)
    {
        pdequeue->tail = 0;
    }

    pdequeue->no_of_elements++;

    return (SUCCESS);
}

extern data_t mv_dequeue_dequeue_front(p_mv_dequeue_t pdequeue)
{
    // Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT_ARRAY | CHECK_UNDERFLOW);

    RETURN_NULL(status);

    data_t to_return_data = pdequeue->dequeue[pdequeue->head];

    pdequeue->head++;

    if (pdequeue->head == pdequeue->length)
    {
        pdequeue->head = 0;
    }

    pdequeue->no_of_elements--;
    return (to_return_data);
}

extern data_t mv_dequeue_dequeue_back(p_mv_dequeue_t pdequeue)
{
    //  Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT_ARRAY | CHECK_UNDERFLOW);

    RETURN_NULL(status);

    pdequeue->tail--;

    if (-1 == pdequeue->tail)
    {
        pdequeue->tail = pdequeue->length - 1;
    }
    data_t to_return_data = pdequeue->dequeue[pdequeue->tail];

    pdequeue->no_of_elements--;
    return (to_return_data);
}

//  Queue Length
extern size_t mv_dequeue_size(p_mv_dequeue_t pdequeue)
{
    // Code
    ret_t status = check_dequeue_conditions(pdequeue, CHECK_OBJECT_ARRAY);

    RETURN_FAILURE(status);

    return (pdequeue->length);
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

    // fprintf(stdout, "\nDequeue:\n");
    fprintf(stdout, "{START}-");
    for (long long le = pdequeue->head; le != pdequeue->tail; ++le)
    {
        if (le == pdequeue->length)
            le = 0;
        pprintfunc(pdequeue->dequeue[le]);
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
    fprintf(stdout, "{START}-");
    for (long long le = pdequeue->head; le != pdequeue->tail; ++le)
    {
        if (le == pdequeue->length)
            le = 0;

        pdeletefunc(pdequeue->dequeue[le]);
        pdequeue->dequeue[le] = NULL;
    }
    fprintf(stdout, "{END}\n");

    // Deallocate array
    if (pdequeue->dequeue)
    {
        free(pdequeue->dequeue);
        pdequeue->dequeue = NULL;
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
