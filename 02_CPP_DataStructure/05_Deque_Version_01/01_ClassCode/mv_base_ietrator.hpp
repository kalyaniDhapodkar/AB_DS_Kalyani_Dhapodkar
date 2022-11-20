

#pragma	once

template<typename T>
class 	 mv_base_iterator
{
public:
	mv_base_iterator() {}

	~mv_base_iterator() {}

	mv_base_iterator& operator++();
	mv_base_iterator& operator--();
	mv_base_iterator operator++(int value);
	mv_base_iterator operator--(int value);
	mv_base_iterator operator+(int value);
	mv_base_iterator operator-(int value);
	mv_base_iterator operator+=(int value);
	mv_base_iterator operator-=(int value);
	bool operator==(mv_base_iterator& itr);
	bool operator!=(mv_base_iterator& itr);
	T operator*();
};
