def main():
    _ = input()
    nums = list(map(int, input().split()))
    for i in range(1, len(nums), 1):
        for j in range(0, i, 1):
            if nums[i] < nums[j]:
                nums[i], nums[j] = nums[j], nums[i]
        print(*nums, sep=' ')


if __name__ == "__main__":
    main()
