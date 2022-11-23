


#pragma	once

//	Headers
#include	"mv_dcll.hpp"

//	class

template<typename T_QUEUE>
class MV_Queue : private MV_DCLL<T_QUEUE>
{
public:
	MV_Queue() {}

	~MV_Queue() {}

	inline ret_t	PushBack(T_QUEUE data)
	{
		// Code
		return( InsertBack(data) );
	}	

	inline T_QUEUE PopFront()
	{
		// Code
		return(RemoveFront());
	}

	inline T_QUEUE GetFront()
	{
		// Code
		return(Head());
	}

	inline T_QUEUE GetBack()
	{
		// Code
		return(Tail());
	}

	inline size_t Size() 
	{
		// Code
		return( static_cast<MV_DCLL<T_QUEUE>*>(this)->Size() );
	}

	inline bool Empty() 
	{
		// Code
		return( 0 == Size() );
	}

	T_QUEUE operator[](long index)
	{
		// Code
		/*return( (*static_cast<MV_DCLL<T_QUEUE>*>(this))[index] );*/

		if( index >= Size() )
		{
			std::cerr << "ERROR: Index out of bound." << std::endl;
			return(nullptr);
		}	

		long le = 0;
		auto itr;
		for(itr = begin(); le < index; ++le, ++itr);
		
		return(*itr);
	}

	inline Iterator begin()
	{
		// Code
		return( static_cast<MV_DCLL<T_QUEUE>*>(this)->begin() );
	}

	inline Iterator end()
	{
		// Code
		return( static_cast<MV_DCLL<T_QUEUE>*>(this)->end() );
	}

	ret_t Show()
	{
		// Code
		std::cout << "Queue:" << std::endl;
		std::cout << "{START}-";
 		for( auto itr = static_cast<MV_DCLL<T_QUEUE>*>(this)->begin(); 
			 itr != static_cast<MV_DCLL<T_QUEUE>*>(this)->end();
			 ++itr)
		{
			std::cout << "{" << (*itr) << "}-";
		}
		std::cout << "{END}" << std::endl << std::endl;
	}

	template<typename T_QUEUE>
	friend std::ostream& operator<<(std::ostream& out, MV_Queue<T_QUEUE>*& queue);
};

template<typename T_OUT>
std::ostream& operator<<(std::ostream& out, MV_Queue<T_OUT>*& queue)
{
	// Code
	out << "Queue:" << std::endl;
	out << "{START}-";
		for( auto itr = static_cast<MV_DCLL<T_OUT>*>(queue)->begin(); 
		 itr != static_cast<MV_DCLL<T_OUT>*>(queue)->end();
		 ++itr)
	{
		out << "{" << (*itr) << "}-";
	}
	out << "{END}" << std::endl << std::endl;

	return(out);
}
