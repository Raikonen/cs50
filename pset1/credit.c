#include <cs50.h>
#include <stdio.h>
#include <math.h>

int checksum, counter;
long number;
void step1_2(int k);

void step1(long j)
{
while (j>9){
int digit=(j/10)%10;
step1_2(digit);
j=j/100;
}
}
void step1_2(int k)
{
    k=k*2;
   if(k<10)
   {
       checksum+=k;
   }
   else
   {
       checksum+=k%10;
       checksum+=1;
   }
}
void step2(long p)
{
   while (p>0)
{
int digit=p%10;
checksum+=digit;
p=p/100;
}
}

void length(long u)
{
    counter=0;
    while(u>9)
    {
    u/=10;
    counter++;
    }
    counter+=1;
}

int main(void){
    
do{
printf("Number: ");
number=get_long_long();
}
while (number<0);

step1(number);
step2(number);
length(number);
int first_two=number/pow(10,counter-2);
if (checksum%10==0)
{
    if (counter==15 && first_two==34)
    {
        printf("AMEX\n");
    }
    else if (counter==15 && first_two==37)
    {
        printf("AMEX\n");
    }
    else if (counter==16 && 50<first_two && first_two<56)
    {
        printf("MASTERCARD\n");
    }
    else if (counter==16 && first_two/10==4)
    {
        printf("VISA\n");
    }
    else if(counter==13 && first_two/10==4)
    {
        printf("VISA\n");
    }
}
else {
    printf("INVALID\n");
}
}