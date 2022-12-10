

/**
 * @file	mv_dcll.hpp
 * @author	Kalyani Dhapodkar (dhapodkarkalyani@gmail.com)
 * @brief	This file contains all the class definitions and data members and member functions required to implement Doubly Circular Linked List. 
 * @date	07/12/2022
 * @version	1.0
 * 
 * @copyright	Copyright (c) 2022
 */

#pragma once

// Headers
#include    "mv_list.hpp"

// Constant Literals
#ifndef     SUCCESS
#define     SUCCESS     0
#endif

#ifndef     FAILURE
#define     FAILURE     1
#endif

// Typedefs
typedef     int     ret_t;

// Node Class Definition
template<typename T_NODE>
class Node
{
private:
    T_NODE m_data;
    Node<T_NODE>*   mp_next;
    Node<T_NODE>*   mp_prev;

    Node( T_NODE data) : m_data(data), mp_next(this), mp_prev(this)
    { }

    ~Node() { }

    template<typename T_NODE>
    friend class MV_DCLL;
};

template<typename T_LIST>
class MV_DCLL : public IList<T_LIST>
{
private:
    Node<T_LIST>*   mp_head;
    Node<T_LIST>*   mp_tail;
    size_t          m_size;

    // List Heper Functions
    ret_t  GenericInsert(Node<T_LIST>* first, Node<T_LIST>* mid, Node<T_LIST>* last)
    {
        // Code
        mid->mp_next = last;
        mid->mp_prev = first;

        first->mp_next = mid;
        last->mp_prev = mid;

        m_size++;

        mp_tail = mp_head->mp_prev;

        return(SUCCESS);
    }

    T_LIST  GenericRemove(Node<T_LIST>* d_node)
    {
        // Code
        Node<T_LIST>* first = d_node->mp_prev;
        Node<T_LIST>* last = d_node->mp_next;

        first->mp_next = last;
        last->mp_prev = first;

        T_LIST to_return_data = d_node->m_data;

        delete(d_node);

        m_size--;

        mp_tail = mp_head->mp_prev;

        return(to_return_data);
    }

public:
    MV_DCLL()
    {
        // Code
        mp_head = new Node<T_LIST>((T_LIST)0);
        mp_tail = mp_head;
        m_size = 0;
    }

    ~MV_DCLL()
    {
        // Code
        Node<T_LIST>* prunner = mp_head->mp_next;

        for(prunner; prunner != mp_head; )
        {
            Node<T_LIST>* prunner_next = prunner->mp_next;

            delete(prunner);

            prunner = prunner_next
        }

        delete(mp_head);
    }

    // List Interface Function
    ret_t InsertFront(T_LIST new_data)
    {
        // Code
        return( GenericInsert(mp_head, new Node<T_LIST>(new_data), mp_head->mp_next) );
    }

    ret_t InsertBack(T_LIST new_data)
    {
        // Code
        return( GenericInsert(mp_tail, new Node<T_LIST>(new_data), mp_head) );
    }

    ret_t InsertAfter(T_LIST new_data, T_LIST e_data)
    {
        // Code
        if( 0 == m_size)
        {
            std::cerr << "ERROR: No List Found." << std::endl;
            return(FAILURE);
        }

        Node<T_LIST>* prunner = mp_head->mp_next;

        for(prunner; prunner != mp_head; prunner = prunner->mp_next)
        {
            if(prunner->m_data == e_data)
                break;
        } 

        if(mp_head == prunner)
        {
            std::cerr << "ERROR: Existing data not found." << std::endl;
            return(FAILURE);
        }

        return( GenericInsert(prunner, new Node<T_LIST>(new_data), prunner->mp_next) );
    }

    ret_t InsertBefore(T_LIST new_data, T_LIST e_data)
    {
        // Code
        if( 0 == m_size)
        {
            std::cerr << "ERROR: No List Found." << std::endl;
            return(FAILURE);
        }

        Node<T_LIST>* prunner = mp_head->mp_next;

        for(prunner; prunner != mp_head; prunner = prunner->mp_next)
        {
            if(prunner->m_data = e_data)
                break;
        }

        if(mp_head == prunner)
        {
            std::cerr << "ERROR: Existing data Not found." << std::endl;
            return(FAILURE);
        }

        return( GenericInsert(prunner->mp_next, new Node<T_LIST>(new_data), prunner) );
    }

    ret_t InsertAt(T_LIST new_data, long index)
    {
        // Code
        if(0 == m_size)
        {
            std::cerr << "ERROR: List Not Found." << std::endl;
            return(FAILURE);
        }

        if(index > m_size)
        {
            std::cerr << "ERROR: Index Out Of Bound." << std::endl;
            return(FAILURE);
        }

        if( 0 == index)
            return( InsertFront(new_data) );
        else if(m_size == index)
            return( InsertBack(new_data) );

        Node<T_LIST>* prunner = mp_head;

        for(long le = 0; le < index; le++)
            prunner = prunner->mp_next;

        return( GenericInsert(prunner, new Node<T_LIST>(new_data), prunner->mp_next) );
    }

    // List Deletion Functions

    T_LIST RemoveFront()
    {
        // Code
        if( 0 == m_size)
        {
            std::cerr << "ERROR: List Not Found." << std::endl;
            return((T_LIST)0);
        }

        return( GenericRemove(mp_head->mp_next) );
    }

    T_LIST RemoveBack()
    {
        // Code
        if( 0 == m_size)
        {
            std::cerr << "ERROR: List Not Found." << std::endl;
            return((T_LIST)0);
        }

        return( GenericRemove(mp_tail) );
    }

    T_LIST RemoveAfter(T_LIST e_data)
    {
        // Code
        if( 0 == m_size)
        {
            std::cerr << "ERROR: List Not Found." << std::endl;
            return((T_LIST)0);
        }

        Node<T_LIST>* prunner = mp_head->mp_next;

        for(prunner; prunner != mp_head; prunner = prunner->mp_next)
        {
            if(prunner->m_data == e_data)
                break;
        }

        if(mp_head == prunner)
        {
            std::cerr << "ERROR: Existing Data Not Found." << std::endl;
            return((T_LIST)0);
        }

        if(mp_tail == prunner)
        {
            prunner = mp_head;
        }

        return( GenericRemove(prunner->mp_next) );
    }

    T_LIST RemoveBefore(T_LIST e_data)
    {
        // Code
        if(0 == m_size)
        {
            std::cerr << "ERROR: List Not Found." << std::endl;
            return((T_LIST)0);
        }

        Node<T_LIST>* prunner = mp_head->mp_next;

        for(prunner; prunner != mp_head; prunner = prunner->mp_next)
        {
            if(prunner->m_data == e_data)
                break;
        }

        if(mp_head == prunner)
        {
            std::cerr << "ERROR: Existing Data Not Found." << std::endl;
            return((T_LIST)0);
        }

        if(mp_head->mp_next == prunner)
        {
            prunner = mp_head;
        }

        return( GenericRemove(prunner->mp_prev) );
    }

    T_LIST RemoveAt(long index)
    {
        // Code
        if( 0 == m_size)
        {
            std::cerr << "ERROR: List Not Found." << std::endl;
            return((T_LIST)0);
        }

        if(index >= m_size)
        {
            std::cerr << "ERROR: Index Out Of Bound." << std::endl;
            return((T_LIST)0);
        }

        if( 0 == index)
            return( RemoveFront() );
        if(m_size-1 == index)
            return( RemoveBack() );

        Node<T_LIST>* prunner = mp_head;

        for(long le = 0; le < index; le++)
            prunner = prunner->mp_next;

        return( GenericRemove(prunner->mp_next) );
    }

    // List Data Functions

    ret_t ShowList()
    {
        // Code
        std::cout << "Doubly Circular Linked List: " << std::endl;
        std::cout << "{START}->";
        for(Node<T_LIST>* prunner = mp_head->mp_next;
            prunner != mp_head; 
            prunner = prunner->mp_next)
        {
            std::cout << "{" << prunner->data << "}->";
        }
        std::cout << "{END}" << std::endl << std::endl;

        return(SUCCESS);
    }

    ret_t ForwardPrint()
    {
        // Code
        return(ShowList());
    }

    ret_t ReversePrint()
    {
        // Code
        std::cout << "Reverse Doubly Circular Linked List:" << std::endl;
        std::cout << "{START}->";
        for(Node<T_LIST>* prunner = mp_tail; 
            prunner != mp_head; 
            prunner = prunner->mp_prev)
        {
            std::cout << "{" << prunner->data << "}->";
        }
        std::cout << "{END}->" << std::endl;

        return(SUCCESS);
    }

    T_LIST Head() const { return(mp_head->mp_next->data); }
    T_LIST Tail() const { return(mp_tail->data); }
    size_t Size() const { return(m_size); }

    // List Manipulation Functions
    MV_DCLL<T_LIST>* Merge(MV_DCLL<T_LIST>* plist)
    {
        // Code
        if( 0 == this->m_size   ||
            NULL == plist       ||
            0 == plist->m_size)
        {
            std:cerr << "ERROR: List Not Present to Merge." << std::endl;
            return(NULL);
        }

        Node<T_LIST>* prunner1 = this->mp_head->mp_next;
        Node<T_LIST>* prunner2 = plist->mp_head->mp_next;

        MV_DCLL<T_LIST>* plist_new = new MV_DCLL<T_LIST>();

        // Test 1: Both the list Present i.e 
        while(  prunner1 != this->mp_head && 
                prunner2 != plist->mp_head)
        {
            if( prunner1->m_data <= prunner2->m_data)
            {
                plist_new->InsertBack(prunner1->m_data);
                prunner1 = prunner1->mp_next;
            }
            else
            {
                plist_new->InsertBack(prunner2->m_data);
                prunner2 = prunner2->mp_next;
            }
        }

        // Test 2: List1->size < list2->size
        if( prunner1 == this->mp_head &&
            prunner2 != plist->mp_head )
        {
            while(prunner2 != plist->mp_head )
            {
                plist_new->InsertBack(prunner2->m_data);
                prunner2 = prunner2->mp_next;
            }
        }

        // Test 3: List2->size < List1->size
        if( prunner2 == plist->mp_head &&
            prunner1 != this->mp_head )
        {
            while( prunner1 != this->mp_head)
            {
                plist_new->InsertBack(prunner1->m_data);
                prunner1 = prunner1->mp_next;
            }
        }

        return(plist_new);
    }

    // Iterator
    class Iterator
    {
    private:
        Node<T_LIST>* itr;
        MV_DCLL<T_LIST>* list;
    public:
        Iterator(Node<T_LIST>* itr, MV_DCLL<T_LIST>* list) : itr(itr), list(list) { }

        ~Iterator() {}

        Iterator& operator++()
        {
            // Code
            itr = itr->mp_next;

            return(*this);
        }

        Iterator& operator--()
        {
            // Code
            itr = itr->mp_prev;

            return(*this);
        }

        Iterator operator++(int value)
        {
            // Code
            Iterator temp = Iterator(itr, list);

            ++(*this);

            return(temp);
        }

        Iterator operator--(int value)
        {
            // Code
            Iterator temp = Iterator(itr, list);

            --(*this);

            return(temp);
        }

        Iterator operator+(long value)
        {
            Iterator temp = Iterator(itr, list);
            
            for(long le = 0; le < value; le++)
                ++temp;

            return(temp);
        }

        Iterator operator-(long value)
        {
            Iterator temp = Iterator(itr, list);

            for(long le = 0; le < value; le++)
                --temp;

            return(temp);
        }

        Iterator& operator+=(long value)
        {
            // Code
            for(long le = 0; le < value; le++)
                ++(*this);

            return(*this);
        }

        Iterator& operator-=(long value)
        {
            // Code
            for(long le = 0; le < value; le++)
                --(*this);

            return(*this);
        }

        Iterator& operator=(T_LIST value)
        {
            itr->m_data = value;

            return(*this);
        }

        bool    operator==(Iterator& itr)
        {
            return( this->itr == itr.itr);
        }

        bool    operator!=(Iterator& itr)
        {
            return( !((*this) == itr) );
        }

        T_LIST operator*()
        {
            // Code
            return(itr->m_data);
        }
    };

    Iterator begin()
    {
        // Code
        return( Iterator(this->mp_head->mp_next, this) );
    }

    Iterator end()
    {
        // Code
        return( Iterator(this->mp_head, this) );
    }
};

template<typename T_OUT>
std::ostream& operator<<(std::ostream& out, MV_DCLL<T_OUT>* list)
{
    // Code
    out << "Doubly Circulat Linked List:" << std::endl;
    out << "{START}->";
    for(auto itr = list->begin(); itr != list->end(); ++itr)
        out << "{" << (*itr) << "}->";
    out << "{END}" << std::endl;

    return(out); 
}

