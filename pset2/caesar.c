#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int key, i;
string plaintext;
void encrypt()
{
        for (i=0; i<strlen(plaintext); i++)
    {
        if (isalpha(plaintext[i]) && isupper(plaintext[i]))
        {
            int c= (int) plaintext[i];
            c= (c-65+key)%26;
            c+=65;
            plaintext[i]= (char) c;
        }
        else if (isalpha(plaintext[i]) && islower(plaintext[i]))
        {
            int c= (int) plaintext[i];
            c= (c-97+key)%26;
            c+=97;
            plaintext[i]= (char) c;
        }
    }
}
int main(int argc, string argv[])
{
    if (argc==2)
    {
        key=atoi(argv[1]);
        printf("plaintext: ");
        plaintext=get_string();
        if (plaintext!=NULL)
            {
            encrypt();
            printf("ciphertext: %s\n", plaintext);
            }

    }
    else
    {
        printf("Usage: ./caesar k\n");
        return 1;
    }
}