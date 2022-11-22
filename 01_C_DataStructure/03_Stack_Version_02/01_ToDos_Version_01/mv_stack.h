

#ifndef  	_MV_STACK_H
#define  	_MV_STACK_H

// Header File
#include 	"mv_dcll.h"

// Macros
#ifndef  	SUCCESS
#define  	SUCCESS  	0
#endif

#ifndef  	FAILURE
#define  	FAILURE  	1
#endif

// Type Definitions

struct mv_stack;  	// Declaration

typedef  	struct mv_stack  	mv_stack_t;
typedef  	struct mv_stack*  	p_mv_stack_t;
typedef  	struct mv_stack** 	pp_mv_stack_t;

typedef  	void*  	data_t;
typedef  	int  	ret_t;

// Struct type Definition
struct mv_stack
{
	p_mv_dcll_t  	pdcll;
};
#define  	SIZE_STACK  	(sizeof(mv_stack_t))

// Stack Interface Functions

// Stack Creation Function
extern  	p_mv_stack_t  	create_stack(void);

// Stack Insertion Function
extern  ret_t  	mv_stack_push(p_mv_stack_t pstack, data_t data);

// Stack Removal Function
extern  data_t  mv_stack_pop(p_mv_stack_t pstack);

// Stack getter Function
extern  data_t  mv_stack_peek(p_mv_stack_t pstack);

// Stack Print Function
extern  void  	mv_stack_print(p_mv_stack_t pstack, void (*pPrintDataFunc)(data_t) );

// Stack Destroy Function
extern  ret_t  	mv_stack_destroy(pp_mv_stack_t ppstack);

#endif	/* _MV_STACK_H */


