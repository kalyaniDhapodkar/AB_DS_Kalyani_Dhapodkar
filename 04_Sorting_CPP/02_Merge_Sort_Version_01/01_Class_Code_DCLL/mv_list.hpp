

/**
 * @file:	mv_list.hpp
 * @author:	MarshallingVoid	(marshallingvoid@gmail.com) 
 * @brief:	This file contains the declaration of <class IList>(Interface) to be inherited by all the list for further implemention
 * @date:	10/11/2022
 * @version	1.0
 * 
 * @copyright	Copyright (c) 2022
 * 
 */

#pragma	once

#ifndef	_MV_LIST
#define	_MV_LIST

#ifndef	RET_T
#define	RET_T
typedef	int 	ret_t;
#endif

template<typename T_LIST>
class IList
{
public:

	// List Insertion Functions
	virtual	ret_t	InsertFront(T_LIST data) = 0;
	virtual ret_t	InsertBack(T_LIST data) = 0;
	virtual ret_t	InsertAfter(T_LIST new_data, T_LIST e_data) = 0;
	virtual ret_t	InsertBefore(T_LIST new_data, T_LIST e_data) = 0;
	virtual ret_t	InsertAt(T_LIST new_data, long index) = 0;

	//	List Removal Functions
	virtual	T_LIST	RemoveFront() = 0;
	virtual T_LIST	RemoveBack() = 0;
	virtual T_LIST	RemoveAfter(T_LIST e_data) = 0;
	virtual T_LIST 	RemoveBefore(T_LIST e_data) = 0;
	virtual T_LIST	RemoveAt(long index) = 0;
};

#endif	/* _MV_LIST */

