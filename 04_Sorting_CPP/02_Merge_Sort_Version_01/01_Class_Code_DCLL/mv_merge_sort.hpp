

#pragma	once

template<typename T_SORT, class Compare>
static void Merge(T_SORT& array, long long first, long long mid, long long last, Compare compare)
{
	// Code
	long long left_size = mid - first + 1;

	long long right_size = last - (mid+1) + 1;

	T_SORT	left = T_SORT(array, first, mid);
	T_SORT	right = T_SORT(array, mid+1, last);

	for( long long le = 0; le < left_size; ++le)
		left[le] = array[first + le];

	for( long long le = 0; le < right_size; ++le)
		right[le] = array[ mid + 1 + le ];

	long long left_index = 0;
	long long right_index = 0;
	long long array_index = first;

	//	Merge the two sub array 
	while( left_index != left_size && right_index != right_size )
	{
		if( compare(left[left_index], right[right_index]) )
		{
			array[ array_index ] = left[left_index];
			left_index++;
		}
		else
		{
			array[array_index] = right[right_index];
			right_index++;
		}
		array_index++;
	}

	//	Case 1 if left is complete and right remains
	while( 	left_index == left_size &&
			right_index != right_size )
	{
		array[array_index] = right[right_index];
		right_index++;
		array_index++;
	}

	//	Case 2 if left remains and right is complete
	while( 	left_index != left_size &&
			right_index == right_size )
	{
		array[array_index] = left[left_index];
		left_index++;
		array_index++;
	}

}

template<typename T_SORT, class Compare>
static void Partition(T_SORT& array, long long first, long long last, Compare compare)
{
	//	Code
	if( first < last )
	{
		long long mid = (last - first) / 2 + first;

		Partition(array, first, mid, compare);
		Partition(array, mid+1, last, compare);
		Merge(array, first, mid, last, compare);
	}
}

template<typename T_SORT, class Compare>
extern	void MergeSort(T_SORT& array, long long size, Compare compare)
{
	//	Code
	Partition(array, 0, size-1, compare);	
}

