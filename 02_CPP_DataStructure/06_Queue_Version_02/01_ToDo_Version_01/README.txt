

Directory : 06_Queue_Version_02\01_ToDo_Version_01

Files : 1) mv_queue_header.hpp
	2) mv_queue_client.cpp
	3) mv_vector_header.hpp

Description :

	1) mv_queue_header.hpp  : This header files contains all the declaration as well as declarations (as because of templates) of interface functions
			 of 'mv_queue'

	Updation :
		1) error_checking function is modified in a way that is used to handle error by accepting
		argument as pointer to error_handler and also argument as void pointer to parameter of 
		of error handler
			
			error_checking( assert_condition, 
					assert_condition_str,
					filename,
					line_no,
					error_condition,
					err_msg,
					void* (*perror_handler)(void*),
					void* error_handler_params )

		2) Queue here is implemented using vector, on server side queue is using vector to enque, deque, print and destory data in queue.


	3) mv_queue_client.c : This source file contains interface function calls made by client in order to manage
	   generic data on queue data structure and therefore needs callback function as client is the only who
	  knows how to represent data on console and in memory
    
	4) mv_vector_header.hpp  : This header files contains all the declaration as well as declarations (as because of templates) of interface functions of 'mv_vector'
