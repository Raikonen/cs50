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
    hashes=1
    while(True):
        if rows==0:
            break
        for i in range(rows-1):
            print(" ", end="")
        for i in range(hashes):
            print("#", end="")
        print("  ", end="")
        for i in range(hashes):
            print("#", end="")
        print()
        hashes+=1
        rows-=1



if __name__ == "__main__":
    main()