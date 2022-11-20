Directory : 01_ClassCode

Files : 1) MV_Queue.h
	2) MV_Queue.c
	3) MV_Client.c

Description :

	1) MV_Queue.h  : This header files contains all the declaration of interface functions
			 of 'MV_Queue'

	2) MV_Queue.c : This source file contains all the definition of interface functions as 
			well as auxillary functions

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


	3) MV_Client.c : This source file contains interface function calls made by client in order to manage
	   generic data on queue data structure and therefore needs callback function as client is the only who
	  knows how to represent data on console and in memory
    
    
