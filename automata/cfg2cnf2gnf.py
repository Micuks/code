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

    def add_N(self):
        set_u = self.get_set_N()
        for item in alphabet_N:
            if item not in set_u:
                return item

    def add_S1(self):
        new_N = self.add_N()
        self.grammar.update({new_N: [epsilon]})
        self.grammar[new_N].append(self.start)
        self.start = new_N
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

    def conv2cnf(self):
        set_t_epsilon = alphabet_T.copy()
        set_t_epsilon.add(epsilon)
        dict_new_g = dict()
        for item in self.grammar:
            set_del = set()
            set_add = set()
            for jtem in self.grammar[item]:
                if not self.in_set(jtem, alphabet_N):
                    if not jtem in set_t_epsilon:
                        for ktem in jtem:
                            if ktem in set_t_epsilon:
                                new_fr = self.handle_g(ktem, dict_new_g)
                                new_jtem = jtem.replace(ktem, new_fr, 1)
                                set_del.add(jtem)
                                if new_jtem not in self.grammar[item]:
                                    set_add.add(new_jtem)
            for jtem in set_del:
                self.grammar[item].remove(jtem)
            for jtem in set_add:
                self.grammar[item].append(jtem)
        for item in dict_new_g:
            self.grammar.update({item: dict_new_g[item]})

    def handle_g(self, terminal, dict):
        """
        return N if there is a N which has only one grammar N->ternimal; if hasn't, add new grammer N->terminal, return N.
        """
        for item in self.grammar:
            if self.grammar[item] == terminal:
                return item
        for item in dict:
            if dict[item] == terminal:
                return item
        new_N = self.add_N()
        dict.update({new_N: terminal})
        return new_N

        
    def cfg_to_cnf(self):
        self.delete_epsilon()
        self.delete_useless()
        self.delete_single_generator()
        self.conv2cnf()
        self.is_CNF = True

    def printer(self):
        for item in self.grammar:
            print(item+" -> ", end='')
            for jtem in self.grammar[item]:
                if self.grammar[item][0] == jtem:
                    print(jtem+" ", end='')
                else:
                    print("| "+jtem+" ", end='')
            print("")

def helper():
    print("""
    Convert Context Free Grammer to Chomsky Normal Form
    ---
    Input example:
    4
    S->bA
    S->aB
    A->bAA|aS|a
    B -> aBB | bS | b
    ---
    Tips:
    Only support Upper letters(as Non-Terminal) and Lower letters(as Terminal) now;
    Identify S as start character;
    Identify 0 as epsilon.
    
    """)


def main():
    n = int(input("Input the number of grammars.\n"))
    for i in range(n):
        str = input("Input grammar {}/{}\n".format(i+1, n))
        sstr = str.split('->')
        key = sstr[0].strip()
        vals = sstr[1].split('|')
        vals = [ j.strip() for j in vals ]
        if key in grammars:
            grammars[key].extend(vals)
        else:
            grammars.update({key: vals})
        # grammars[key] = vals
    g = CFG(grammars, 'S')
    g.printer()
    print()
    g.cfg_to_cnf()
    g.printer()

if __name__ == "__main__":
    helper()
    main()
