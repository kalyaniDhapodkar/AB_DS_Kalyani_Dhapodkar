

// Headers

#include	<iostream>

#include	"queue.hpp"

MVQueue<long>* pqueue;

int main(void)
{
	// Code
	pqueue = new MVQueue<long>();

	pqueue->PushBack(100);
	pqueue->PushBack(90);
	pqueue->PushBack(80);
	pqueue->PushBack(70);
	pqueue->PushBack(60);
	pqueue->PushBack(50);
	pqueue->PushBack(40);
	pqueue->PushBack(30);
	pqueue->PushBack(20);
	pqueue->PushBack(10);
	pqueue->PushBack(99);
	pqueue->PushBack(23);

	std::cout << std::endl << std::endl;
	std::cout << "Queue After Push Back." << std::endl;
	std::cout << (*pqueue);

	std::cout << std::endl << std::endl;
	std::cout << "Popped Data = " << pqueue->PopFront() << std::endl;
	std::cout << "Popped Data = " << pqueue->PopFront() << std::endl;
	std::cout << "Popped Data = " << pqueue->PopFront() << std::endl;
	std::cout << "Popped Data = " << pqueue->PopFront() << std::endl;
	std::cout << "Popped Data = " << pqueue->PopFront() << std::endl;

	std::cout << std::endl << std::endl;
	std::cout << "Queue After Pop Front." << std::endl;
	std::cout << (*pqueue);	

	pqueue->PushBack(1111);
	pqueue->PushBack(5647);
	pqueue->PushBack(3488);

	std::cout << std::endl << std::endl;
	std::cout << "Queue After Push Back." << std::endl;
	std::cout << (*pqueue);

	delete(pqueue);

	return(SUCCESS);
}	

