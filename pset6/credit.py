import cs50

def main():
    while(True):
        print("Number: ", end="")
        card= cs50.get_int()
        if card>0:
            break
        print("Please enter a valid card number")
    checksum=step1(card)
    checksum=step2(checksum,card)
    length=count(card)
    firsttwo=get_firsttwo(card, length)
    if checksum%10==0:
        
        if length==15 and firsttwo==34:
            print("AMEX")
            
        elif length==15 and firsttwo==37:
            print("AMEX")
            
        elif length==16 and firsttwo>50 and firsttwo<56:
            print("MASTERCARD")
            
        elif length==16 and int(firsttwo/10)==4:
            print("VISA")
            
        elif length==13 and int(firsttwo/10)==4:
            print("VISA")
            
    else:
        print("INVALID")

def step1(n):
    checksum=0
    while(n>9):
        digit=int((n/10)%10)
        if digit*2>=10:
            checksum+=int(digit*2%10)
            checksum+=1
        else:
            checksum+=digit*2
        n=n//100
    return checksum

def step2(checksum, n):
    k=0
    while(n>1):
        digit=int(n%10)
        k+=digit
        n=n/100
    checksum+=k
    return checksum

def count(n):
    counter=0
    while(n>10):
        counter+=1
        n=int(n/10)
    counter+=1
    return counter

def get_firsttwo(n, length):
    if length<3:
        print("INVALID")
        exit(1)
    else:
        n=int(n/(10**(length-2)))
    return n


if __name__ == "__main__":
    main()