grammars = {}
epsilon = '0'
alphabet = ('A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z')

def replace_idx(text, idx=0, pat=''):
    return '%s%s%s'%(text[:idx], pat, text[idx+1:])

class CFG:
    def __init__(self, grammar, start):
        self.grammar = grammar
        self.start = start
        self.is_CNF = False
        self.is_GNF = False

    def delete_epsilon(self):
        set0 = set(epsilon)
        set1 = set(epsilon)
        if epsilon in self.grammar[self.start]:
            self.add_S1()
        for item in self.grammar:
            if epsilon in self.grammar[item]:
                set1.add(item)
        while set0 != set1:
            set0 = set1
            for item in self.grammar:
                for jtem in self.grammar[item]:
                    if self.in_set(jtem, set0):
                        set1.add(item)
                        break
        set2 = set()
        for item in set1:
            if item.isupper():
                set2.add(item)
        for item in self.grammar:
            for jtem in self.grammar[item]:
                if item != self.start and jtem == epsilon:
                    self.grammar[item].remove(epsilon)
                    continue;
                for ktem in set2:
                    i = jtem.find(ktem)
                    while i != -1 and len(jtem) > 1:
                        new_n = replace_idx(jtem, i)
                        if new_n not in self.grammar[item]:
                            self.grammar[item].append(new_n)
                        i = jtem.find(ktem, i+1)

    def add_S1(self):
        set_u = self.get_set_N()
        for item in alphabet:
            if item not in set_u:
                self.grammar.update({item: [epsilon]})
                self.grammar[item].append(self.start)
                self.start = item
                return

    def get_set_N(self):
        set_n = set()
        for item in self.grammar:
            for jtem in self.grammar[item]:
                for ktem in jtem:
                    if ktem in alphabet:
                        set_n.add(ktem)
        return set_n
                    
    def in_set(self, jtem, set):
        flag = True
        for c in jtem:
            if c not in set:
                flag = False
                break
        return flag

    def delete_single_generator(self):
        for item in self.grammar:
            set0 = set()
            set1 = set(item)
            while set0 != set1:
                set0 = set1.copy()
                for jtem in set0:
                    for ktem in self.grammar[jtem]:
                        if ktem not in set0 and len(ktem) == 1 and ktem in alphabet:
                            set1.add(ktem)
            print(set1)
            for jtem in set1:
                self.grammar[item].extend(self.grammar[jtem])
                self.grammar[item] = list(set(self.grammar[item]))
                if jtem in self.grammar[item]:
                    self.grammar[item].remove(jtem)


def main():
    n = int(input("Input the number of grammars.\n"))
    for i in range(n):
        str = input("Input grammar No.{}\n".format(i))
        sstr = str.split('->')
        key = sstr[0].strip()
        vals = sstr[1].split('|')
        vals = [ j.strip() for j in vals ]
        grammars[key] = vals
    print(grammars)
    g = CFG(grammars, 'S')
    g.delete_epsilon()
    g.delete_single_generator()
    print(grammars)

if __name__ == "__main__":
    main()
