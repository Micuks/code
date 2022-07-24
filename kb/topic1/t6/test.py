import math


def is_prime(num):
    for i in range(2, int(math.sqrt(num)+1)):
        if(num % i == 0):
            return False
        return True


def main():
    for i in range(1, 9):
        print("case {}:".format(i))
        if(is_prime(i*1000+33)):
            print(i*1000+33)


if __name__ == "__main__":
    main()
