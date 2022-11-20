

#ifndef		_MV_STACK_H
#define		_MV_STACK_H

//	Header
#include	"mv_vector.h"

//	Macros
#ifndef		SUCCESS
#define		SUCCESS		0
#endif		

#ifndef		FAILURE	
#define		FAILURE		1
#endif	

//	Type definitions

struct mv_stack;	//	declaration

typedef		struct mv_stack 	mv_stack_t;
typedef		struct mv_stack*	p_mv_stack_t;
typedef		struct mv_stack**	pp_mv_stack_t;

typedef		int 	ret_t;

// 	Struct type definition
struct 	mv_stack
{
	p_mv_vector_t	pvector;
};
#define		SIZE_STACK		(sizeof(mv_stack_t))

//	Stack Interface Functions

extern	p_mv_stack_t 	create_stack(void);

extern	ret_t	mv_stack_push(p_mv_stack_t pstack, data_t data);

extern	data_t	mv_stack_pop(p_mv_stack_t pstack);

extern	data_t	mv_stack_peek(p_mv_stack_t pstack);

extern	void 	mv_stack_print(p_mv_stack_t pstack, void (*pPrintDataFunc) (data_t) );

extern	ret_t	mv_stack_destroy(pp_mv_stack_t ppstack);

#endif		/* _MV_STACK_H */
