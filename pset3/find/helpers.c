/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

bool searchRec(int value, int values[], int n, int start, int end);


/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    if (n < 0)
    {
        return false;
    }
    
    sort(values, n);
    
    int start = 0;
    int end = n;
    return  searchRec(value, values, n, start, end);
}

bool searchRec(int value, int values[], int n, int start, int end)
{
        if (start > n || end < start)
        {
            return false;
        }
        int mid = (start + end) / 2;
        
        if(values[mid] == value)
        {
            return true;
        }else if(value > values[mid]) 
        {
            start = mid + 1;
            return searchRec(value, values, n, start, end);
        }else {
            end = mid - 1;
            return searchRec(value, values, n, start, end);
        }
        return false;
    
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    //insertion sort
    for(int i = 1 ; i < n ; i++) 
    {
        int el = values[i];
        
        int j = i;
        
        while(j > 0 && el < values[j - 1])
        {
            values[j] = values[j - 1];
            j--;
        }
        values[j] = el;
    }
    return;
}

