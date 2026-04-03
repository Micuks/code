class stack:
    def __init__(self):
        self.items = []

    def len(self):
        return len(self.items)

    def push(self, items):
        for i in items:
            self.items.append(i)

    def pop(self, num):
        l = []
        real_num = num if num <= self.len() else self.len()
        while (real_num):
            l.append(self.items.pop())
            real_num -= 1
        return l

    def to_string(self):
        return " ".join(str(x) for x in self.items)


class stack_operator:
    def __init__(self):
        self.pop_queue = []

    def oper(self, s, op):
        if(op[0] == "pop"):
            for i in (s.pop(op[1])):
                self.pop_queue.append(i)
        elif(op[0] == "push"):
            s.push(op[1:])
        return

    def len(self):
        return len(self.pop_queue)

    def to_string(self):
        return " ".join(str(x) for x in self.pop_queue)


if __name__ == "__main__":
    s = stack()
    sop = stack_operator()

    _ = input()
    nums = [int(x) for x in input().split()]
    s.push(nums)

    op = [int(x) if x.isnumeric() else x for x in input().split()]
    sop.oper(s, op)

    op = [int(x) if x.isnumeric() else x for x in input().split()]
    sop.oper(s, op)

    if(s.len() == 0):
        print("len = 0")
    else:
        print(f"len = {s.len()}, data = {s.to_string()}")
    if(sop.len() == 0):
        print("len = 0")
    else:
        print(f"len = {sop.len()}, data = {sop.to_string()}")
