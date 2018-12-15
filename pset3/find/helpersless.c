/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */

bool search(int value, int values[], int n)
{
     if (n>0)
     {
        int i;
        int start=0;
        int end=n-1;
        do {
            i=(start + end) /2;
            if (values[i]==value)
            {
                return true;
            }
            else if (value<values[i])
            {
                end=i-1;
            }
            else if (value>values[i])
            {
                start=i+1;
            }
        }
        while (end-start>=0);
     }
     else 
     {
         return 1;
     }
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    int swap=-1;
    while (swap!=0)
    {
        swap=0;
        for (int j=0; j<n-1; j++)
        {
            if (values[j]>values[j+1])
            {
                int temp= values[j];
                values[j]=values[j+1];
                values[j+1]=temp;
                swap++;
                
            }
        }
    }
    
    return;
}
