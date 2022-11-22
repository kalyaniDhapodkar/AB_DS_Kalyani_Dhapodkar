

//	Header
#include	<stdio.h>
#include	<stdlib.h>

#include	"mv_stack.h"

struct Demo
{
	long	lnum1;
	char 	ch;
};
#define		SIZE_DEMO		(sizeof(struct Demo))
typedef	struct Demo 	demo_t;
typedef	struct Demo* 	p_demo_t;

p_mv_stack_t	pstack_int = NULL;

p_mv_stack_t 	pstack_demo = NULL;

void print_data_int(data_t data)
{
	// Code
	fprintf(stdout,"|\t%lld\t|\n", (long long ) data);
}

void print_data_demo(data_t data)
{
	//	Code
	p_demo_t pdemo = (p_demo_t)data;

	fprintf(stdout, "|   {%ld | %c}   |\n", pdemo->lnum1, pdemo->ch);
}

void delete_data_demo(data_t data)
{
	//	Code
	p_demo_t pdemo = (p_demo_t)data;

	fprintf(stdout, "Deleting : |\t {%ld | %c} \t|\n", pdemo->lnum1, pdemo->ch);
}

int main(void)
{
	//	Code

	/********************************************************\
	 * 				STACK for INTEGER DATA
	\********************************************************/

	pstack_int = create_stack();

	mv_stack_push(pstack_int, (data_t) 10);
	mv_stack_push(pstack_int, (data_t) 20);
	mv_stack_push(pstack_int, (data_t) 30);
	mv_stack_push(pstack_int, (data_t) 40);
	mv_stack_push(pstack_int, (data_t) 50);
	mv_stack_push(pstack_int, (data_t) 60);

	//	Stack Print;
	mv_stack_print(pstack_int, print_data_int);

	fprintf(stdout, "popped data:");
	print_data_int( mv_stack_pop(pstack_int) );
	fprintf(stdout, "\n");
	
	fprintf(stdout, "popped data:");
	print_data_int( mv_stack_pop(pstack_int) );
	fprintf(stdout, "\n");
	
	fprintf(stdout, "popped data:");
	print_data_int( mv_stack_pop(pstack_int) );
	fprintf(stdout, "\n");

	mv_stack_print(pstack_int, print_data_int);

	mv_stack_destroy(&pstack_int);

	mv_stack_print(pstack_int, print_data_int);

	/********************************************************\
	 * 				STACK for STRUCT DEMO
	\********************************************************/
	pstack_demo = create_stack();

	//	Push Demo Data
	p_demo_t pdemo = (p_demo_t)malloc(SIZE_DEMO);
	pdemo->lnum1 = 123;
	pdemo->ch = 'M';
	mv_stack_push(pstack_demo, pdemo);

	pdemo = (p_demo_t)malloc(SIZE_DEMO);
	pdemo->lnum1 = 456;
	pdemo->ch = 'A';
	mv_stack_push(pstack_demo, pdemo);

	pdemo = (p_demo_t)malloc(SIZE_DEMO);
	pdemo->lnum1 = 789;
	pdemo->ch = 'R';
	mv_stack_push(pstack_demo, pdemo);

	pdemo = (p_demo_t)malloc(SIZE_DEMO);
	pdemo->lnum1 = 980;
	pdemo->ch = 'S';
	mv_stack_push(pstack_demo, pdemo);

	pdemo = (p_demo_t)malloc(SIZE_DEMO);
	pdemo->lnum1 = 135;
	pdemo->ch = 'V';
	mv_stack_push(pstack_demo, pdemo);

	pdemo = (p_demo_t)malloc(SIZE_DEMO);
	pdemo->lnum1 = 246;
	pdemo->ch = 'O';
	mv_stack_push(pstack_demo, pdemo);

	pdemo = (p_demo_t)malloc(SIZE_DEMO);
	pdemo->lnum1 = 357;
	pdemo->ch = 'I';
	mv_stack_push(pstack_demo, pdemo);

	pdemo = (p_demo_t)malloc(SIZE_DEMO);
	pdemo->lnum1 = 975;
	pdemo->ch = 'D';
	mv_stack_push(pstack_demo, pdemo);

	//	Print Demo Data
	mv_stack_print(pstack_demo, print_data_demo);

	//	Pop Demo Data
	pdemo = mv_stack_pop(pstack_demo);
	fprintf(stdout, "popped data:");
	print_data_demo( pdemo );
	fprintf(stdout, "\n");
	if( pdemo )
	{
		free(pdemo);
		pdemo = NULL;
	};

	pdemo = mv_stack_pop(pstack_demo);
	fprintf(stdout, "popped data:");
	print_data_demo( pdemo );
	fprintf(stdout, "\n");
	if( pdemo )
	{
		free(pdemo);
		pdemo = NULL;
	}

	pdemo = mv_stack_pop(pstack_demo);
	fprintf(stdout, "popped data:");
	print_data_demo( pdemo );
	fprintf(stdout, "\n");
	if( pdemo )
	{
		free(pdemo);
		pdemo = NULL;
	}

	pdemo = mv_stack_pop(pstack_demo);
	fprintf(stdout, "popped data:");
	print_data_demo( pdemo );
	fprintf(stdout, "\n");
	if( pdemo )
	{
		free(pdemo);
		pdemo = NULL;
	}

	mv_stack_print(pstack_demo, print_data_demo);

	mv_stack_destroy(&pstack_demo);

	mv_stack_print(pstack_demo, print_data_demo);

	exit(SUCCESS);
}

