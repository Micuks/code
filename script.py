def find_min(numbers):
    return min(numbers)


def main():
    # 读取输入
    n = int(input())
    input_numbers = list(map(int, input().split()))

    # 查找最小值
    min_value = find_min(input_numbers)

    # 输出结果
    print("min =", min_value)


if __name__ == "__main__":
    main()
