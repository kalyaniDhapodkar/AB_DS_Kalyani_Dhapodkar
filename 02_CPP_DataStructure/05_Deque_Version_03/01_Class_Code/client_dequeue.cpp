


//	Headers
#include	<iostream>
#include	"mv_dequeue.hpp"

MV_DeQueue<long>*	queue1 = NULL;
MV_DeQueue<long>*	queue2 = NULL;

int main(void)
{
	// Code
	
	//	Queue 1
	queue1 = new MV_DeQueue<long>();

	for( long le = 1; le <= 20; ++le )
	{
		queue1->PushBack( le * 13 );
	}

	std::cout << "Queue1:" << queue1;

	for( long le = 1; le <= 5; ++le )
	{
		std::cout <<"Popped Data: " << queue1->PopFront( ) << std::endl;
	}

	std::cout << "Queue1:" << queue1;

	std::cout << "Front: " << queue1->GetFront();
	std::cout << "Back: " << queue1->GetBack();

	for( long le = 1; le <= 20; ++le )
	{
		queue1->PushFront( le * 79 );
	}

	std::cout << "Queue1:" << queue1;

	for( long le = 1; le <= 5; ++le )
	{
		std::cout <<"Popped Data: " << queue1->PopBack( ) << std::endl;
	}

	std::cout << "Queue1:" << queue1;

	std::cout << "Front: " << queue1->GetFront() << std::endl;
	std::cout << "Back: " << queue1->GetBack() << std::endl;

	//	Queue 2
	queue2 = new MV_DeQueue<long>();

	for( long le = 1; le <= 30; ++le )
	{
		queue2->PushBack( le * 4 );
	}

	std::cout << "Queue2:" << queue2;

	for( long le = 1; le <= 3; ++le )
	{
		std::cout <<"Popped Data: " << queue2->PopFront( ) << std::endl;
	}

	std::cout << "Queue2:" << queue2;

	std::cout << "Front: " << queue2->GetFront();
	std::cout << "Back: " << queue2->GetBack();

	for( long le = 1; le <= 30; ++le )
	{
		queue2->PushFront( le * 18 );
	}

	std::cout << "Queue2:" << queue2;

	for( long le = 1; le <= 3; ++le )
	{
		std::cout <<"Popped Data: " << queue2->PopBack( ) << std::endl;
	}

	std::cout << "Queue2:" << queue2;

	std::cout << "Front: " << queue2->GetFront() << std::endl;
	std::cout << "Back: " << queue2->GetBack() << std::endl;

	std::cout << "Before Swapping: " << std::endl;
	std::cout << "Queue1:" << queue1;
	std::cout << "Queue2:" << queue2;

	queue1->Swap(queue2);

	std::cout << "After Swapping: " << std::endl;
	std::cout << "Queue1:" << queue1;
	std::cout << "Queue2:" << queue2;

	delete(queue2);
	queue2 = NULL;

	delete(queue1);
	queue1 = NULL;

	exit(SUCCESS);
}

