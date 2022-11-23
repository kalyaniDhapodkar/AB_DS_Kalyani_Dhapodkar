

/**
 * @file:	mv_singly_list.hpp
 * @author:	MarshallingVoid	(marshallingvoid@gmail.com) 
 * @brief:	This file contains the implementation of <class SinglyLinkedList> and its Interface<public> and Helper<private> function using cpp.
 * @date:	10/11/2022
 * @version	1.0
 * 
 * @copyright	Copyright (c) 2022
 * 
 */

#pragma	once

//	Headers

#include	"mv_list.hpp"
#include	"mv_base_iterator.hpp"

//	Constant Literals

#ifndef	SUCCESS
#define	SUCCESS	0
#endif

#ifndef	FAILURE
#define	FAILURE	1
#endif

//	Typedef
#ifndef	RET_T
#define	RET_T
typedef	int 	ret_t;
#endif

//	Struct Node Definition
template<typename T_NODE>
class Node
{
private:
	T_NODE	m_data;
	Node*	mp_next;

	Node( T_NODE data ) : m_data(data) 
	{ 
		// Code
		mp_next = NULL;
	}

	template<typename T_NODE>
	friend class SinglyLinkedList;
};

// Class SinglyLinkedList Definition
template<typename T_SLL>
class SinglyLinkedList : public IList<T_SLL>
{
private:
	Node<T_SLL>*		mp_head;
	Node<T_SLL>*		mp_tail;
	size_t		m_size;

	ret_t GenericInsert( Node<T_SLL>* first, Node<T_SLL>* mid, Node<T_SLL>* last )
	{
		// Code
		mid->mp_next = last;

		first->mp_next = mid;
	
		m_size++;

		if( NULL == mid->mp_next )
			mp_tail = mid;

		return(SUCCESS);
	}

	T_SLL GenericRemove(Node<T_SLL>* node)
	{
		// Code
		Node<T_SLL>* d_node = node->mp_next;

		node->mp_next = d_node->mp_next;

		d_node->mp_next = NULL;

		T_SLL to_return_data = d_node->m_data;

		free(d_node);

		if( NULL == node->mp_next )
			mp_tail = node;

		m_size--;

		return(to_return_data);
	}

public:

	SinglyLinkedList()
	{
		// Code
		mp_head = new Node<T_SLL>(0);	//	Sentinel
		mp_tail = mp_head;
		m_size = 0;
	}

	~SinglyLinkedList()
	{
		// Code

		Node<T_SLL>* prunner = mp_head->mp_next;

		while( true )
		{
			Node<T_SLL>* prunner_next = prunner->mp_next;

			std::cout << "Deleting: " << prunner->m_data << std::endl;

			delete(prunner);

			prunner = prunner_next;

			if( NULL == prunner )
				break;
		}

		delete(mp_head);
	}

	// List Insertion Functions
	ret_t	InsertFront(T_SLL new_data)
	{
		// Code
		return( GenericInsert(mp_head, new Node<T_SLL>(new_data), mp_head->mp_next) );
	}

	ret_t	InsertBack(T_SLL new_data)
	{
		// Code
		return( GenericInsert(mp_tail, new Node<T_SLL>(new_data), mp_tail->mp_next) );
	}

	ret_t	InsertAfter(T_SLL new_data, T_SLL e_data)
	{
		// Code
		if( 0 == m_size )
			return(FAILURE);

		Node<T_SLL>*	prunner = mp_head->mp_next;

		while( NULL != prunner )
		{
			if( prunner->m_data == e_data )
				break;

			prunner = prunner->mp_next;
		}

		if( NULL == prunner )
		{
			std::cerr << "ERROR: " << e_data << " not found in the list." << std::endl;
			return(FAILURE);
		}

		return( GenericInsert( prunner, new Node<T_SLL>(new_data), prunner->mp_next ) );
	}

	ret_t	InsertBefore(T_SLL new_data, T_SLL e_data)
	{
		//	Code
		if( 0 == m_size )
			return(FAILURE);

		Node<T_SLL>* prunner = mp_head;

		while( NULL != prunner->mp_next )
		{
			if( e_data == prunner->mp_next->m_data )
				break;

			prunner = prunner->mp_next;
		}

		if(NULL == prunner->mp_next)
			return(FAILURE);

		return( GenericInsert(prunner, new Node<T_SLL>(new_data), prunner->mp_next) );
	}

	ret_t	InsertAt(T_SLL new_data, long index)
	{
		// Code

		if( 0 == m_size || index > m_size)
			return(FAILURE);

		if( 0 == index )
			return( InsertFront(new_data) );
		else if( m_size == index )
			return( InsertBack(new_data) );

		Node<T_SLL>* prunner = mp_head;

		for( long le = 0; le < index; ++le)
			prunner = prunner->mp_next;

		return( GenericInsert(prunner, new Node<T_SLL>(new_data), prunner->mp_next) ); 
	}

	//	List Removal Functions
	T_SLL	RemoveFront() 
	{ 
		// Code

		if( 0 == m_size )
		{
			std::cerr << "ERROR: List not found.\n";
			return((T_SLL)NULL);
		}

		return( GenericRemove(mp_head) ); 
	}

	T_SLL	RemoveBack() 
	{ 
		// Code
		if( 0 == m_size)
		{
			std::cerr << "ERROR: List not found\n";
			return((T_SLL)NULL);
		}

		Node<T_SLL>* prunner = mp_head;

		while( prunner->mp_next->mp_next )
			prunner = prunner->mp_next;

		return( GenericRemove(prunner) );
	}

	T_SLL	RemoveAfter(T_SLL e_data) 
	{ 
		// Code

		if( 0 == m_size)
		{
			std::cerr << "ERROR: List not found\n";
			return((T_SLL)NULL);
		}

		Node<T_SLL>* prunner = mp_head;

		while( true )
		{
			if( e_data == prunner->m_data )
				break;

			prunner = prunner->mp_next;

			if( NULL == prunner->mp_next)
			{
				std::cerr << "ERROR: No Data to remove after\n";
				return((T_SLL)NULL);
			}

		}

		return(GenericRemove(prunner)); 
	}

	T_SLL 	RemoveBefore(T_SLL e_data) 
	{ 
		// Code
		if( 0 == m_size )
		{
			std::cerr << "ERROR: List not found\n";
			return((T_SLL)NULL);
		}

		if( 1 == m_size )
		{
			std::cerr << "ERROR: No Data to remove before\n";
			return((T_SLL)NULL);
		}


		Node<T_SLL>* prunner = mp_head;

		while( true )
		{
			if( e_data == prunner->mp_next->mp_next->m_data )
				break;

			prunner = prunner->mp_next;

			if( NULL == prunner->mp_next->mp_next )
			{
				std::cerr << "ERROR: Existing data not found\n";
				return((T_SLL)NULL);
			}
		}

		return( GenericRemove(prunner) ); 
	}
	
	T_SLL	RemoveAt(long index) 
	{ 
		// Code
		if( 0 == m_size )
		{
			std::cerr << "ERROR: List not found.\n";
			return((T_SLL)NULL);
		}

		if( 0 == index )
			return( RemoveFront() );
		else if( index == m_size-1 )
			return( RemoveBack() );

		if( index >= m_size )
		{
			std::cerr << "ERROR: Index Out of bound.\n";
			return((T_SLL)NULL);
		}

		Node<T_SLL>* prunner = mp_head;

		for( long le = 0; le < index; ++le)
			prunner = prunner->mp_next;

		return( GenericRemove(prunner) ); 
	}

	T_SLL DataAt(long index)
	{
		// Code
		if( 0 == m_size )
		{
			std::cerr << "ERROR: List not found.\n";
			return((T_SLL)NULL);
		}
		
		if( index >= m_size )
		{
			std::cerr << "ERROR: Index Out of bound.\n";
			return((T_SLL)NULL);
		}

		Node<T_SLL>* prunner = mp_head->mp_next;

		for( long le = 0; le < index; ++le )
			prunner = prunner->mp_next;

		return( prunner->m_data );
	}

	//	Data Print Function
	void ShowList()
	{
		// Code

		Node<T_SLL>* prunner = mp_head->mp_next;

		std::cout << "Singly List:" << std::endl;
		std::cout << "{START}->";
		for( prunner; NULL != prunner; prunner = prunner->mp_next)
		{
			std::cout << "{" << prunner->m_data << "}->";
		}
		std::cout << "{END}" << std::endl << std::endl;
	}

	T_SLL Head() const { return( mp_head->mp_next->m_data ); }
	
	T_SLL Tail() const { return( mp_tail->m_data ); }

	T_SLL operator[](long index)
	{
		// Code
		return( DataAt(index) );
	}

	size_t	Size() const { return(m_size); }

	template<typename T_OUT>
	friend std::ostream& operator<<(std::ostream& out, SinglyLinkedList<T_OUT>& list);

	friend class Iterator;

	class Iterator : public mv_base_iterator<T_SLL>
	{
	private:
		Node<T_SLL>*	itr_pnode;
		SinglyLinkedList<T_SLL> list;

	public:
		Iterator(SinglyLinkedList<T_SLL>& list, Node<T_SLL>* pnode)
		{
			// Code
			itr_pnode = pnode;
			this->list = list;
		}

		Iterator(Node<T_SLL>* pnode)
		{
			// Code
			itr_pnode = pnode;
		}

		Iterator& operator++()
		{
			//	Code
			itr_pnode = itr_pnode->mp_next;

			return(*this);
		}

		Iterator& operator--()
		{
			// Code
			Node<T_SLL>* prunner = list.mp_head;

			while( true )
			{
				if( prunner->mp_next == itr_pnode )
				{
					itr_pnode = prunner;
					break;
				}
			}

			if( prunner == list.mp_head )
				itr_pnode = NULL;

			return(*this);
		}
		
		Iterator operator++(int value)
		{
			Node<T_SLL>* temp = itr_pnode;

			++(*this);

			return( Iterator(temp) );
		}

		Iterator operator--(int value)
		{
			// Code
			Node<T_SLL>* temp = itr_pnode;

			--(*this);

			return(Iterator(temp));
		}

		Iterator operator+(int value)
		{
			// Code
			Iterator<T_SLL> temp = Iterator(itr_pnode);
			for( long le = 0; le < value; ++le )
			{
				++(temp);
				if( NULL == temp.itr_pnode )
					break;
			}
			return( temp );
		}
		
		Iterator operator-(int value)
		{
			// Code
			Iterator<T_SLL> temp = Iterator(itr_pnode);
			for( long le = 0; le < value; ++le )
			{
				--(temp);
				if( NULL == temp.itr_pnode )
					break;
			}
			return( temp );
		}

		Iterator operator+=(int value)
		{
			// Code
			for( long le = 0; le < value; ++le )
			{
				++(*this);
				if( NULL == itr_pnode )
					break;
			}
			return( Iterator(*this) );
		}

		Iterator operator-=(int value)
		{
			// Code
			for( long le = 0; le < value; ++le )
			{
				--(*this);
				if( NULL == itr_pnode )
					break;
			}
			return( Iterator(*this) );
		}

		bool operator==(Iterator& itr)
		{
			// Code
			return( itr.itr_pnode == this->itr_pnode ); 
		}

		bool operator!=(Iterator& itr)
		{
			// Code
			return( !( itr == (*this) )  );
		}

		T_SLL operator*()
		{
			// Code
			return( itr_pnode->m_data );
		}
	};

	Iterator begin()
	{
		return( Iterator((*this), this->mp_head->mp_next) );
	}

	Iterator end()
	{
		return( Iterator(this->mp_tail->mp_next) );
	}
};

template<typename T_OUT>
std::ostream& operator<<(std::ostream& out, SinglyLinkedList<T_OUT>& list)
{
	// Code

	out << "Singly Linear Linked List:" << std::endl;
	out << "{START}->";
	for( long le = 0; le < list.Size(); ++le)
	{
		out << "{" << list[le] << "}->";
	}
	out << "{END}" << std::endl;

	return(out);
}
