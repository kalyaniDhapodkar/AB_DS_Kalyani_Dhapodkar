


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

/**
 * @function: Create List Function
 * @params:	void
 * @returns: a pointer to singly list object
 */
extern p_mv_sll_t create_singly_list(void);

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
extern ret_t mv_sll_insert_front(p_mv_sll_t plist, data_t new_data);

/**
 * @function: Insert data in BACK of singly list'
 * @params:	1)	List
 * 			2)	New Data
 * @returns:	Status of insertion at BACK
 * 			returns SUCCESS for successful insertion
 * 			OR
 * 			returns FAILURE for un-successful insertion
 */
extern ret_t mv_sll_insert_back(p_mv_sll_t plist, data_t new_data);

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
extern ret_t mv_sll_insert_at(p_mv_sll_t plist, data_t new_data, long index);

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
extern ret_t mv_sll_insert_before(p_mv_sll_t plist, data_t new_data, data_t e_data); 

/**
 * @function: Insert Data AFTER a specific existing data
 * @params:	1) List
 * 			2) New Data
 * 			3) Existing Data
 * @returns: Status of insertion AFTER an existing data
 * 			returns SUCCESS for successful insertion
 * 			OR
 * 			returns FAILURE for un-successful insertion
 */
extern ret_t mv_sll_insert_after(p_mv_sll_t plist, data_t new_data, data_t e_data);

//	List Data Removal Functions
/**
 * @function: Remove Data from FRONT of the list
 * @params:	1) List
 * @returns: Removed Data from list
 * 			returns a valid data if remove successful
 * 			OR
 * 			return NULL if unsuccessful
 */
extern data_t mv_sll_remove_front(p_mv_sll_t plist);

/**
 * @function: Remove Data from BACK of the list
 * @params: 1) List
 * @returns: Removed Data from list
 * 			returns a valid data if remove successful
 * 			OR
 * 			returns NULL if unsuccessful
 */
extern data_t mv_sll_remove_back(p_mv_sll_t plist);

/**
 * @function: Remove Data from a specific INDEX
 * @params: 1) List
 * 			2) INDEX
 * @return: Removed data from list
 * 			returns a valid data if remove successful
 * 			OR
 * 			returns NULL if unsuccessful
 */
extern data_t mv_sll_remove_at(p_mv_sll_t plist, long index);

/**
 * @function: Remove Data from BEFORE of an existing data
 * @params:	1) List
 * 			2) Existing Data
 * @returns: Removed Data from list
 * 			returns a valid data if remove succssful
 * 			OR
 * 			returns NULL if unsuccessful
 */
extern data_t mv_sll_remove_before(p_mv_sll_t plist, data_t e_data);

/**
 * @function: Remove Data from AFTER of an existing data
 * @params: 1) List
 * 			2) Existing Data
 * @returns: Removed Data from list
 * 			returns a valid data from list if successful
 * 			OR
 * 			returns NULL if unsuccessful
 */
extern data_t mv_sll_remove_after(p_mv_sll_t plist, data_t e_data);

//	List Traversal Functions
/**
 * @function: Prints data present in the list in forward manner
 * @params:	1) List
 * 			2) Function Pointer to print data
 * @returns: SUCCESS for successful print
 */
extern ret_t mv_sll_print_forward(p_mv_sll_t plist, SHOWDATAPROC pshowdataproc);

/**
 * @function: Prints data present in the list in reverse manner
 * @params: 1) List
 * 			2) Function Pointer to print data
 * @returns: SUCCESS for successful print
 */
extern ret_t mv_sll_print_reverse(p_mv_sll_t plist, SHOWDATAPROC pshowdataproc);

//	List Getter Functions
/**
 * @function: Get The FIRST element from list
 * @params: 1) List
 * @returns: FIRST Element if present OR returns NULL
 */
extern data_t mv_sll_get_head(p_mv_sll_t plist);

/**
 * @function: Get the LAST element from list
 * @params: 1) List
 * @returns: LAST element if present OR returns NULL
 */
extern data_t mv_sll_get_tail(p_mv_sll_t plist);

/**
 * @function: Get data from specific index
 * @params: 1) List
 * 			2) INDEX
 * @returns: DATA from a specific INDEX of list OR NULL
 */
extern data_t mv_sll_get_data(p_mv_sll_t plist, long index);

/**
 * @function: Get the SIZE of list
 * @params: 1) List
 * @returns: Count of elements present in list
 */
extern size_t mv_sll_get_size(p_mv_sll_t plist);

//	List Destroy Function
/**
 * @function: Destroy the existing list
 * @params:	1) Pointer To LIST
 * 			2) Callback function for destroy data
 * @returns: SUCCESS for successful destroy
 * 			 OR
 * 			 FAILURE if no data present
 */
extern ret_t mv_sll_destroy(pp_mv_sll_t pplist, DELETEDATAPROC pdeletedataproc);

#endif /* _MV_SINGLY_LIST_H */
