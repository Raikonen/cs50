#include <cs50.h>
#include <stdio.h>

int row;
int i;
int main(void)
{
    do{
    printf("Height: ");
    i=get_int();
    }
    while (i>23 || i<0);
    
    int z=i-1;
    int k=2;
   for (int j=0;j<i;j++)
       {
   
    for(int l=0;l<z;l++)
    {
        printf(" ");
    }
    for(int p=0;p<k-1;p++)
    {
        printf("#");
    }
        printf("  ");
      for(int u=0;u<k-1;u++)
    {
        printf("#");
    }
    
    printf("\n");
       
    z--;
    k++;
       }
    
    
    
}