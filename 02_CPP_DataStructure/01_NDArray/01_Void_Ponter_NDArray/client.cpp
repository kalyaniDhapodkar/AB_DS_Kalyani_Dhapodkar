
// Headers
#include <iostream>

#include "mv_nd_array.hpp"

// Constant Literals
#define 	MAX  	5

MVArray*  parray_4d = NULL;

int main(void)
{
	// Code
	parray_4d = new MVArray(4,
							MAX,
							MAX,
							MAX,
							MAX);

	// Write Data to array
	long long count = 1; 			// MVArray::GetDimensionSize(&parray_4d, 0);
	for(long index1 = 0; index1 < parray_4d->GetDimensionSize(0); index1++)
	{
		for(long index2 = 0; index2 < parray_4d->GetDimensionSize(1); index2++)
		{
			for(long index3 = 0; index3 < parray_4d->GetDimensionSize(2); index3++)
			{
				for(long index4 = 0; index4 < parray_4d->GetDimensionSize(3); index4++)
				{
					parray_4d->SetData((data_t)count++, index1, index2, index3, index4);
				}
			}
		}
	}

	// Get data from array
	count = 1;
	for(long index1 = 0; index1 < parray_4d->GetDimensionSize(0); index1++)
	{
		for(long index2 = 0; index2 < parray_4d->GetDimensionSize(1); index2++)
		{
			for(long index3 = 0; index3 < parray_4d->GetDimensionSize(2); index3++)
			{
				for(long index4 = 0; index4 < parray_4d->GetDimensionSize(3); index4++)
				{
					std::cout 	<< "parray_4d["
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
								<< "="
								<< (long long )parray_4d->GetData(index1, index2, index3, index4)
								<< std::endl;
				}
			}
		}
	}

	delete(parray_4d);

	return(0);
}

