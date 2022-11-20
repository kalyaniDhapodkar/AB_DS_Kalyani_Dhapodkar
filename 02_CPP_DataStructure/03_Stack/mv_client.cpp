
// Headers
#include <iostream>

#include "mv_stack.hpp"

MVStack<long>* pstack = NULL;

int main(void)
{
	// Code
	pstack = new MVStack<long>();

	for(long le = 0; le < 20; le++)
		pstack->Push( (le+1) * 17 );

	std::cout << std::endl;
	std::cout << "After Stack Data Push" << std::endl;
	std::cout << (*pstack);

	std::cout << std::endl;
	std::cout << "Popped Data : " << pstack->Pop() << std::endl;
	std::cout << "Popped Data : " << pstack->Pop() << std::endl;
	std::cout << "Popped Data : " << pstack->Pop() << std::endl;
	std::cout << "Popped Data : " << pstack->Pop() << std::endl;

	std::cout << std::endl;
	std::cout << "After Stack Data Pop " << std::endl;
	std::cout << (*pstack);

	delete(pstack);

	return(SUCCESS);
}

