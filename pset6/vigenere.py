import cs50
import sys

def main():
    if len(sys.argv) != 2:
        print("Usage python vigenere.py key")
        exit(1)

    k=sys.argv[1].upper()

    for i in k:
        if not i.isalpha():
            print("Alphabetic key only")
            exit(2)

    print("plaintext: ", end="")
    plaintext=cs50.get_string()
    if plaintext!= None:
        ciphertext=encrypt(plaintext, k)
        print("ciphertext= {}".format(ciphertext))

def encrypt(text, key):
    counter=0
    ciphertext=""
    for i in text:
        k=ord(key[counter])-65
        if i.isalpha() and i.isupper():
            c= ord(i)
            c= (c-65+k)%26;
            c+=65;
            ciphertext += chr(c)
            counter = (counter+1)%len(key)

        elif i.isalpha() and i.islower():
            c= ord(i)
            c= (c-97+k)%26;
            c+=97;
            i= chr(c)
            ciphertext += chr(c)
            counter = (counter+1)%len(key)

        else:
            ciphertext += i
    return ciphertext

if __name__ == "__main__":
    main()