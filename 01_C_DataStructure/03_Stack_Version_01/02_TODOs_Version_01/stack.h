

#ifndef  	_MV_STACK_H
#define 	_MV_STACK_H

#ifndef  	SUCCESS
#define  	SUCCESS 	0
#endif

#ifndef  	FAILURE  	
#define  	FAILURE  	1
#endif

#define  	FIRST  		1
#define   	SECOND		2

// typedef 
struct array;

typedef 	struct array  	array_t;
typedef  	struct array*   p_array_t;
typedef  	struct array**  pp_array_t;


struct stack;
typedef  	struct stack 	stack_t;
typedef  	struct stack*  	p_stack_t;
typedef  	struct stack**  pp_stack_t;

typedef  	void*   	data_t;
typedef  	data_t*   	p_data_t;

#define  	SIZE_DATA  	(sizeof(data_t))

typedef   	int   		ret_t;
typedef  	int   		stack_no_t;

// struct type definition
struct array
{
	p_data_t ptr;
	p_stack_t pstack1;
	p_stack_t pstack2;

};
#define  	SIZE_ARRAY  	(sizeof(array_t))

struct stack
{
	size_t  nr_of_elements;
	long  top;
};
#define  	SIZE_STACK  	(sizeof(stack_t))

extern  ret_t 	create_stack(void);
extern  ret_t 	stack_push_back(stack_no_t stack, data_t data);
extern  data_t 	stack_pop_back(stack_no_t stack, void (*pdeletedata)(data_t));
extern  void  	stack_print(stack_no_t stack, void (*pprintdata)(data_t));
extern  data_t 	stack_peek(stack_no_t stack);
extern 	ret_t 	stack_destroy();
#endif  	// _MV_STACK_H
