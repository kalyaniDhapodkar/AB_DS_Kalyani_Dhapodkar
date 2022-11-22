
#include "mv_dcll.h"

#ifndef _MV_DEQUEUE_H
#define _MV_DEQUEUE_H

//  Constant Literal

#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE 1
#endif

//  Type definitions

struct mv_dequeue;

typedef struct mv_dequeue mv_dequeue_t;
typedef struct mv_dequeue* p_mv_dequeue_t;
typedef struct mv_dequeue** pp_mv_dequeue_t;

typedef void* data_t;
typedef data_t* p_data_t;
#define SIZE_DATA (sizeof(data_t))

typedef int ret_t;

typedef void (*PRINTDATAPROC)(data_t);
typedef void (*DELETEDATAPROC)(data_t);

typedef void* (*ERROR_HANDLER)(void *);

//  Struct Type Definition

struct mv_dequeue
{
    p_mv_dcll_t pdcll;
};
#define SIZE_DEQUEUE (sizeof(mv_dequeue_t))

//  Dequeue Interface Functions

//  Data Structure Creation
extern p_mv_dequeue_t mv_create_default_dequeue(void);

// extern p_mv_dequeue_t mv_create_custom_dequeue(size_t custom_size);

//  Data Insertion
extern ret_t mv_dequeue_enqueue_front(p_mv_dequeue_t pdequeue, data_t data);
extern ret_t mv_dequeue_enqueue_back(p_mv_dequeue_t pdequeue, data_t data);

//  Data Removal
extern data_t mv_dequeue_dequeue_front(p_mv_dequeue_t pdequeue);
extern data_t mv_dequeue_dequeue_back(p_mv_dequeue_t pdequeue);

//  Queue Length
// extern size_t mv_dequeue_size(p_mv_dequeue_t pdequeue);

//  Queue No of elements
extern size_t mv_dequeue_no_of_elements(p_mv_dequeue_t pdequeue);

//  Data Print
extern ret_t mv_dequeue_print_data(p_mv_dequeue_t pdequeue, PRINTDATAPROC pprintfunc);

//  Destroy Dequeue
extern ret_t mv_dequeue_destroy(pp_mv_dequeue_t ppdequeue, DELETEDATAPROC pdeletefunc);

#endif /* _MV_DEQUEUE_H */
