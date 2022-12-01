
Directory : 01_C_Datastructure\04_Queue_Version_04\01_TODO_Version_01
			
Files :
		1) mv_queue_header.h
		2) mv_queue_server.c
		3) mv_queue_client.c
		4) mv_dcll_server.h
		5) mv_dcll_header.c

Description :

1) mv_queue_header.h  : This header files contains all the declaration of interface functions
			 			 of 'mv_queue'

2) mv_queue_server.c : This Source file contains all the function definitions declared in mv_queue.h
	
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

					2) Queue here is implemented using Doubly Circular Linked List, on server 
						side queue is using Doubly Circular Linked List to enque, deque, print and destory 
						data in queue.

3) mv_queue_client.c : This source file contains interface function calls made 
						by client in order to manage generic data on queueue data structure and 
						therefore needs callback function as client is the only who
	  					knows how to represent data on console and in memory
    
4) mv_dcll_header.h  : This header files contains all the declaration of interface functions of 'mv_dcll'

5) mv_dcll_server.c : This Source file contains all the function definitions declared in mv_dcll.h

