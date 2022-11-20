
// Headers
#include <iostream>

#include "mv_vector.hpp"

// Global Object
MVVector<long>* pvector_1 = NULL;
MVVector<long>* pvector_2 = NULL;

int main(void)
{
	// Code
	pvector_1 = new MVVector<long>();
	pvector_2 = new MVVector<long>();

	for(long le = 0; le < 10; le++)
	{
		pvector_1->PushBack((le+1) * 15 );
	}

	pvector_2->PushBackv(10, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000);

	std::cout << std::endl << std::endl;

	// // std::cout << "Vector:" << std::endl;
	// for(long le = 0; le < pvector->Size(); le++)
	// {
	// 	std::cout 	<< "pvector["
	// 				<< le
	// 				<< "] = "
	// 				<< (*pvector)[le]
	// 				<< std::endl;
	// }

	// std::cout << std::endl << std::endl;
	// std::cout << "Vector Pop Back: " << std::endl;
	// std::cout << "Popped Data = " << pvector->PopBack() << std::endl;
	// std::cout << "Popped Data = " << pvector->PopBack() << std::endl;
	// std::cout << "Popped Data = " << pvector->PopBack() << std::endl;

	// std::cout << std::endl << std::endl;

	// for(long le = 0; le < pvector->Size(); le++)
	// {
	// 	std::cout 	<< "pvector["
	// 				<< le 
	// 				<< "] = "
	// 				<< (*pvector)[le]
	// 				<< std::endl;
	// }

	std::cout << "Vector 1 Using Operator << : " << std::endl << (*pvector_1);
	std::cout << "Vector 2 Using Operator << : " << std::endl << (*pvector_2);
	// std::cout << "Vector Using Operator using pointer : " << std::endl << pvector;
	
	// std::cout << "Using Forward Traversal " << std::endl;
	// pvector->ForwardTraversal();

	// std::cout << "Using BackwardTraversal" << std::endl;
	// pvector->ReverseTraversal(); 

	std::cout << std::endl << "After Merge Vector 2 in Vector 1: " << std::endl;

	pvector_1->VectorMerge(pvector_2);

	std::cout << "Vector 1 Using Operator << : " << std::endl << (*pvector_1);
	std::cout << "Vector 2 Using Operator << : " << std::endl << (*pvector_2);

	delete(pvector_1);
	pvector_1 = NULL;

	delete(pvector_2);
	pvector_2 = NULL;

	return(0);
}

