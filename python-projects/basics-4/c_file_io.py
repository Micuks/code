if __name__ == "__main__":
    context = input()
    mode = input()
    nxt_context = input()
    with open('tmp', 'w') as f:
        f.write(context)

    if mode in ["r", "r+", "a", "a+", "w", "w+", "x", "x+"]:
        try:
            f = open('tmp', mode)
            f.write(nxt_context)
        except BaseException:
            pass
        finally:
            f.close()

    with open('tmp', 'r') as f:
        print(f.read())
