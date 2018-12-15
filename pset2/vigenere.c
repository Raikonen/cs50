#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

int i, key_counter;
string key, plaintext;

void encrypt(string s)
{
        for (i=0; i<strlen(s); i++)
    {
        if (isalpha(s[i]) && isupper(s[i]))
        {
          
            int c= (int) s[i];
            c= (c-65+(int) key[key_counter]-65)%26;
            c+=65;
            s[i]= (char) c;
            key_counter=(key_counter+1)%strlen(key);
        }
        else if (isalpha(s[i]) && islower(s[i]))
        {
            int c= (int) s[i];
            c= (c-97+((int) key[key_counter])-65)%26;
            c+=97;
            s[i]= (char) c;
            key_counter=(key_counter+1)%strlen(key);
            
        }
    }
}
int main(int argc, string argv[])
{
    if (argc==2)
        {
        key= argv[1];
        for (i=0; i<strlen(key); i++)
            {
            if (isalpha(key[i]))
            {
                key[i]=toupper(key[i]);
            }
            else
            {
                printf("Alphabetic key only\n");
                return 1;
            }
            }
    printf("plaintext: ");
    plaintext=get_string();
        if (plaintext!=NULL)
        {
            key_counter=0;
            encrypt(plaintext);
            printf("ciphertext: %s\n", plaintext);
        }
        }
   
    else
    {
        printf("Usage: ./vigenere k\n");
        return 1;
    }
}