def main():
    dict_list = sum(list(input().split() for _ in range(int(input()))), [])
    map_dict = {dict_list[i+1]: dict_list[i]
                for i in range(0, len(dict_list), 2)}
    y = input()
    # result = list(map_dict.get(input(0, "got")))
    result = list()
    while(y != "dog"):
        result.append(map_dict.get(y, "dog"))
        y = input()

    print(*result, sep='\n')
    # or it can be written as print('\n'.join(result))


if __name__ == "__main__":
    main()
