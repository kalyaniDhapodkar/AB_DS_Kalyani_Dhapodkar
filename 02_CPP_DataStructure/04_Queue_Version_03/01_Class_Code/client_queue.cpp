


//	Headers
#include	<iostream>
#include	"mv_queue.hpp"

MV_Queue<long>*	queue = NULL;

int main(void)
{
	// Code
	queue = new MV_Queue<long>();

	for( long le = 1; le <= 20; ++le )
	{
		queue->PushBack( le * 13 );
	}

	std::cout << queue;

	for( long le = 1; le <= 5; ++le )
	{
		std::cout <<"Popped Data: " << queue->PopFront( ) << std::endl;
	}

	std::cout << queue;

	std::cout << "Front: " << queue->GetFront();
	std::cout << "Back: " << queue->GetBack();

	delete(queue);
	queue = NULL;

	exit(SUCCESS);
}

