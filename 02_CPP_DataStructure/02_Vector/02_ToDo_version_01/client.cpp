
// Headers
#include <iostream>

#include "vector.hpp"

// Global Object
MVVector<long>* pvector = NULL;

int main(void)
{
	// Code
	pvector = new MVVector<long>();

	for(long le = 0; le < 10; le++)
	{
		pvector->PushBack((le+1) * 15 );
	}

	pvector->PushBackv(10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000);

	std::cout << std::endl << std::endl;

	// std::cout << "Vector:" << std::endl;
	for(long le = 0; le < pvector->Size(); le++)
	{
		std::cout 	<< "pvector["
					<< le
					<< "] = "
					<< (*pvector)[le]
					<< std::endl;
	}

	std::cout << std::endl << std::endl;
	std::cout << "Vector Pop Back: " << std::endl;
	std::cout << "Popped Data = " << pvector->PopBack() << std::endl;
	std::cout << "Popped Data = " << pvector->PopBack() << std::endl;
	std::cout << "Popped Data = " << pvector->PopBack() << std::endl;

	std::cout << std::endl << std::endl;

	for(long le = 0; le < pvector->Size(); le++)
	{
		std::cout 	<< "pvector["
					<< le 
					<< "] = "
					<< (*pvector)[le]
					<< std::endl;
	}

	std::cout << "Vector Using Operator << : " << std::endl << (*pvector);
	std::cout << "Vector Using Operator using pointer : " << std::endl << pvector;
	
	std::cout << "Using Forward Traversal " << std::endl;
	pvector->ForwardTraversal();

	std::cout << "Using BackwardTraversal" << std::endl;
	pvector->ReverseTraversal(); 

	delete(pvector);
	pvector = NULL;

	return(0);
}

