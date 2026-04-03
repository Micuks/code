def lru_append(item: int, n, load_times, buffer):
    if item in buffer:
        buffer.remove(item)
        buffer.append(item)
    elif len(buffer) == n:
        buffer.pop(0)
        buffer.append(item)
        load_times += 1
    elif len(buffer) < n:
        buffer.append(item)
        load_times += 1
    else:
        raise ValueError("Undefined condition")

    return load_times


def main():
    n, _ = (int(i) for i in input().split())
    access_order = [int(i) for i in input().split()]
    load_times = 0
    buffer = list()
    for item in access_order:
        load_times = lru_append(item, n, load_times, buffer)
    print(load_times)
    print(*sorted(buffer), sep=" ")


if __name__ == "__main__":
    main()
