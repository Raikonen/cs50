#define _XOPEN_SOURCE
#include <unistd.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    if (argc!=2)
    {
    printf("Usage: ./crack hash");
    return 1;
    }
    else
    {}
    for (int j=2; j<6; j++)
    {
        char password[j];
        password[j-1]='\0';
        for (int l=0;l<j; l++)
        {
            for (int i=65; i<123; i++)
            {
                password[l]=(char) i;
                string hash=crypt(password, "50");
                printf("%c",password[0]);
                printf("%s\n",hash);
                if (strcmp(hash,argv[1])==0)
                {
                    printf("Correct\n");
                    break;
                }
                else
                {
                    printf("Wrong\n");
                }
            }
        }
    }
}