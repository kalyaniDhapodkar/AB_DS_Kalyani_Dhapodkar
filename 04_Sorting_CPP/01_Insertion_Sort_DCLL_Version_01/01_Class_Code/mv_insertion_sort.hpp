

/**
 * @file:	mv_insertion_sort.hpp
 * @author:	Kalyani Dhapodkar (dhapodkarkalyani@gmail.com)
 * @brief:	This file holds the definition for sort algorithm i.e generic insertion sort
 * @date:	07/12/2022
 * @version:	1.0
 * 
 * @copyright:	Copyrights(c) 2022
 */

#pragma once

/*
 *  This Insertion Sort is Data Generic BUT Array D.S Specific
 */
template<typename T>
extern void     InsertonSort(T& array, long size)
{
    // Code
    for(long ole = 1; ole < size; ole++)
    {
        T key = array[ole];

        long ile = ole - 1;

        while(ile >= 0 && key < array[le])
        {
            array[ile+1] = array[ile];
            --ile;
        }

        array[ile+1] = key;
    }
}


/**
 *  This Insertion Sort is Data Generic AS WELL AS Data Structure Generic
 */
template<typename T_ITR>
extern void InsertionSort(T_ITR first, T_ITR last)
{
    // Code
    for(T_ITR itr = first + 1; itr != last; ++itr)
    {
        auto key = *itr;

        T_ITR ritr = itr - 1;
        while(ritr != first-1 && key < *ritr)
        {
            (ritr + 1) = *ritr;
            ritr--;
        }

        (ritr+1) = key;
    }

}

/**
 *  This Insertion Sort is Data Generic AS WELL AS Data Structure Generic
 */
template<typename T_ITR, class Compare>
extern void InsertionSort(T_ITR first, T_ITR last, Compare compare)
{
    // Code
    for(T_ITR itr = first + 1; itr != last; itr++)
    {
        auto key = *itr;

        T_ITR ritr = itr - 1;

        while(ritr != first - 1 && compare(key, *ritr))
        {
            (ritr + 1) = *ritr;
            ritr--;
        }

        (ritr + 1) = key;
    }
}