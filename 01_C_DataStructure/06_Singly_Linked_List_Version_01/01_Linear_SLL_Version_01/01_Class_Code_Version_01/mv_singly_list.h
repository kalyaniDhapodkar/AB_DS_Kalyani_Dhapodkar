


#ifndef _MV_SINGLY_LIST_H
#define _MV_SINGLY_LIST_H

//	Constant Literals
#ifndef SUCCESS
#define SUCCESS 0
#endif

#ifndef FAILURE
#define FAILURE 1
#endif

//	Types and Typedefs
struct list_node;

typedef struct list_node node_t;
typedef struct list_node *p_node_t;
typedef struct list_node **pp_node_t;

struct mv_singly_list;

typedef struct mv_singly_list mv_singly_list_t;
typedef struct mv_singly_list *p_mv_singly_list_t;
typedef struct mv_singly_list **pp_mv_singly_list_t;

typedef mv_singly_list_t mv_sll_t;
typedef p_mv_singly_list_t p_mv_sll_t;
typedef pp_mv_singly_list_t pp_mv_sll_t;

typedef void *data_t;
typedef int ret_t;

typedef void (*SHOWDATAPROC)(data_t);
typedef void (*DELETEDATAPROC)(data_t);

//	Type Definitions

//	List Node Struct Definition
struct list_node
{
	data_t key;		 //	data
	p_node_t p_next; //	self referential pointer
};
#define SIZE_NODE (sizeof(node_t))

//	List struct definition
struct mv_singly_list
{
	p_node_t p_head; //	The first element of list
	p_node_t p_tail; //	The last element of list
	size_t size;	 //	Total count of elements in list
};
#define SIZE_LIST (sizeof(mv_singly_list_t))

//	List Interface Functions

extern p_mv_sll_t create_singly_list(void);

//	List Data Insertion Functions
extern ret_t mv_sll_insert_front(p_mv_sll_t plist, data_t new_data);
extern ret_t mv_sll_insert_back(p_mv_sll_t plist, data_t new_data);
extern ret_t mv_sll_insert_at(p_mv_sll_t plist, data_t new_data, long index);
extern ret_t mv_sll_insert_before(p_mv_sll_t plist, data_t new_data, data_t e_data); 
extern ret_t mv_sll_insert_after(p_mv_sll_t plist, data_t new_data, data_t e_data);

//	List Data Removal Functions
extern data_t mv_sll_remove_front(p_mv_sll_t plist);
extern data_t mv_sll_remove_back(p_mv_sll_t plist);
extern data_t mv_sll_remove_at(p_mv_sll_t plist, long index);
extern data_t mv_sll_remove_before(p_mv_sll_t plist, data_t e_data);
extern data_t mv_sll_remove_after(p_mv_sll_t plist, data_t e_data);

//	List Traversal Functions
extern ret_t mv_sll_print_forward(p_mv_sll_t plist, SHOWDATAPROC pshowdataproc);

//	List Getter Functions
extern data_t mv_sll_get_head(p_mv_sll_t plist);
extern data_t mv_sll_get_tail(p_mv_sll_t plist);
extern data_t mv_sll_get_data(p_mv_sll_t plist, long index);
extern size_t mv_sll_get_size(p_mv_sll_t plist);

//	List Destroy Function
extern ret_t mv_sll_destroy(pp_mv_sll_t pplist, DELETEDATAPROC pdeletedataproc);

#endif /* _MV_SINGLY_LIST_H */
