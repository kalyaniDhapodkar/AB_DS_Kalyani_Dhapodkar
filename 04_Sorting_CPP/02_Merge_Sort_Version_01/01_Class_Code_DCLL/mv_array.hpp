

#pragma	once

#ifndef	SUCCESS
#define	SUCCESS	0
#endif

#ifndef	FAILURE	
#define	FAILURE	1
#endif

template<typename T_ARRAY, size_t size>
class MVArray
{
private:	
	T_ARRAY*	array;
	size_t		m_size;

public:
	MVArray()
	{
		array = new T_ARRAY[size];
		m_size = size;
	}

	MVArray(MVArray& arr, long long first, long long last)
	{
		m_size = last - first + 1;
		array = new T_ARRAY[ m_size ];

		for( long long le = 0; le < m_size; le++ )
			array[le] = arr[le + first];
	}

	~MVArray()
	{
		delete [] array;
	}

	T_ARRAY& operator[](long index)
	{
		return(array[index]);
	}

	size_t	Size() { return(m_size); }

	class Iterator
	{
	private:	
		T_ARRAY*	runner;
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

			return( itr );
		}

		Iterator operator--(int value)
		{
			Iterator itr(runner);

			(*this) -= 1;

			return( itr );
		}

		bool	operator == (Iterator& itr)
		{
			return( this->runner == itr.runner );
		}

		bool	operator != (Iterator& itr)
		{
			return( !((*this) == itr) );
		}

		void	operator=(T_ARRAY value)
		{
			*runner = value;
		}

		T_ARRAY operator*()
		{
			return(*runner);
		}
	};

	Iterator	begin()
	{
		return( Iterator(&array[0]) );
	}

	Iterator	end()
	{
		return( Iterator(&array[m_size]) );
	}
};

