Directory : 05_Deque_Version_01/01_ClassCode

Files : 1) MV_Deque.h
	2) MV_Deque.c
	3) MV_Client.c

Description :

	1) MV_Deque.h : This header files contains all declaration of interface routines along with Macros and typedef 
			definitions that is require in the context of deque

	2) MV_Deque.c : This server file of 'MV_Deque' contains definition of all interface routines along with definitions
			of auxillary functions

	Updations :
		1) New function is added i.e check_deque_conditions that takes pointer to deque and ERROR CODES
		check_deque_conditions function is specifically designed to make error handling code more redundant
		by simply providing ERROR CODES
	
	3) MV_Client.c : This client file contains interface function calls made by client to be operated
			 on data that is defined by client itself and therefore there is need of callback functions
			 as client is only one who knows how to represent its data on console as well as in memory
       
       
