

/**
 * @file:	mv_array.hpp
 * @author:	Kalyani Dhapodkar (dhapodkarkalyani@gmail.com)
 * @brief:	This file hold the definition for array  
 * @date:	06/12/2022
 * @version:	1.0
 * 
 * @copyright:	Copyrights(c) 2022
 */


#pragma once

#ifndef  	SUCCESS
#define  	SUCCESS  	0
#endif

#ifndef  	FAILURE
#define  	FAILURE  	1
#endif

template<typename T_ARRAY, size_t no_of_elements>
class MVArray
{
private:
	T_ARRAY* array;
public:
	MVArray()
	{
		array = new T_ARRAY[no_of_elements];
	}

	~MVArray()
	{
		delete [] array;
	}

	T_ARRAY& operator[](long index)
	{
		return(array[index]);
	}

	size_t Size() { return(no_of_elements); }

	class Iterator
	{
	private:
		T_ARRAY* runner;
	public:
		Iterator(T_ARRAY* object_ptr)
		{
			runner = object_ptr;
		}

		~Iterator()
		{

		}

		Iterator operator+(long index)
		{
			return(Iterator(runner + index));
		}

		Iterator operator-(long index)
		{
			return(Iterator(runner - index));
		}

		Iterator operator+=(long index)
		{
			runner += index;
			return(*this); 
		}

		Iterator operator-=(long index)
		{
			runner -= index;
			return(*this);
		}

		Iterator operator++()
		{
			return( (*this) += 1 );
		}

		Iterator operator--()
		{
			return( (*this) -= 1 );
		}

		Iterator operator++(int value)
		{
			Iterator itr(runner);

			(*this) += 1;

			return(itr);
		}

		Iterator operator--(int value)
		{
			Iterator itr(runner);

			(*this) -= 1;

			return(itr);
		}

		bool operator==(Iterator& itr)
		{
			return( this->runner == itr.runner );
		}

		bool operator!=(Iterator& itr)
		{			
			return( !((*this) == itr) );
		}

		void operator=(T_ARRAY value)
		{
			*runner = value;
		}

		T_ARRAY operator*()
		{
			return(*runner);
		}
	};

	Iterator begin()
	{
		return( Iterator(&array[0]) );
	}

	Iterator end()
	{
		return( Iterator(&array[no_of_elements]) );
	}
};

