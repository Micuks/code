def isPrime(a):
    # print(a)
    for i in range(2, a//2+1, 1):
        # print(f'{a} % {i} == {a%i}')
        if a % i == 0:
            return False

    return True


def main():
    N = int(input())
    result = str()
    for i in range(2, N+1, 1):
        if(isPrime(i)):
            result += str(i)+' '

    print(result[:len(result)-1])


if __name__ == '__main__':
    main()
