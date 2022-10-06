def main():
    _ = input()
    sa = set(int(i) for i in input().split())
    _ = input()
    sb = set(int(i) for i in input().split())

    l_a_and_b = sorted(list(sa & sb))
    l_a_or_b = sorted(list(sa | sb))
    l_a_minus_b = sorted(list(sa-sb))

    print(*l_a_and_b, sep=" ")
    print(*l_a_or_b, sep=" ")
    print(*l_a_minus_b, sep=" ")


if __name__ == "__main__":
    main()
