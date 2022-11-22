


/**
 * @file    mv_singly_list.h
 * @author  MarshallingVoid (marshallingvoid@gmail.com)
 * @brief   This file constains all the singly linked list related interface function's declarations and
 *          type declarations/definitions.
 * @date    21-11-2022
 * @version 1.0
 *
 * @copyright   Copyrights (c) 2022
 * 
 */

#ifndef     _MV_SINGLY_LIST_H
#define     _MV_SINGLY_LIST_H

// Constant Literals
#ifndef     SUCCESS     
#define     SUCCESS     0
#endif 

#ifndef     FAILURE
#define     FAILURE     1
#endif

// Types and Typedefs
struct list_node;

typedef     struct list_node    node_t;
typedef     struct list_node*   p_node_t;
typedef     struct list_node**  pp_node_t;

struct mv_singly_list;

typedef     struct mv_singly_list   mv_singly_list_t;
typedef     struct mv_singly_list*  p_mv_singly_list_t;
typedef     struct mv_singly_list** pp_mv_singly_list_t;

typedef     mv_singly_list_t    mv_sll_t;
typedef     p_mv_singly_list_t  p_mv_sll_t;
typedef     pp_mv_singly_list_t  pp_mv_sll_t;

typedef     void*   data_t;
typedef     int     ret_t;

typedef     void (*SHOWDATAPROC)(data_t);
typedef     void (*DELETEDATAPROC)(data_t);
typedef     ret_t (*COMPAREEQUALITYDATAPROC)(data_t, data_t);

// Type Definitions

// List Node Struct Definition
struct list_node
{
    data_t  key;
    p_node_t p_next;
};
#define     SIZE_NODE   sizeof(node_t)

// List Struct Definition
struct mv_singly_list
{
    p_node_t p_head;
    p_node_t p_tail;
    size_t  size;
};
#define     SIZE_LIST   (sizeof(mv_singly_list_t))

// List Interface Function

// List Creation Function
extern p_mv_sll_t   create_singly_list(void);

// List Insertion Functions
extern ret_t    mv_sll_insert_front(p_mv_sll_t plist, data_t new_data);
extern ret_t    mv_sll_insert_back(p_mv_sll_t plist, data_t new_data);
extern ret_t    mv_sll_insert_at(p_mv_sll_t plist, data_t new_data, size_t index);
extern ret_t    mv_sll_insert_before(p_mv_sll_t plist, data_t new_data, data_t e_data, COMPAREEQUALITYDATAPROC pcompareproc);
extern ret_t    mv_sll_insert_after(p_mv_sll_t plist, data_t new_data, data_t e_data, COMPAREEQUALITYDATAPROC pcompareproc);

// List Removal Functions
extern data_t   mv_sll_remove_front(p_mv_sll_t plist);
extern data_t   mv_sll_remove_back(p_mv_sll_t plist);
extern data_t   mv_sll_remove_at(p_mv_sll_t plist, size_t index);
extern data_t   mv_sll_remove_before(p_mv_sll_t plist, data_t e_data, COMPAREEQUALITYDATAPROC pcompareproc);
extern data_t   mv_sll_remove_after(p_mv_sll_t plist, data_t e_data, COMPAREEQUALITYDATAPROC pcompareproc);

// List Printing Functions
extern ret_t    mv_sll_print_forward(p_mv_sll_t plist, SHOWDATAPROC pshowdataproc);
extern ret_t    mv_sll_print_reverse(p_mv_sll_t plist, SHOWDATAPROC pshowdataproc);


// List Getter Functions
extern data_t   mv_sll_get_head(p_mv_sll_t plist);
extern data_t   mv_sll_get_tail(p_mv_sll_t plist);

extern data_t   mv_sll_get_data(p_mv_sll_t plist, size_t indexe);

extern size_t   mv_sll_get_size(p_mv_sll_t plist);

// List Destroy Function
extern ret_t    mv_sll_destroy(pp_mv_sll_t pplist, DELETEDATAPROC pdeletedataproc);

#endif  /* _MV_SINGLY_LIST_H */

