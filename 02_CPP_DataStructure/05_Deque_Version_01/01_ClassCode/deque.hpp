

#pragma	once

//	Headers
#include	<cassert>

#include	"base_ietrator.hpp"

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
class MVDeQueue
{
private:
	T*	m_data_array;
	long	m_head;
	long	m_tail;
	size_t	m_length;
	size_t	m_size;

public:
	MVDeQueue()
	{
		// Code
		this->m_length = DEFAULT_QUEUE_SIZE;
		this->m_size = 0;
		this->m_head = 0;
		this->m_tail = 0;

		this->m_data_array = new T[this->m_length];
	}

	MVDeQueue(size_t new_size)
	{
		// Code
		this->m_length = new_size;
		this->m_size = 0;
		this->m_head = 0;
		this->m_tail = 0;

		this->m_data_array = new T[this->m_length];
	}

	~MVDeQueue()
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
		if( m_size == m_length )
		{
			std::cerr << "ERROR : Dequeue Overflow." << std::endl;
			return(FAILURE);
		}

		m_data_array[m_tail] = data;
		m_tail++;

		if( m_tail == m_length )
		{
			m_tail = 0;
		}

		m_size++;

		return(SUCCESS);
	}

	ret_t PushFront(T data)
	{
		// Code
		if( m_size == m_length )
		{
			std::cerr << "ERROR: DeQueue Overflow." << std::endl;
			return(FAILURE);
		}

		m_head--;

		if( m_head < 0 )
			m_head = m_length - 1;

		m_data_array[m_head] = data;

		m_size++;

		return(SUCCESS);
	}

	T PopBack()
	{
		// Code
		if( 0 == m_size )
		{
			std::cerr << "ERROR : DeQueue Underflow." << std::endl;
			return((T)0);
		}

		m_tail--;

		if( m_tail < 0 )
			m_tail = m_length - 1;

		T to_return_data = m_data_array[m_tail];

		m_size--;

		return(to_return_data);
	}

	T PopFront()
	{
		// Code
		if( 0 == m_size )
		{
			std::cerr << "ERROR: DeQueue Underflow." << std::endl;
			return((T)0);
		}

		T to_return_data = m_data_array[m_head];

		m_head++;

		if( m_head >= m_length )
			m_head = 0;

		m_size--;

		return(to_return_data);
	}

	size_t 	Size() const { return(m_size); }
	size_t 	Length() const { return( m_length); }
	long 	Head() const { return(m_head); }
	long	Tail() const { return(m_tail); }

	T operator[](long index)
	{
		if( index >= m_length )
		{
			std::cerr << "ERROR: Index Out Of Bound." << std::endl;
		}
		assert(index < m_length);
		return( m_data_array[index] );
	}

	class Iterator : public mv_base_iterator<T>
	{
	private:
		long m_index;
		MVDeQueue<T>* m_dequeue;
	public:

		Iterator(long index)
		{
			// Code
			this->m_index = index;
		}

		Iterator(long index, MVDeQueue<T>* dequeue)
		{
			// Code
			this->m_index = index;
			this->m_dequeue = dequeue;
		}

		~Iterator()
		{

		}

		Iterator& operator++()
		{
			// Code
			++this->m_index;

			if( m_index >= m_dequeue->Length() )
				m_index = 0;

			return(*this);
		}

		Iterator& operator--()
		{
			// Code
			--this->m_index;

			if( m_index < 0 )
				m_index = m_dequeue->Length()-1;

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
			Iterator itr = Iterator(m_index + value, m_dequeue);
			return(itr);
		}

		Iterator operator-(int value)
		{
			// Code
			Iterator itr = Iterator(m_index - value, m_dequeue);
			return(itr);
		}

		Iterator operator+=(int value)
		{
			// Code
			m_index += value;
			return(*this);
		}

		Iterator operator-=(int value)
		{
			m_index -= value;
			return(*this);
		}
		
		bool operator==(Iterator& itr)
		{
			// Code
			return( this->m_index == itr.m_index );
		}

		bool operator!=(Iterator& itr)
		{
			return( !( *this == itr ) );
		}

		T operator*()
		{
			return( (*m_dequeue)[m_index] );
		}
	};

	Iterator begin()
	{
		// Code
		long h = m_head;

		if( h >= m_length )
			h = 0;

		return(Iterator(h, this));
	}

	Iterator end()
	{
		// Code
		long t = m_tail-1;

		if( t < 0 )
			t = m_length - 1;

		return( Iterator(t, this) );
	}
};

template<typename T>
std::ostream& operator<<(std::ostream& out, MVDeQueue<T>& dequeue)
{
	// Code

	out << "{START}-";
	for( auto itr = dequeue.begin(); itr != dequeue.end(); ++itr )
	{
		out << "{" << *itr << "}-";
	}
	out << "{" << *(dequeue.end()) << "}-";
	out << "{END}" << std::endl << std::endl;

	return(out);
}
