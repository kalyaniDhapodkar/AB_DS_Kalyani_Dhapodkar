

// Headers
#include <iostream>
#include <ctime>

#include "mv_nd_array.hpp"

// Constant Literals
#define  	MAX 	2

// Global Objects
struct Demo
{
	int inum;
	long lnum;
	char ch;

	Demo(int inum, long lnum, char ch)
	{
		// Code
		this->inum = inum;
		this->lnum = lnum;
		this->ch = ch;
	}
};

std::ostream& operator<<(std::ostream& out, Demo& demo)
{
	// Code
	out << " { "
		<< demo.inum
		<< " | "
		<< demo.lnum
		<< " | "
		<< demo.ch
		<< " } ";

	return(out);
} 

// Primitive Data Type
MVArray<long>* parray_4D = NULL;

// Userdefined Data Type
MVArray<struct Demo*>* parray_4D_demo = NULL;

int main(void)
{
	// Code

	/******************************************\
	*			Primitive Type  			   *
	\******************************************/

	parray_4D = new MVArray<long>(4, MAX, MAX, MAX, MAX);

	std::cout << std::endl << std::endl;

	// Write Data to Array
	long count = 0;
	for(long index1 = 0; index1 < parray_4D->GetDimensionSize(0); index1++)
		for(long index2 = 0; index2 < parray_4D->GetDimensionSize(1); index2++)
			for(long index3 = 0; index3 < parray_4D->GetDimensionSize(2); index3++)
				for(long index4 = 0; index4 < parray_4D->GetDimensionSize(3); index4++)
					parray_4D->SetData(++count, index1, index2, index3, index4);

	for(long index1 = 0; index1 < parray_4D->GetDimensionSize(0); index1++)
		for(long index2 = 0; index2 < parray_4D->GetDimensionSize(1); index2++)
			for(long index3 = 0; index3 < parray_4D->GetDimensionSize(2); index3++)
				for(long index4 = 0; index4 < parray_4D->GetDimensionSize(3); index4++)
					std::cout 	<< "parray_4D"
								<< "["
								<< index1
								<< "]"
								<< "["
								<< index2
								<< "]"
								<< "["
								<< index3
								<< "]"
								<< "["
								<< index4
								<< "]"
								<< " = "
								<< parray_4D->GetData(index1, index2, index3, index4)
								<< std::endl;

    std::cout << std::endl << std::endl;

    for(long le = 0; le < parray_4D->GetSize(); le++)
   	{
   		std::cout 	<< "parray_4D ["
   					<< le 
   					<< "] = "
   					<< (*parray_4D)[le]
   					<< std::endl;
   	} 	


	/******************************************\
	*			User Defined Data Type			   *
	\******************************************/

   	parray_4D_demo = new MVArray<struct Demo*>(4, MAX, MAX, MAX, MAX);

   	std::cout << std::endl << std::endl;

   	// Write Data to Array
   	srand(time(0));
   	count = 0;
   	for(long index1 = 0; index1 < parray_4D_demo->GetDimensionSize(0); index1++)
  	 	for(long index2 = 0; index2 < parray_4D_demo->GetDimensionSize(1); index2++)
   			for(long index3 = 0; index3 < parray_4D_demo->GetDimensionSize(2); index3++)
   				for(long index4 = 0; index4 < parray_4D_demo->GetDimensionSize(3); index4++)
   					parray_4D_demo->SetData(new struct Demo(rand() % 1024,
   															rand() % (1024 * 100),
   															65 + (rand() % 26)
   															),
   											index1, index2, index3, index4);

  	for(long index1 = 0; index1 < parray_4D_demo->GetDimensionSize(0); index1++)
  	 	for(long index2 = 0; index2 < parray_4D_demo->GetDimensionSize(1); index2++)
   			for(long index3 = 0; index3 < parray_4D_demo->GetDimensionSize(2); index3++)
   				for(long index4 = 0; index4 < parray_4D_demo->GetDimensionSize(3); index4++)
   					std::cout 	<< "parray_4D_demo"
   								<< "["
   								<< index1
   								<< "]"
   								<< "["
   								<< index2
   								<< "]"
   								<< "["
   								<< index3
   								<< "]"
   								<< "["
   								<< index4
   								<< "]"
   								<< " = "
   								<< (*parray_4D_demo->GetData(index1, index2, index3, index4))
   								<< std::endl;

   	std::cout << std::endl << std::endl;

   	for(long le = 0; le < parray_4D_demo->GetSize(); le++)
   	{
   		std::cout << "parray_4D_demo [" << le << "] = " << *(*parray_4D_demo)[le] << std::endl;
   	}  

   	delete(parray_4D);
   	delete(parray_4D_demo);

   	return(SUCCESS);
}
