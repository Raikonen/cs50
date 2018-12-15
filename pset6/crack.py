import cs50
import sys
import crypt

def main():
    if len(sys.argv) != 2:
        print("Usage: python crack.py hash")
        exit(1)
    test_hash=sys.argv[1]

    alpha_range= list(range(65, 91)) + list(range (97, 123))
    for i in alpha_range:
        pass_hash= crypt.crypt(chr(i), "50")
        if test_hash == pass_hash:
            print("Match, password is {}",format(chr(i)))

    for i in alpha_range:
        for j in alpha_range:
            pass_hash= crypt.crypt(chr(i)+chr(j),"50")
            if test_hash == pass_hash:
                print("Match, password is {}".format(chr(i)+chr(j)))

    for i in alpha_range:
        for j in alpha_range:
            for k in alpha_range:
                pass_hash= crypt.crypt(chr(i)+chr(j)+chr(k),"50")
                if test_hash == pass_hash:
                    print("Match, password is {}".format(chr(i)+chr(j)+chr(k)))

    for i in alpha_range:
        for j in alpha_range:
            for k in alpha_range:
                for l in alpha_range:
                    pass_hash= crypt.crypt(chr(i)+chr(j)+chr(k)+chr(l),"50")
                    if test_hash == pass_hash:
                        print("Match, password is {}".format(chr(i)+chr(j)+chr(k)+chr(l)))

if __name__ == "__main__":
    main()