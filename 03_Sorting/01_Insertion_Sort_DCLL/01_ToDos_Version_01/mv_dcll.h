

/**
 * @file	mv_dcll.h
 * @author	MarshallingVoid	(marshallingvoid@gmail.com)
 * @breif	This file contains all the interface function declarations and 
 * 			type definitions required for DOUBLY CIRCULAR LINKED LIST  
 * @date	06/11/2022
 * @version	1.0
 * 
 * @copyright	Copyright (c) 2022
 * 
 */

#ifndef	_MV_DCLL_H
#define	_MV_DCLL_H

//	Constant Literals
#ifndef	SUCCESS	
#define	SUCCESS 0
#endif

#ifndef	FAILURE
#define	FAILURE	1
#endif	

//	Enums
enum
{
	FALSE = 0,
	TRUE
};

//	struct type declarations and typedefs

struct 	list_node;

typedef	struct list_node	node_t;
typedef	struct list_node*	p_node_t;
typedef	struct list_node**	pp_node_t;

struct mv_doubly_circular_list;

typedef struct mv_doubly_circular_list		mv_doubly_list_t;
typedef	struct mv_doubly_circular_list*		p_mv_doubly_list_t;
typedef	struct mv_doubly_circular_list**	pp_mv_doubly_list_t;

typedef	mv_doubly_list_t	mv_dcll_t;
typedef	p_mv_doubly_list_t	p_mv_dcll_t;
typedef	pp_mv_doubly_list_t	pp_mv_dcll_t;

typedef	void*	data_t;
typedef	int 	ret_t;

typedef	char	bool_t;

typedef		ret_t (*COMPAREDATAPROC)(data_t, data_t);
typedef		void (*SHOWDATAPROC)(data_t);
typedef		void (*DELETEDATAPROC)(data_t);

//	Struct Type Definitions
struct list_node
{
	data_t	key;
	p_node_t 	p_next;
	p_node_t 	p_prev;
};
#define	SIZE_NODE	(sizeof(node_t))

struct 	mv_doubly_circular_list
{
	p_node_t p_head;
	p_node_t p_tail;
	size_t	size;
};
#define	SIZE_DCLL	(sizeof(mv_dcll_t))

//	List Interface Functions

/**
 * @function	This function will return a pointer to an DOUBLY CIRCULAR LIST OBJECT
 * @params	
 * @returns		pointer to the created list object 
 */
extern p_mv_dcll_t	create_doubly_circular_list();

//	List Data Insertion Functions

extern ret_t mv_dcll_insert_back(p_mv_dcll_t plist, data_t new_data);

extern ret_t mv_dcll_insert_front(p_mv_dcll_t plist, data_t new_data);

extern ret_t mv_dcll_insert_at(p_mv_dcll_t plist, data_t new_data, size_t index);

extern ret_t mv_dcll_insert_before(p_mv_dcll_t plist, data_t new_data, data_t e_data, COMPAREDATAPROC  pcomparedataproc);

extern ret_t mv_dcll_insert_after(p_mv_dcll_t plist, data_t new_data, data_t e_data, COMPAREDATAPROC pcomparedataproc);


//	List Data Removal Functions

extern data_t mv_dcll_remove_back(p_mv_dcll_t plist);

extern data_t mv_dcll_remove_front(p_mv_dcll_t plist);

extern data_t mv_dcll_remove_at(p_mv_dcll_t plist, size_t index);

extern data_t mv_dcll_remove_before(p_mv_dcll_t plist, data_t e_data, COMPAREDATAPROC pcomparedataproc);

extern data_t mv_dcll_remove_after(p_mv_dcll_t plist, data_t e_data, COMPAREDATAPROC pcomparedataproc);

//	List Data Getter Functions

extern p_node_t mv_dcll_get_head(p_mv_dcll_t plist);

extern p_node_t mv_dcll_get_tail(p_mv_dcll_t plist);

extern size_t mv_dcll_get_size(p_mv_dcll_t plist);

extern bool_t mv_dcll_empty(p_mv_dcll_t plist);

//	List Show Data Functions

extern ret_t mv_dcll_print_forward(p_mv_dcll_t plist, SHOWDATAPROC pshowdataproc);

extern ret_t mv_dcll_print_reverse(p_mv_dcll_t plist, SHOWDATAPROC pshowdataproc);

extern ret_t mv_dcll_destroy(pp_mv_dcll_t pplist, DELETEDATAPROC pdeletedataproc);

#endif /* _MV_DCLL_H */
