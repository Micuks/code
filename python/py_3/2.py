def is_binary_search_tree(post_order_traversal: list):
    if(len(post_order_traversal) <= 1):
        return True
    root: int = post_order_traversal[-1]
    i = 0
    lchild = []
    rchild = []
    while i <= len(post_order_traversal)-2:
        if post_order_traversal[i] < root:
            lchild.append(post_order_traversal[i])
            i += 1
        else:
            break
    while i <= len(post_order_traversal)-2:
        if post_order_traversal[i] > root:
            rchild.append(post_order_traversal[i])
            i += 1
        else:
            return False
    return is_binary_search_tree(lchild) and is_binary_search_tree(rchild)


def main():
    post_order_traversal = [int(x) for x in input().split()]
    ans = is_binary_search_tree(post_order_traversal)
    print("true" if ans else "false")


if __name__ == "__main__":
    main()
