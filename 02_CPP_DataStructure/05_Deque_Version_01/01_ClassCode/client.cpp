

//	Headers
#include	<iostream>

#include	"deque.hpp"

MVDeQueue<long>*	pdequeue = NULL;

int main(void)
{
	// Code
	pdequeue = new MVDeQueue<long>();

	std::cout << "Dequeue Push Back:" << std::endl;
	for( int le = 0; le < 12; ++le )
	{
		pdequeue->PushBack( (le+1) * 12 );
	}

	std::cout << (*pdequeue);

	std::cout << "Dequeue Push Front:" << std::endl;
	for( int le = 0; le < 6; ++le )
	{
		pdequeue->PushFront( (le+1) * 17 );
	}

	std::cout << (*pdequeue);

	std::cout << "PopBack: " << std::endl;
	std::cout << "Popped Data " << pdequeue->PopBack() << std::endl;
	std::cout << "Popped Data " << pdequeue->PopBack() << std::endl;
	std::cout << "Popped Data " << pdequeue->PopBack() << std::endl;
	std::cout << "Popped Data " << pdequeue->PopBack() << std::endl << std::endl;

	std::cout << "PopFront: " << std::endl;
	std::cout << "Popped Data " << pdequeue->PopFront() << std::endl;
	std::cout << "Popped Data " << pdequeue->PopFront() << std::endl;
	std::cout << "Popped Data " << pdequeue->PopFront() << std::endl;
	std::cout << "Popped Data " << pdequeue->PopFront() << std::endl << std::endl;

	std::cout << (*pdequeue);

	delete(pdequeue);

	return(SUCCESS);
}

