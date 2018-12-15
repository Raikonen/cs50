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
    int final_array[n-1];
    int counting_array[65535] ={0};
    int t=0;
    for (int j=0; j<n; j++)
    {
        int r=values[j];
        counting_array[r]++;
    }
    
    for (int k=0; k<65535; k++)
    {
        while (counting_array[k]!=0)
        {
         final_array[t]=k;
         t++;
         counting_array[k]--;
        }
    }
        return;
}
