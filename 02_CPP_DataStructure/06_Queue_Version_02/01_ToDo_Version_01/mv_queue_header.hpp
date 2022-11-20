
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
class MVQueue : private MVVector<T>
{
private:
	long 	m_head;
	long 	m_tail;

public:
	MVQueue()
	{
		// Code
		this->m_head = 0;
		this->m_tail = 0;

	}

	MVQueue(size_t new_size)
	{
		// Code
		this->m_head = 0;
		this->m_tail = 0;

	}

	~MVQueue()
	{
		
	}

	ret_t  EnqueBack(T data)
	{
		ret_t status = PushBack(data);

		if(SUCCESS == status)
		m_tail++;

		return(status);
	}

	T DequeFront()
	{
		// Code
		
		T to_return_data = PopFront();
		m_tail--;

		return(to_return_data);
	}

	size_t QSize() const { return(Size());}

	long GetHead() const{ DataAt[0]; }

	long GetTail() const { DataAt[Size()-1]; }

	T operator[] (long index)
	{
		// Code
		if(index >= Size())
		{
			std::cerr << "ERROR: Index Out of Bound." << std::endl;
			return((T)0);
		}

		return(DataAt(index));
	}	

	template<typename T>
	friend std::ostream& operator<<(std::ostream& out, MVQueue<T>*& queue);
};

template<typename T>
std::ostream& operator<<(std::ostream& out, MVQueue<T>*& queue)
{
	// Code
	static_cast<MVVector<T>*>(queue)->ForwardTraversal();
	static_cast<MVVector<T>*>(queue)->ReverseTraversal();

	return(out);
}

