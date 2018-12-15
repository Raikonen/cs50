import cs50
import sys

def main():
    if len(sys.argv)!=2 or int(sys.argv[1])<=0:
        print("Please use a non-negative integer as a key")
        exit(1)
    k=int(sys.argv[1])
    print("plaintext: ", end="")
    plaintext=cs50.get_string()
    if plaintext!= None:
        ciphertext=encrypt(plaintext, k)
        print("ciphertext= {}".format(ciphertext))



def encrypt(text, key):
    ciphertext=""
    for i in text:
        if i.isalpha() and i.isupper():
            c= ord(i)
            c= (c-65+key)%26;
            c+=65;
            ciphertext += chr(c)

        elif i.isalpha() and i.islower():
            c= ord(i)
            c= (c-97+key)%26;
            c+=97;
            i= chr(c)
            ciphertext += chr(c)

        else:
            ciphertext += i

    return ciphertext

if __name__ == "__main__":
    main()
