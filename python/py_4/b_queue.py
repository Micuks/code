class queue:
    def __init__(self):
        self.items = []

    def len(self):
        return len(self.items)

    def enqueue(self, items):
        for i in items:
            self.items.append(i)

    def dequeue(self, num):
        l = []
        real_num = num if num <= self.len() else self.len()
        while (real_num):
            l.append(self.items.pop(0))
            real_num -= 1
        return l

    def to_string(self):
        return " ".join(str(x) for x in self.items)


class queue_operator:
    def __init__(self):
        self.dequeue_queue = []

    def oper(self, s, op):
        if(op[0] == "out"):
            for i in (s.dequeue(op[1])):
                self.dequeue_queue.append(i)
        elif(op[0] == "in"):
            s.enqueue(op[1:])
        return

    def len(self):
        return len(self.dequeue_queue)

    def to_string(self):
        return " ".join(str(x) for x in self.dequeue_queue)


if __name__ == "__main__":
    q = queue()
    qop = queue_operator()

    _ = input()
    nums = [int(x) for x in input().split()]
    q.enqueue(nums)

    op = [int(x) if x.isnumeric() else x for x in input().split()]
    qop.oper(q, op)

    op = [int(x) if x.isnumeric() else x for x in input().split()]
    qop.oper(q, op)

    if(q.len() == 0):
        print("len = 0")
    else:
        print(f"len = {q.len()}, data = {q.to_string()}")
    if(qop.len() == 0):
        print("len = 0")
    else:
        print(f"len = {qop.len()}, data = {qop.to_string()}")
