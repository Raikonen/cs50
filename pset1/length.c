#include <cs50.h>
#include <stdio.h>
#include <math.h>
int counter;

void length(long u)
{
    while(u>9)
    {
    u/=10;
    counter++;
    }
    counter+=1;
}
int main(void)
{
long k=get_long_long();
length(k);
printf("%i\n",counter);
int first_two=k/pow(10,counter-2);
printf("%i\n",first_two);
}