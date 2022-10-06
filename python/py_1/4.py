def main():
    n = int(input())
    scores = list(map(int, input().split()))
    sum = 0
    count = 0
    for i in scores:
        sum += i
    average = sum/n
    for i in scores:
        if i >= 60:
            count += 1
    print('average = {:.1f}'.format(average))
    print('count = {}'.format(count))


if __name__ == '__main__':
    main()
