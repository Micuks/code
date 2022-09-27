def main():
    n = int(input())
    classes = map(int, input().split())
    classes = list(classes)

    classes.sort()
    result = 0
    for i in range((n+1)//2):
        result += (classes[i]+1) // 2
    
    print(result)


if __name__ == '__main__':
    main()
