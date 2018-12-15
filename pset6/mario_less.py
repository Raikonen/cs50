import cs50

def main():
    while(True):
        print("n is ",end="")
        n=cs50.get_int()
        if n>=0 and n<24:
            break
        else:
            print("Please input a non-negative integer no more than 23")
    rows=n
    hashes=2
    while(True):
        for i in range(rows-1):
            print(" ", end="")
        for i in range(hashes):
            print("#", end="")
        print()
        hashes+=1
        rows-=1
        if rows==0:
            break


if __name__ == "__main__":
    main()