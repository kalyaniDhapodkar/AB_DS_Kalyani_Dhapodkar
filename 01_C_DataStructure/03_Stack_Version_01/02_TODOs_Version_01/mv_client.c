
#include <stdio.h>
#include <stdlib.h>

#include "mv_stack.h"

extern void print_data(data_t data)
{
	fprintf(stdout, "{%lld}-", (long long)data);
}

extern void delete_data(data_t data)
{
	fprintf(stdout, "{%lld}", (long long)data);
}

p_stack_t pstack = NULL;

int main(void)
{
	create_stack();
	stack_push_back(FIRST, (data_t)10);
	stack_push_back(FIRST, (data_t)30);
	stack_push_back(FIRST, (data_t)3038);
	stack_push_back(FIRST, (data_t)308);
	stack_push_back(FIRST, (data_t)320);
	stack_push_back(FIRST, (data_t)510);

	stack_push_back(SECOND, (data_t)20);
	stack_push_back(SECOND, (data_t)206);
	stack_push_back(SECOND, (data_t)230);
	stack_push_back(SECOND, (data_t)2012);
	stack_push_back(SECOND, (data_t)4035);
	stack_push_back(SECOND, (data_t)6020);

	stack_print(FIRST, print_data);
	stack_print(SECOND, print_data);

	fprintf(stdout, "Stack 1 Peek - %lld\n", (long long)stack_peek(FIRST));
	fprintf(stdout, "Stack 2 Peek - %lld\n", (long long)stack_peek(SECOND));

	stack_pop_back(FIRST, delete_data);
	stack_pop_back(FIRST, delete_data);
	stack_pop_back(FIRST, delete_data);
	stack_pop_back(FIRST, delete_data);
	stack_pop_back(SECOND, delete_data);
	stack_pop_back(SECOND, delete_data);
	stack_pop_back(SECOND, delete_data);
	stack_pop_back(SECOND, delete_data);

	stack_print(FIRST, print_data);
	stack_print(SECOND, print_data);

	fprintf(stdout, "Stack 1 Peek - %lld\n", (long long)stack_peek(FIRST));
	fprintf(stdout, "Stack 2 Peek - %lld\n", (long long)stack_peek(SECOND));

	stack_destroy();

	return(0);
}

