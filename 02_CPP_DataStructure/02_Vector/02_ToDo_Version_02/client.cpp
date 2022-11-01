

#include	<iostream>

#include	"vector.hpp"

//	Global Object
MVVector<long>* pvector = NULL;

int main(void)
{
	// Code
	pvector = new MVVector<long>();

	for( long le = 0; le < 10; ++le )
	{
		pvector->PushBack( (le+1) * 12 );
	}

	pvector->PushBackV( 10, 11, 22, 33, 44, 55, 66, 77, 88, 99, 111);

	std::cout << std::endl << std::endl;
	// std::cout << "Vector:" << std::endl;
	/*for( long le = 0; le < pvector->Size(); ++le )
	{
		std::cout 	<< "pvector[" 
					<< le
					<< "] = "
					<< (*pvector)[le]
					<< std::endl;
	}*/

	std::cout << "Vector Using Operator << :" << std::endl << (*pvector);
	// std::cout << "Vector Using Operator using pointer << :" << std::endl << pvector;

	// std::cout << "Using Forward Traversal" << std::endl;
	// pvector->ForwardTraversal();

	// std::cout << "Using Reverse Traversal" << std::endl;
	// pvector->ReverseTraversal();

	//std::cout << "Vector Using Iterator:" << std::endl;
	// for( MVVector<long>::Iterator itr = pvector->begin(); itr != pvector->end(); ++itr ) 
	/*for( auto itr = pvector->begin(); itr != pvector->end(); ++itr ) 
	{
		std::cout << *itr << std::endl;
	}*/

	// std::cout << std::endl << std::endl;
	// std::cout << "Vector Pop Back:"<< std::endl;
	// std::cout << "Popped Data = " << pvector->PopBack() << std::endl;
	// std::cout << "Popped Data = " << pvector->PopBack() << std::endl;
	// std::cout << "Popped Data = " << pvector->PopBack() << std::endl;
	// std::cout << "Popped Data = " << pvector->PopBack() << std::endl;

	// std::cout << std::endl << std::endl;
	//std::cout << "Vector:" << std::endl;
	/*for( long le = 0; le < pvector->Size(); ++le )
	{
		std::cout 	<< "pvector[" 
					<< le
					<< "] = "
					<< (*pvector)[le]
					<< std::endl;
	}*/

	pvector->Replace(5, 1000);	
	std::cout << "Vector Using Operator << :" << std::endl << (*pvector);

	pvector->Insert(5, 2000);
	std::cout << "Vector Using Operator << :" << std::endl << (*pvector);
	
	pvector->Remove(5);
	std::cout << "Vector Using Operator << :" << std::endl << (*pvector);

	
	std::cout << "Vector Using Operator << :" << std::endl << (*pvector);

	//std::cout << "Vector Using Iterator:" << std::endl;
	/*//for( MVVector<long>::Iterator itr = pvector->begin(); itr != pvector->end(); ++itr ) 
	for( auto itr = pvector->begin(); itr != pvector->end(); ++itr ) 
	{
		std::cout << *itr << std::endl;
	}*/

	delete(pvector);
	pvector = NULL;

	return(SUCCESS);
}

