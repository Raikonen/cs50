import cs50


def main():
    print("O hai!How much change is owed?")
    while(True):
        total=round(cs50.get_float()*100)
        if total<0:
            print("Please input the amount of change in dollars")
        else:
            break

    print("Initial amount is {} cents".format(total))
    counter=0
    for i in [25, 10, 5, 1]:
        if total>=i:
            counter+=round(total/i)
            total=round(total%i)
        print("Current amount left is {} cents".format(total))
        print("Current number of coins is {}".format(counter))


if __name__ == "__main__":
    main()