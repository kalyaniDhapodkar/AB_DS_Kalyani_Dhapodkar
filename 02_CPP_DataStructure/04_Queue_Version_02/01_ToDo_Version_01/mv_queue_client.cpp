

// Headers

#include	<iostream>

#include	"mv_queue_header.hpp"

MVQueue<long>* pqueue;

int main(void)
{
	// Code
	pqueue = new MVQueue<long>();

	pqueue->EnqueBack(100);
	pqueue->EnqueBack(90);
	pqueue->EnqueBack(80);
	pqueue->EnqueBack(70);
	pqueue->EnqueBack(60);
	pqueue->EnqueBack(50);
	pqueue->EnqueBack(40);
	pqueue->EnqueBack(30);
	pqueue->EnqueBack(20);
	pqueue->EnqueBack(10);
	pqueue->EnqueBack(99);
	pqueue->EnqueBack(23);

	std::cout << std::endl << std::endl;
	std::cout << "Queue After Push Back." << std::endl;
	std::cout << (pqueue);

	std::cout << std::endl << std::endl;
	std::cout << "Popped Data = " << pqueue->DequeFront() << std::endl;
	std::cout << "Popped Data = " << pqueue->DequeFront() << std::endl;
	std::cout << "Popped Data = " << pqueue->DequeFront() << std::endl;
	std::cout << "Popped Data = " << pqueue->DequeFront() << std::endl;
	std::cout << "Popped Data = " << pqueue->DequeFront() << std::endl;

	std::cout << std::endl << std::endl;
	std::cout << "Queue After Pop Front." << std::endl;
	std::cout << (pqueue);	

	std::cout << "Size: " << pqueue->QSize() << std::endl;

	pqueue->EnqueBack(1111);
	pqueue->EnqueBack(5647);
	pqueue->EnqueBack(3488);

	std::cout << std::endl << std::endl;
	std::cout << "Queue After Push Back." << std::endl;
	std::cout << (pqueue);

	std::cout << "Size: " << pqueue->QSize() << std::endl;

	delete(pqueue);

	std::cout << "Size: " << pqueue->QSize() << std::endl;

	std::cout << (pqueue);

	std::cout << "------------END-----------" << std::endl;

	return(SUCCESS);
}	

