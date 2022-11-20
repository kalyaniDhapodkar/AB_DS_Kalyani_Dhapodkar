

#include <stdio.h>
#include <stdlib.h>

#include "mv_stack.h"

#define 	MAX_ELEMENT  20

static p_array_t gparray = NULL;

//	Function Declaration
static	ret_t	error_checking(	const int 	assert_condition,
								const char* assert_condition_str,
								const char*	file_name,
								const long	line_no,
								const int 	error_condition,
								const char*	error_str);

//	Macros
#define		ERROR_CHECKING( assert_condition, error_condition, error_str )		(											\
																					error_checking( assert_condition,		\
																									#assert_condition,		\
																									__FILE__,				\
																									__LINE__,				\
																									error_condition,		\
																									error_str )				\
																				)


//	Stack Helper Functions
/*
	Function Name 	: xmalloc
	Description 	: alloacate memory of given size
	Input Params 	: 1. no_of_bytes
	Return  		: pointer to allocated memory block
*/

static void* xmalloc(size_t no_of_bytes)
{
	void* p = malloc(no_of_bytes);

	ERROR_CHECKING(	1, 
					NULL == p,
					"ERROR: Out Of Memory.\n");

	return(p);
}

/*
	Function Name 	: xcalloc
	Description 	: alloacate continous memory of given size
	Input Params 	: 1. no_of_elements
					  2. no_of_bytes
	Return  		: pointer to allocated memory block
*/

static  void* xcalloc(size_t no_of_elements, size_t no_of_bytes)
{
	void* p = calloc(no_of_elements, no_of_bytes);

	ERROR_CHECKING(	1, 
					NULL == p,
					"ERROR: Out Of Memory.\n");

	return(p);
}

/*
	Function Name 	: error_checking
	Description 	: function do assertion if DEBUG is define
					  else error checking
	Input Params 	: 1. assertion condition
					  2. assertion condition string
					  3. File Name
					  4. Line Number
					  5. Error Checking
					  6. Error string
*/

static	ret_t	error_checking(	const int 	assert_condition,
								const char* assert_condition_str,
								const char*	file_name,
								const long	line_no,
								const int 	error_condition,
								const char*	error_str)
{
	// Code

	#ifdef	MV_DEBUG
		//	Assertion
		if( !assert_condition )
		{
			fprintf(stdout, 
					"Assertion Filed: %s, File: %s, Line #: %ld\n", 
					assert_condition_str,
					file_name,
					line_no);
			return(FAILURE);
		}
	#else
		// Error Checking
		if( error_condition )
		{
			if( NULL != error_str )
			{
				fprintf(stderr, error_str);
				return(FAILURE);
			}
		}
	#endif

	return(SUCCESS);
}

// Array Interface Function

/*
	Function Name 	: create_array
	Description 	: creates a array of default size
	Input Params 	: 1. void
	Return  		: pointer to array created
*/

static 	p_array_t create_array(void)
{
	p_array_t parray = xmalloc(SIZE_ARRAY);

	ERROR_CHECKING(	1, 
					NULL == parray,
					"ERROR: Out Of Memory.\n");

	parray->ptr = (p_data_t)xcalloc(MAX_ELEMENT, SIZE_DATA);

	ERROR_CHECKING(	1, 
					NULL == parray->ptr,
					"ERROR: Out Of Memory.\n");

	return(parray);
}

// Array Interface Function

/*
	Function Name 	: create_stack
	Description 	: creates two stack
	Input Params 	: 1. void
	Return  		: SUCCESS - if created successfully
*/

extern  ret_t create_stack(void)
{
	p_stack_t pstack_one = xmalloc(SIZE_STACK);
	ERROR_CHECKING( NULL != pstack_one,
					0,
					NULL);

	pstack_one->nr_of_elements = 0;
	pstack_one->top = -1;

	p_stack_t pstack_two = xmalloc(SIZE_STACK);
	ERROR_CHECKING( NULL != pstack_two,
					0,
					NULL);

	pstack_two->nr_of_elements = 0;
	pstack_two->top = MAX_ELEMENT;

	gparray = create_array();
	gparray->pstack1 = pstack_one;
	gparray->pstack2 = pstack_two;

	return(SUCCESS);
}


/*
	Function Name 	: stack_push_back
	Description 	: push/adds data in stack
	Input Params 	: 1. which vector ( 1st or 2nd )
					  2. Data to be push
	Output  		: SUCCESS - if pushed/added successfully
					  FAILURE - if failed
*/

extern  ret_t stack_push_back(int stack, data_t data)
{

	ERROR_CHECKING( stack == FIRST || stack == SECOND,
					stack != FIRST && stack != SECOND,
					"ERROR: Only TWO stack availaible\n" );

	ERROR_CHECKING( NULL != data,
					NULL == data,
					"ERROR: Data is NULL.\n" );

	size_t index = 0;

	if(stack == FIRST)
	{
		gparray->pstack1->nr_of_elements++;
		gparray->pstack1->top = gparray->pstack1->top + 1;
		index = gparray->pstack1->top;
	}
	else if(stack == SECOND)
	{
		gparray->pstack2->nr_of_elements++;
		gparray->pstack2->top = gparray->pstack2->top - 1;
		index = gparray->pstack2->top;
	}

	gparray->ptr[index] = data;

	return(SUCCESS);
}


/*
	Function Name 	: stack_pop_back
	Description 	: pops last element from the stack
	Input Params 	: 1. which vector ( 1st or 2nd )
					  2. pointer to printing function(deletion)
	Output  		: data - popped data
*/

extern  data_t stack_pop_back(stack_no_t stack, void (*pdeletedata)(data_t))
{
	ERROR_CHECKING( stack == FIRST || stack == SECOND,
					stack != FIRST && stack != SECOND,
					"ERROR: Only TWO stack availaible\n" );

	ERROR_CHECKING( NULL != pdeletedata,
					NULL == pdeletedata,
					"ERROR: deletedata proc is empty.\n" );

	size_t index = 0;
	if(stack == FIRST)
	{
		index = gparray->pstack1->top;
		gparray->pstack1->top--;
		gparray->pstack1->nr_of_elements--;
	}
	else if(stack == SECOND)
	{
		index = gparray->pstack2->top;
		gparray->pstack2->top++;
		gparray->pstack2->nr_of_elements--;
	}

	data_t to_return_data = gparray->ptr[index];

	return(to_return_data);
}


/*
	Function Name 	: stack_print
	Description 	: prints the stack
	Input Params 	: 1. which stack (1st or 2nd)
					  2. pointer to printing function(printing)
	Output  		: void 
*/

extern  void  stack_print(int stack, void (*pprintdata)(data_t))
{
	ERROR_CHECKING( stack == FIRST || stack == SECOND,
					stack != FIRST && stack != SECOND,
					"ERROR: Only TWO stack availaible\n" );

	ERROR_CHECKING( NULL != pprintdata,
					NULL == pprintdata,
					"ERROR: printdata proc is empty.\n" );

	if(stack == FIRST)
	{
		fprintf(stdout, "Stack 1: \n{START}-");
		for(long le = 0; le <= gparray->pstack1->top; le++)
		{
			pprintdata(gparray->ptr[le]);
		}
		fprintf(stdout, "{END}\n\n");
	}
	else if (stack == SECOND)
	{
		fprintf(stdout, "Stack 2: \n{START}-");
		for(long le = MAX_ELEMENT-1; le >= gparray->pstack2->top; le--)
		{
			pprintdata(gparray->ptr[le]);
		}
		fprintf(stdout, "{END}\n\n");
	}

}


/*
	Function Name 	: stack_peek
	Description 	: gives the peek of stack
	Input Params 	: 1. which stack (1st or 2nd)
	Output  		: peek of required stack
*/

extern  data_t 	stack_peek(stack_no_t stack)
{
	ERROR_CHECKING( stack == FIRST || stack == SECOND,
					stack != FIRST && stack != SECOND,
					"ERROR: Only TWO stack availaible\n" );

	if(stack == FIRST)
		return(gparray->ptr[gparray->pstack1->top]);

	else if(stack == SECOND)
		return(gparray->ptr[gparray->pstack2->top]);

	else
		return(0);
}


/*
	Function Name 	: stack_destroy
	Description 	: destroy the given stack
	Input Params 	: 1. void
	Output  		: SUCCESS - if destroyed successfully
*/

extern ret_t stack_destroy()
{
	if(gparray->pstack1)
	{
		gparray->pstack1->nr_of_elements = 0;
		gparray->pstack1->top = 0;
		free(gparray->pstack1);
		gparray->pstack1 = NULL;
	}

	if(gparray->pstack2)
	{
		gparray->pstack2->nr_of_elements = 0;
		gparray->pstack2->top = 0;
		free(gparray->pstack2);
		gparray->pstack2 = NULL;
	}

	free(gparray);
	gparray = NULL;

	return(SUCCESS);
}

