

Directory : 04_Queue_Version_03\01_Class_Code

Files : 1) mv_queue.hpp
	2) mv_queue_client.cpp
	3) mv_dcll.hpp
	4) mv_list.hpp

Description :

	1) mv_queue.hpp  : This header files contains all the declaration as well as definitions (as because of templates) of interface functions
			 of 'mv_queue'

	Updation :
		1) Queue here is implemented using doubly circular linked list, on server side queue is using dcll to enque, deque, print and destory data in queue.


	2) mv_queue_client.c : This source file contains interface function calls made by client in order to manage
	   generic data on queue data structure and therefore needs callback function as client is the only who
	  knows how to represent data on console and in memory
    
	3) mv_dcll.hpp : This header files contains all the declaration as well as definitions (as because of templates) of interface functions
			 of 'mv_dcll'

	4) mv_list.hpp : This header files contains all the declaration  of interface functions
			 of 'mv_list'
