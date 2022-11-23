

//	Headers
#include	<iostream>

#include	"mv_deque_header.hpp"

MVDeQueue<long>*	pdequeue = NULL;

int main(void)
{
	// Code
	pdequeue = new MVDeQueue<long>();

	std::cout << "Dequeue Enque Back:" << std::endl;
	for( int le = 0; le < 12; ++le )
	{
		pdequeue->EnqueBack( (le+1) * 12 );
	}

	std::cout << (pdequeue) << std::endl;

	std::cout << "Dequeue Enque Front:" << std::endl;
	for( int le = 0; le < 6; ++le )
	{
		pdequeue->EnqueFront( (le+1) * 17 );
	}
	std::cout << (pdequeue) << std::endl;

	std::cout << "Size: " << pdequeue->QSize() << std::endl << std::endl;

	std::cout << "DequeBack: " << std::endl;
	std::cout << "Dequed Data " << pdequeue->DequeBack() << std::endl;
	std::cout << "Dequed Data " << pdequeue->DequeBack() << std::endl;
	std::cout << "Dequed Data " << pdequeue->DequeBack() << std::endl;
	std::cout << "Dequed Data " << pdequeue->DequeBack() << std::endl << std::endl;

	std::cout << (pdequeue) << std::endl;

	std::cout << "Size: " << pdequeue->QSize() << std::endl << std::endl;

	std::cout << "DequeFront: " << std::endl;
	std::cout << "Dequed Data " << pdequeue->DequeFront() << std::endl;
	std::cout << "Dequed Data " << pdequeue->DequeFront() << std::endl;
	std::cout << "Dequed Data " << pdequeue->DequeFront() << std::endl;
	std::cout << "Dequed Data " << pdequeue->DequeFront() << std::endl << std::endl;

	std::cout << (pdequeue) << std::endl;

	std::cout << "Size: " << pdequeue->QSize() << std::endl << std::endl;

	delete(pdequeue);

	std::cout << "Size: " << pdequeue->QSize() << std::endl << std::endl;
	std::cout << (pdequeue) << std::endl;

	std::cout << "--------------END-----------------" << std::endl;

	return(SUCCESS);
}

