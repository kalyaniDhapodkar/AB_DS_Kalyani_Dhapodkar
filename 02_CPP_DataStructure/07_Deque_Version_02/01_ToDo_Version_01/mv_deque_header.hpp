

#pragma	once

//	Headers
#include	<cassert>

#include 	"mv_vector_header.hpp"

//	Constant Literals
#ifndef	SUCCESS
#define	SUCCESS	0
#endif

#ifndef	FAILURE
#define	FAILURE 1
#endif

#define		DEFAULT_QUEUE_SIZE	12

// Typedefs
typedef		int		ret_t;

//	Class Definition
template<typename T>
class MVDeQueue : public MVVector<T>
{
private:
	long	m_head;
	long	m_tail; 

public:
	MVDeQueue()
	{
		// Code
		this->m_head = 0;
		this->m_tail = 0;

	}

	MVDeQueue(size_t new_size)
	{
		// Code
		this->m_head = 0;
		this->m_tail = 0;

	}

	~MVDeQueue()
	{

	}

	ret_t EnqueBack(T data)
	{

		// Code
		PushBack(data);
		this->m_tail++;

		return(SUCCESS);
	}

	ret_t EnqueFront(T data)
	{
		// Code
 	 	PushFront(data);
 	 	this->m_tail++;

		return(SUCCESS);
	}

	T DequeBack()
	{
		// Code
		T to_return_data = PopBack();
   		this->m_tail--;

		return(to_return_data);
	}

	T DequeFront()
	{
		// Code
		T to_return_data = PopFront();

		this->m_tail--;

		return(to_return_data);
	}

	size_t 	QSize() const { return( Size()); }
	size_t 	Length() const { return( Capacity()); }
	long 	Head() const { return( this->m_head); }
	long	Tail() const { return( this->m_tail); }

	T operator[](long index)
	{
		if( index >= Capacity() )
		{
			std::cerr << "ERROR: Index Out Of Bound." << std::endl;
		}
		assert(index < Capacity());
		return( DataAt(index) );
	}

	template<typename T>
	friend std::ostream& operator<<(std::ostream& out, MVDeQueue<T>*& dequeue);

};

template<typename T>
std::ostream& operator<<(std::ostream& out, MVDeQueue<T>*& dequeue)
{
	// Code
	static_cast<MVVector<T>*>(dequeue)->ForwardTraversal();
	static_cast<MVVector<T>*>(dequeue)->ReverseTraversal();

	return(out);
}
