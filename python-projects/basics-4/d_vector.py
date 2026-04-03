import math


class vector:
    def __init__(self, vec=[]):
        self.vec = vec

    def add(self, u):
        vec = self.vec
        return [vec[i]+u.vec[i] for i in range(0, 3)]

    def sub(self, u):
        vec = self.vec
        return [vec[i]-u.vec[i] for i in range(0, 3)]

    def mul(self, scalar=1):
        vec = self.vec
        return [scalar * x for x in vec]

    def div(self, scalar=1):
        vec = self.vec
        return [x/scalar for x in vec]

    def get_length(self):
        vec = self.vec
        return math.sqrt(vec[0]**2+vec[1]**2+vec[2]**2)


def to_string(l=[]):
    return " ".join(str(x) for x in l)


if __name__ == "__main__":
    v1 = vector([int(x) for x in input().split()])
    v2 = vector([int(x) for x in input().split()])
    op = input()
    if(op == "add"):
        print(to_string(v1.add(v2)))
    elif(op == "sub"):
        print(to_string(v1.sub(v2)))
    elif(op == "mul"):
        print(to_string(v1.mul(int(input()))))
    elif(op == "div"):
        print(to_string([f"{y:.2f}" for y in v1.div(int(input()))]))
    elif(op == "get_length"):
        print(f"{v1.get_length():.2f}")
