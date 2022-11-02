
#pragma once

// Headers
#include <cassert>

#include "mv_base_iterator.hpp"
#include "mv_vector_header.hpp"

// Constant Literals
#ifndef  	SUCCESS
#define 	SUCCESS  	0
#endif

#ifndef  	FAILURE
#define  	FAILURE  	1
#endif

#define  	DEFAULT_QUEUE_SIZE  	12

// typedefs
typedef  	int  	ret_t;

// Class Definition
template<typename T>
class MVQueue : public MVVector<T>
{
private:
	MVVector<T>* m_pvector;
	long 	m_head;
	long 	m_tail;

public:
	MVQueue()
	{
		// Code
		this->m_pvector = new MVVector<T>();

		this->m_pvector->m_capacity = DEFAULT_QUEUE_SIZE;
		this->m_pvector->m_no_of_elements = 0;

		this->m_head = 0;
		this->m_tail = 0;

		this->m_data_array = new T[this->m_pvector->m_capacity];
	
	}

	MVQueue(size_t new_size)
	{
		// Code
		this->m_pvector = create_vector();

		this->m_pvector->m_capacity = new_size;
		this->m_pvector->m_no_of_elements = 0;

		this->m_head = 0;
		this->m_tail = 0;

		this->m_data_array = new T[this->m_pvector->m_capacity];
	
	}

	~MVQueue()
	{
		if(this->m_pvector->m_data_array)
		{
			delete[] m_data_array;
			m_data_array = NULL;
		}

		if(this->m_pvector)
		{
			delete m_pvector;
			m_pvector = NULL;
		}
	}

	ret_t  PushBack(T data)
	{
		// Code
		this->m_pvector->m_data_array[this->m_tail] = data;
		this->m_tail++;

		if(this->m_pvector->m_no_of_elements == this->m_pvector->m_capacity)
		{
			this->m_pvector->m_capacity = this->m_pvector->m_capacity * 2;
			this->m_pvector->m_data_array = (T*)realloc(this->m_pvector->m_data_array, this->m_pvector->m_capacity * sizeof(T));
		}

		this->m_pvector->m_no_of_elements++;

		return(SUCCESS);
	}

	T PopFront()
	{
		T to_return_data = this->m_pvector->m_data_array[0];

		for(long le = 0; le < this->m_pvector->m_no_of_elements; le++)
		{
			this->m_pvector->m_data_array[le] = this->m_pvector->m_data_array[le+1];
		}

		this->m_pvector->m_no_of_elements--;

		if(this->m_pvector->m_no_of_elements < this->m_pvector->m_capacity/2)
		{
			this->m_pvector->m_capacity = this->m_pvector->m_capacity/2;
			this->m_pvector->m_data_array = (T*)realloc(this->m_pvector->m_data_array, this->m_pvector->m_capacity * sizeof(T));
		}

		this->m_tail--;

		return(to_return_data);
	}

	size_t Size() const { return(this->m_pvector->m_no_of_elements);}

	long GetHead() const{ return(this->m_head); }

	long GetTail() const { return(this->m_tail); }

	T operator[] (long index)
	{
		// Code
		if(index >= this->m_pvector->m_no_of_elements)
		{
			std::cerr << "ERROR: Index Out of Bound." << std::endl;
			return((T)0);
		}

		return(this->m_pvector->m_data_array[index]);
	}	

	class Iterator : public mv_base_iterator<T>
	{
	private:
		MVQueue<T>* m_pqueue;
		long	m_index;
		bool	m_flag;

	public:
		Iterator(long index) 
		{
			//	Code
			this->m_index = index;
			m_flag = false;
		}

		Iterator(MVQueue<T>* pqueue) 
		{
			//	Code
			m_pqueue = pqueue;
			this->m_index = m_pqueue->GetHead();
			m_flag = false;
		}

		Iterator(MVQueue<T>* pqueue, long index) 
		{
			//	Code
			m_pqueue = pqueue;
			this->m_index = index;
			m_flag = false;
		}

		~Iterator()
		{

		}

		Iterator& operator++()
		{
			//	Code
			++this->m_index;
			if( m_index >= m_pqueue->m_pvector->m_capacity )
			{
				m_index = 0;
			}
			return(*this);
		}

		Iterator& operator--()
		{
			//	Code
			--this->m_index;
			if( m_index < 0 )
			{
				m_index = m_pqueue->Length()-1;
			}
			return(*this);
		}

		Iterator operator++(int value)
		{
			// Code
			Iterator itr = *this;
			++*this;
			return(itr);
		}	

		Iterator operator--(int value)
		{
			// Code
			Iterator itr = *this;
			--*this;
			return(itr);
		}

		Iterator operator+(int value)
		{
			// Code
			Iterator itr = Iterator(this->m_index + value);
			return(itr);
		}

		Iterator operator-(int value)
		{
			// Code
			Iterator itr = Iterator(this->m_index - value);
			return(itr);
		}

		Iterator& operator+=(int value)
		{
			// Code
			this->m_index += value;
			return(*this);
		}

		Iterator& operator-=(int value)
		{
			// Code
			this->m_index -= value;
			return(*this);
		}

		bool operator!=(Iterator& itr)
		{
			// Code
			return( !( (*this) == itr ) );
		}	

		bool operator==(Iterator& itr)
		{
			// Code
			return( this->m_index == itr.m_index );
		}

		T operator*()
		{
			return( (*pqueue)[m_index] );
		}
	};

	Iterator begin()
	{
		// Code
		long h = this->GetHead();

		if( h >= this->m_pvector->m_no_of_elements )
			h = 0;

		return( Iterator(this, h) );
	}

	Iterator end()
	{
		// Code
		long t = this->GetTail()-1;

		if( t < 0 )
			t = this->m_pvector->m_no_of_elements-1;
		return( Iterator(this, t) );
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& out, MVQueue<T>& queue)
{
	// Code
	out << "{START}-";
	for( auto itr = queue.begin(); 
			itr != queue.end();
			++itr)
	{
		out << "{" << *itr << "}-";
	}
	out << "{" << *(queue.end()) << "}-";
	out << "{END}" << std::endl << std::endl;

	return(out);
}

