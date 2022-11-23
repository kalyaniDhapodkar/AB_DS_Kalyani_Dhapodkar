


//	Header

#include	<iostream>

#include	"mv_stack.hpp"

MV_Stack<long>* p_stack = NULL;

int main(void)
{
	// Code
	p_stack = new MV_Stack<long>();

	for( long le = 1; le <= 10; ++le )
	{
		p_stack->Push( le * 10 );
	}

	p_stack->Show();

	delete(p_stack);
	p_stack = NULL;

	exit(SUCCESS);
}

