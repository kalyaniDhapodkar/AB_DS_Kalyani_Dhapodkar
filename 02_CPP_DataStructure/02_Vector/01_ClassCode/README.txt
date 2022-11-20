Directory : 01_ClassCode

Files : 1) mv_vector.hpp
	2) mv_client.cpp

Description :
	1) mv_vector.hpp - It contains all definition of interface and auxillary function along
			   with 'Iterator' class for vector

	2) mv_client.cpp - It contains function call made by client

Bugs Report :

	1) Function : Status pushbackv(nr_elements, ...);
	Description : va_arg cannot able to operate on userdefined type when userdefined type
		      as template type parameter as second argument and therefore gives segmentation
		      fault, I found it especially when I created vector of string and invoke pushbackv
		      function on vector of string

	2) Function : Status dataAt(index) & Status popBack(data)
	Description : While returning userdefined data through dataAt(), it may happen that we need to
		      return 'ERROR CODE' in case of index is out of bound so the question is how to 
		      handle or return data of varying type in C++

	3) Function : Iterator()
	Description : In the constructor, I found usual and subtle behaviour of comparsion between index of
		      type 'signed' and nr of elements of type 'unsigned' 

Advice : Avoid using const keyword just before identifier when pointer to some type T is typedef

for example :

	typedef vector_t* p_vector_t;
	Now using, p_vector_t const p_vector will makes p_vector as contant entity while our intention 
	is to create p_vector that is pointing to type constant vector_t

	Therefore, carefully place const before typedef so that semantics remains the same

	for example : 
		const p_vector_t p_vector;
		Here, p_vector is pointer to constant vector, not a constant pointer to vector_t
    
