def main():
    str_in = input().split()
    a, b = str_in
    a = str(int(a))
    b = str(int(b))
    len_a = len(a)
    len_b = len(b)

    result = str()
    i, j = 0, 0
    while i < len_a or j < len_b:
        if(i < len_a):
            result += a[i]
            i += 1
        if(j < len_b):
            result += b[j]
            j += 1

    print(result)


if __name__ == '__main__':
    main()
