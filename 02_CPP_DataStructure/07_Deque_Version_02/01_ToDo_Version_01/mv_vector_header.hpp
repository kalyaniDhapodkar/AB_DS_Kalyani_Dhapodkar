
#pragma once

#include <cstdarg>

// Constant Literals
#ifndef  	SUCCESS 	
#define  	SUCCESS  	0
#endif

#ifndef  	FAILURE
#define  	FAILURE  	1
#endif

#ifndef  	DEFAULT_SIZE
#define  	DEFAULT_SIZE  	32
#endif 	

// Type Declarations
template<typename T>
class MVVector;

typedef  	int ret_t;

// Global Function Delarations
template<typename T>
std::ostream& operator<<(std::ostream& out, MVVector<T>& vec);

template<typename T>
std::ostream& operator<<(std::ostream& out, MVVector<T>*& vec);

/*
	Class :
		Data Object : data menbers
		Functions 	: Member Functiions/ Methods
*/

// Type Definition
template<typename T>
class MVVector
{
private:

	T* m_data_array;
    long  m_no_of_elements;
    long  m_capacity;

	bool IsArray() const
	{
		if(m_data_array)
			return(true);

		return(false);
	}

public:

	MVVector()
	{
		// Code
		this->m_data_array = NULL;
		this->m_no_of_elements = 0;
		this->m_capacity = DEFAULT_SIZE;

		this->m_data_array = (T*)realloc(this->m_data_array, DEFAULT_SIZE * sizeof(T));
		if( NULL == m_data_array)
		{
			std::cerr << "ERROR: Out of Memory." << std::endl;
		}

		memset(this->m_data_array, 0, DEFAULT_SIZE * sizeof(T));
	}

	MVVector(size_t custom_size)
	{
		// Code
		this->m_data_array = NULL;
		this->m_no_of_elements = 0;
		this->m_capacity = custom_size;

		this->m_data_array = (T*)realloc(this->m_data_array, custom_size * sizeof(T));
		if( NULL == m_data_array)
		{
			std::cerr << "ERROR: Out of Memory." << std::endl;
		}

		memset(this->m_data_array, 0, DEFAULT_SIZE * sizeof(T));
	}

	~MVVector()
	{
		// Code
		if(this->m_data_array)
		{
			free(this->m_data_array);
			this->m_data_array = NULL;
		}

		this->m_no_of_elements = 0;
	}

	ret_t PushBack(T data)
	{
		// Code
		if( !(IsArray()) )
		{
			std::cerr << "ERROR: Vector Not Found." << std::endl;
			return(FAILURE);
		}

		this->m_data_array[this->m_no_of_elements] = data;
		this->m_no_of_elements++;

		if(this->m_no_of_elements == this->m_capacity)
		{
			this->m_capacity = this->m_capacity * 2;
			this->m_data_array = (T*)realloc(this->m_data_array, this->m_capacity * sizeof(T));
		}
	
		return(SUCCESS);
	}

	ret_t PushFront(T data)
	{
		// Code
 	   	 this->m_no_of_elements++;
	
	 	   if (this->m_capacity >= this->m_no_of_elements)
	 	   {
	 	        this->m_capacity =  this->m_capacity * 2;
	 	        this->m_data_array = (T*)realloc( this->m_data_array,  this->m_capacity * sizeof(T));
	 	   }
	
	 	   for(long le = this->m_no_of_elements-1; le > 0; le--)
	 	   {
	 	       this->m_data_array[le] = this->m_data_array[le-1];
	 	   }
	
	 this->m_data_array[0] = data;

		return(SUCCESS);
	}

	ret_t operator+(T data)
	{
		return(PushBack(data));
	}

	// Variadic Push Back
	ret_t PushBackv(long no_of_values, ...)
	{
		va_list args;

		va_start(args, no_of_values);
		for(long le = 0; le < no_of_values; le++)
		{
			(*this) + va_arg(args, T);
		}
		va_end(args);

		return(SUCCESS);
	}

	// Pop Back
	T PopBack()
	{
		// Code
		if( !(IsArray()) ||
			0 == m_no_of_elements )
		{
			std::cerr << "ERROR: Vector Not Found." << std::endl;
			return((T)0);
		}

		m_no_of_elements--;

		T to_return_data = m_data_array[m_no_of_elements];

		if( m_no_of_elements <= m_capacity/2 &&
			0 != m_no_of_elements)
		{
			m_capacity = m_capacity / 2;
			m_data_array = (T*)realloc(m_data_array, m_capacity * sizeof(T));
		}
	
		return(to_return_data);
	}

	T PopFront()
	{
		// Code
		T to_return_data = this->m_data_array[0];

		for(long le = 0; le < this->m_no_of_elements; le++)
		{
			this->m_data_array[le] = this->m_data_array[le+1];
		}

		this->m_no_of_elements--;

		if(this->m_no_of_elements < this->m_capacity/2)
		{
			this->m_capacity = this->m_capacity/2;
			this->m_data_array = (T*)realloc(this->m_data_array, this->m_capacity * sizeof(T));
		}

		return(to_return_data);
	}

	//Retrive Data
	T DataAt(long index)const
	{
		// Code
		if( !(IsArray()) ||
			0 == m_no_of_elements)
		{
			std::cerr << "ERROR: Vector Not Found." << std::endl;
			return((T)0);
		}

		if( index >= m_no_of_elements)
		{
			std::cerr << "ERROR: Index Out of Bound." << std::endl;
			return((T)0);
		}

		return(m_data_array[index]);
	}

	/*
		T operator[](long index)const

		--> T operator[](const MVVector* this,
						 const long index)
	*/

	T operator[](long index)const { return(DataAt(index)); }

	// Getter size
	size_t Size()const { return(m_no_of_elements); }

	// Getter Capacity
	size_t Capacity()const { return(m_capacity); }

	class Iterator
	{
	private:
		T* m_data_ptr;

	public:
		Iterator(T* data_ptr)
		{
			// code
			this->m_data_ptr = data_ptr;
		}

		~Iterator()
		{
			this->m_data_ptr = NULL;
		}

		// Pre Increment
		Iterator& operator++()
		{
			// Code
			this->m_data_ptr++;
			return(*this);
		}

		// Post Increment
		Iterator operator++(int value)
		{
			// Code
			Iterator itr = *this;
			++*this;
			return(itr);
		}

		// Pre decrement
		Iterator& operator--()
		{
			// Code
			this->m_data_ptr--;
			return(*this);
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
			Iterator itr = Iterator(m_data_ptr + value);

			return(itr);
		}

		Iterator operator-(int value)
		{
			// Code
			Iterator itr = Iterator(m_data_ptr - value);

			return(itr);
		}

		Iterator operator+=(int value)
		{
			this->m_data_ptr = this->m_data_ptr + value;

			return(*this);
		}

		Iterator operator-=(int value)
		{
			// Code
			this->m_data_ptr = this->m_data_ptr - value;

			return(*this);
		}

		bool operator!=(Iterator& itr)
		{
			// Code
			return( !((*this) == itr) );
		}

		bool operator==(Iterator itr)
		{
			// Code
			return(this->m_data_ptr == itr.m_data_ptr);
		}

		T operator*()
		{
			// Code
			return(*m_data_ptr);
		}

	};

	Iterator begin()
	{
		return(Iterator(m_data_array));
	}

	Iterator end()
	{
		return(Iterator(&m_data_array[m_no_of_elements]));
	}

	void ForwardTraversal()
	{
		// Code
		std::cout << (*this);
	}

	void ReverseTraversal()
	{
		// Code
		std::cout << this;
	}

};

template<typename T>
std::ostream& operator<<(std::ostream& out, MVVector<T>& vec)
{
	std::cout << "{START}-" ;
	for(auto itr = vec.begin(); itr != vec.end(); ++itr)
	{
		std::cout << "{" << *itr << "}-" ;
	}
	std::cout << "{END}" << std::endl;

	return(out);
}

template<typename T>
std::ostream& operator<<(std::ostream& out, MVVector<T>*& vec)
{
	std::cout << "{START}-" ;
	for(auto itr = vec->end()-1; itr != vec->begin()-1; --itr)
	{
		std::cout << "{" << *itr << "}-" ;
	}
	std::cout << "{END}" << std::endl;

	return(out);
}


template<typename T>
std::ostream& operator<<(std::ostream& out, MVVector<T>*&& vec)
{
	std::cout << "{START}-" ;
	for(auto itr = vec->end()-1; itr != vec->begin()-1; --itr)
	{
		std::cout << "{" << *itr << "}-" ;
	}
	std::cout << "{END}" << std::endl;

	return(out);
}


