

#pragma	once

#include	"mv_dcll.hpp"

template<typename T_STACK>
class MV_Stack : private MV_DCLL<T_STACK>
{
public:
	MV_Stack()
	{}

	~MV_Stack()
	{}

	ret_t Push(T_STACK data)
	{
		// Code
		return(this->InsertBack(data));
	}

	T_STACK Pop()
	{
		return( this->RemoveBack() );
	}

	T_STACK Peek()
	{
		return( this->Tail() );
	}

	Iterator begin()
	{
		// Code
		return(static_cast<MV_DCLL<T_STACK>*>(this)->begin());
	}

	Iterator end()
	{
		// Code
		return(static_cast<MV_DCLL<T_STACK>*>(this)->end());
	}

	ret_t Show()
	{
		// Code
		std::cout << "Stack: " << std::endl;
		std::cout << "|\tTOP\t|" << std::endl << "\t|" << std::endl;
		auto itr = static_cast<MV_DCLL<T_STACK>*>(this)->rbegin();
		for(itr;
			itr != static_cast<MV_DCLL<T_STACK>*>(this)->rend();
			--itr)
		{
			std::cout << "|\t" << (*itr) << "\t|" << std::endl << "\t|" << std::endl;
		}
		std::cout << "|\t" << (*itr) << "\t|" << std::endl << "\t|" << std::endl;
		std::cout << "|\tSTART\t|" << std::endl << std::endl;

		return(SUCCESS);
	}
};


