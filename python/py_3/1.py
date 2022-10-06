def mat_add(l_ma: list, l_mb: list):
    l_mc = []
    for i in range(len(l_ma)):
        def f(l): return [int(x) for x in l[i].split(',')]
        ua, ub = f(l_ma), f(l_mb)
        l_mc.append([ua[j]+ub[j] for j in range(len(ua))])
    return l_mc.__str__().replace(' ', '')


def main():
    _ = input()
    def f(sin): return sin[2:-2].split("],[")
    print(mat_add(f(input()), f(input())))


if __name__ == "__main__":
    main()
