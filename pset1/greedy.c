#include <cs50.h>
#include <stdio.h>
#include <math.h>

int total, counter;
void count(int coin)
{
    while (total>coin || total==coin)
{
    total=total-coin;
    counter++;
}
}
int main(void){
    
printf("O hai! ");
do{
printf("How much change is owed?\n");
    total=round(get_float()*100);
}
while (total<0);



count(25);
count(10);
count(5);
count(1);

printf("%i\n",counter);
}