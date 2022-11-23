

/**
 * @file:	mv_client.cpp
 * @author:	MarshallingVoid	(marshallingvoid@gmail.com) 
 * @brief:	This file contains the use of all the function implement in mv_singly_list.hpp
 * @date:	23/11/2022
 * @version	1.0
 * 
 * @copyright	Copyright (c) 2022
 * 
 */

//	Headers

#include	<iostream>

#include	"mv_singly_list_header.hpp"

SinglyLinkedList<long> *psll;

int main(void)
{
	// Code
	psll = new SinglyLinkedList<long>();

	for( long le = 0; le < 20; ++le )
	{
		psll->InsertFront( (le+1) * 13 );
	}

	std::cout << "List After insert front: " << std::endl;
	std::cout << (*psll) << std::endl << std::endl;

	for( long le = 0; le < 20; ++le )
	{
		psll->InsertBack( (le+1) * 62 );
	}

	std::cout << "List After insert back: " << std::endl;
	std::cout << (*psll) << std::endl << std::endl;

	psll->InsertAfter(1234, 52);
	psll->InsertAfter(5678, 620);
	psll->InsertAfter(9009, 248);
	psll->InsertAfter(8008, 9999);

	std::cout << "List After insert after: " << std::endl;
	std::cout << (*psll) << std::endl << std::endl;

	psll->InsertBefore(1001, 1234);
	psll->InsertBefore(4422, 248);
	psll->InsertBefore(7865, 9009);
	psll->InsertBefore(9999, 5678);

	std::cout << "List After insert before: " << std::endl;
	std::cout << (*psll) << std::endl << std::endl;

	psll->InsertAt(1331, 10);
	psll->InsertAt(1111, 0);
	psll->InsertAt(9292, 13);
	psll->InsertAt(5555, 15);

	std::cout << "List After insert At: " << std::endl;
	std::cout << (*psll) << std::endl << std::endl;
	
	std::cout << "List After Remove Front: " << std::endl;
	std::cout << "Removing:" << psll->RemoveFront() << std::endl;
	std::cout << "Removing:" << psll->RemoveFront() << std::endl;
	std::cout << "Removing:" << psll->RemoveFront() << std::endl;
	std::cout << "Removing:" << psll->RemoveFront() << std::endl;
	std::cout << "Removing:" << psll->RemoveFront() << std::endl;
	std::cout << (*psll) << std::endl << std::endl;
	
	std::cout << "List After Remove Back: " << std::endl;
	std::cout << "Removing:" << psll->RemoveBack() << std::endl;
	std::cout << "Removing:" << psll->RemoveBack() << std::endl;
	std::cout << "Removing:" << psll->RemoveBack() << std::endl;
	std::cout << "Removing:" << psll->RemoveBack() << std::endl;
	std::cout << "Removing:" << psll->RemoveBack() << std::endl;
	std::cout << (*psll) << std::endl << std::endl;
	
	std::cout << "List After Remove Before: " << std::endl;
	std::cout << "Removing:" << psll->RemoveBefore(4422) << std::endl;
	std::cout << "Removing:" << psll->RemoveBefore(9009) << std::endl;
	std::cout << "Removing:" << psll->RemoveBefore(4422) << std::endl;
	std::cout << "Removing:" << psll->RemoveBefore(13) << std::endl;
	std::cout << "Removing:" << psll->RemoveBefore(208) << std::endl;
	std::cout << (*psll) << std::endl << std::endl;
	
	std::cout << "List After Remove After: " << std::endl;
	std::cout << "Removing:" << psll->RemoveAfter(930) << std::endl;
	std::cout << "Removing:" << psll->RemoveAfter(143) << std::endl;
	std::cout << "Removing:" << psll->RemoveAfter(9292) << std::endl;
	std::cout << "Removing:" << psll->RemoveAfter(434) << std::endl;
	std::cout << "Removing:" << psll->RemoveAfter(620) << std::endl;
	std::cout << (*psll) << std::endl << std::endl;
	
	std::cout << "List After Remove At: " << std::endl;
	std::cout << "Removing:" << psll->RemoveAt(0) << std::endl;
	std::cout << "Removing:" << psll->RemoveAt(psll->Size() - 1) << std::endl;
	std::cout << "Removing:" << psll->RemoveAt(10) << std::endl;
	std::cout << "Removing:" << psll->RemoveAt(4) << std::endl;
	std::cout << "Removing:" << psll->RemoveAt(99) << std::endl;
	std::cout << (*psll) << std::endl << std::endl;

	std::cout << "Using Iterator:" << std::endl;

	delete(psll);
	psll = NULL;

	exit(SUCCESS);
}


