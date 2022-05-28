grammars = {}
epsilon = '0'
alphabet_N = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'}
alphabet_T = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'}

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
        for item in alphabet_N:
            if item not in set_u:
                self.grammar.update({item: [epsilon]})
                self.grammar[item].append(self.start)
                self.start = item
                return

    def get_set_N(self):
        set_n = set()
        for item in self.grammar:
            if item in alphabet_N:
                set_n.add(item)
            for jtem in self.grammar[item]:
                for ktem in jtem:
                    if ktem in alphabet_N:
                        set_n.add(ktem)
        return set_n

    def get_set_T(self):
        set_t = set()
        for item in self.grammar:
            for jtem in self.grammar[item]:
                for ktem in jtem:
                    if ktem in alphabet_T:
                        set_t.add(ktem)
        return set_t
                    
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
                        if ktem not in set0 and len(ktem) == 1 and ktem in alphabet_N:
                            set1.add(ktem)
            print(set1)
            for jtem in set1:
                self.grammar[item].extend(self.grammar[jtem])
                self.grammar[item] = list(set(self.grammar[item]))
                if jtem in self.grammar[item]:
                    self.grammar[item].remove(jtem)

    def delete_useless(self):
        set_n0 = set()
        set_n1 = set()
        for item in self.grammar:
            for jtem in self.grammar[item]:
                if self.in_set(jtem, alphabet_T):
                    set_n1.add(item)
                    break
                    
        while set_n0 != set_n1:
            set_n0 = set_n1
            for item in self.grammar:
                for jtem in self.grammar[item]:
                    if self.in_set(jtem, alphabet_T.union(set_n0)):
                        set_n1.add(item)
                        break

        useless_N = self.get_set_N() - set_n1
        for item in useless_N:
            self.grammar.pop(item, 0)

        for item in self.grammar:
            s = set()
            for jtem in self.grammar[item]:
                for ktem in useless_N:
                    if ktem in jtem:
                        s.add(jtem)
            for jtem in s:
                self.grammar[item].remove(jtem)
        # print(self.grammar)
        # end of algorithm 1 part

        set_0 = set(self.start)
        set_1 = set(self.start)
        for item in set_0:
            for jtem in self.grammar[item]:
                for ktem in jtem:
                    set_1.add(ktem)
        while set_0 != set_1:
            set_0 = set_1
            for item in set_0:
                if item in alphabet_N:
                    for jtem in self.grammar[item]:
                        for ktem in jtem:
                            set_1.add(ktem)
                    
        use_n = set_1.intersection(self.get_set_N())
        useless_N = self.get_set_N() - use_n
        use_t = set_1.intersection(self.get_set_T())
        useless_T = self.get_set_T() - use_t;

        for item in useless_N:
            self.grammar.pop(item, 0)
        for item in self.grammar:
            for jtem in self.grammar[item]:
                if self.in_set(jtem, useless_N.union(useless_T)):
                    self.grammar[item].remove(jtem)


def main():
    n = int(input("Input the number of grammars.\n"))
    for i in range(n):
        str = input("Input grammar No.{}\n".format(i))
        sstr = str.split('->')
        key = sstr[0].strip()
        vals = sstr[1].split('|')
        vals = [ j.strip() for j in vals ]
        if key in grammars:
            grammars[key].extend(vals)
        else:
            grammars.update({key: vals})
        # grammars[key] = vals
    print(grammars)
    g = CFG(grammars, 'S')
    # g.delete_epsilon()
    # g.delete_single_generator()
    g.delete_useless()
    print(grammars)

if __name__ == "__main__":
    main()
