
#pragma	once

//	Headers
#include	"base_iterator.hpp"

// Constant Literals
#ifndef SUCCESS
#define	SUCCESS 0
#endif

#ifndef	FAILURE
#define	FAILURE 1
#endif

#define	DEFAULT_QUEUE_SIZE 	32

// Typedef
typedef int	ret_t;

// Type Definition
template<typename T>
class MVQueue
{
private:
	T* m_data_array;
	long m_head;
	long m_tail;
	size_t m_length;
	size_t m_no_of_elements;

public:

	MVQueue()
	{
		// Code
		this->m_length = DEFAULT_QUEUE_SIZE;

		this->m_head = 0;
		this->m_tail = 0;
		this->m_no_of_elements = 0;

		this->m_data_array = new T[this->m_length];
	}

	MVQueue(size_t length)
	{
		// Code
		this->m_length = length;

		this->m_head = 0;
		this->m_tail = 0;
		this->m_no_of_elements = 0;

		this->m_data_array = new T[this->m_length];
	}

	~MVQueue()
	{
		// Code
		if( m_data_array )
		{
			delete [] m_data_array;
			m_data_array = NULL;
		}
	}

	ret_t PushBack(T data)
	{
		// Code
		if( m_no_of_elements == m_length )
		{
			std::cerr << "ERROR: Queue Overflow." << std::endl;
			return(FAILURE); 
		}	

		this->m_data_array[ this->m_tail ] = data;

		this->m_tail++;

		if( this->m_tail == this->m_length )
		{
			this->m_tail = 0;
		}
		this->m_no_of_elements++;

		return(SUCCESS);
	}

	T PopFront()
	{
		// Code
		if( 0 == this->m_no_of_elements )
		{
			std::cerr << "ERROR: Queue Underflow." << std::endl;
			return((T)0);
		}

		T to_return_data = this->m_data_array[this->m_head];

		this->m_head++;

		if( this->m_length == this->m_head )
		{
			this->m_head = 0;
		}
		this->m_no_of_elements--;

		return(to_return_data);
	}

	size_t Size() const { return(this->m_no_of_elements); }

	size_t Length() const { return(this->m_length); }

	long 	GetHead() const 
	{
		// Code
		return(m_head); 
	}

	long 	GetTail() const 
	{ 
		// Code
		return(m_tail); 
	}

	T operator[] (long index)
	{
		// Code
		if( index >= this->m_length )
		{
			std::cerr << "ERROR: Index Out of bound." << std::endl;
			return((T)0);
		}

		return( this->m_data_array[index] );
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
			if( m_index >= m_pqueue->Length() )
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

		if( h >= this->m_length )
			h = 0;

		return( Iterator(this, h) );
	}

	Iterator end()
	{
		// Code
		long t = this->GetTail()-1;

		if( t < 0 )
			t = this->m_length-1;
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
