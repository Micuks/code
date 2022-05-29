grammars = {}
start = 'S'
epsilon = '0'
l_alphabet_N = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
l_alphabet_T = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
alphabet_N = set(l_alphabet_N)
alphabet_T = set(l_alphabet_T)

def replace_idx(text, idx=0, pat=''):
    """
    replace pattern at text[idx]
    """
    return '%s%s%s'%(text[:idx], pat, text[idx+1:])

class CFG:
    def __init__(self, grammar, start):
        self.grammar = grammar
        self.start = start
        self.is_CNF = False
        self.is_GNF = False

    def delete_epsilon(self):
        """
        delete epsilon in CFG
        """
        set0 = set(epsilon)
        set1 = set(epsilon)

        # use algorithm 1 to collect non-terminal A if there is a A->epsilon
        for item in self.grammar:
            if epsilon in self.grammar[item]:
                set1.add(item)
        # recursively add all symbols can arrive epsilon
        while set0 != set1:
            set0 = set1.copy()
            for k, v in self.grammar.items():
                for jtem in v:
                    if self.in_set(jtem, set0):
                        set1.add(k)
                        break
        set2 = set()
        # collect all non-terminal symbols that can arrive epsilon
        for item in set1:
            if item in alphabet_N:
                set2.add(item)
        # clean epsilon grammers
        for k, v in self.grammar.items():
            for jtem in v:
                if k != self.start and jtem == epsilon:
                    self.grammar[k].remove(epsilon)
                    continue;
                for ktem in set2:
                    i = jtem.find(ktem)
                    while i != -1 and len(jtem) > 1:
                        new_n = replace_idx(jtem, i)
                        if new_n not in self.grammar[k]:
                            self.grammar[k].append(new_n)
                        i = jtem.find(ktem, i+1)
        # add new start symbol if these is a grammer: S->epsilon 
        if epsilon in self.grammar[self.start]:
            self.grammar[self.start].remove(epsilon)
            self.add_S1()

    def add_N(self, set=set()):
        """
        add new unused Non-Terminal
        """
        set_n = self.get_set_N()
        set_n = set_n.union(set)
        for i in range(len(l_alphabet_N)):
            if l_alphabet_N[i] not in set_n:
                return l_alphabet_N[i]
        return str()

    def add_S1(self):
        """
        add new start non-terminal
        """
        new_N = self.add_N()
        self.grammar.update({new_N: [epsilon]})
        self.grammar[new_N].append(self.start)
        self.start = new_N
        return

    def get_set_N(self):
        """
        get non-terminal set
        """
        set_n = set()
        for k, v in self.grammar.items():
            if k in alphabet_N:
                set_n.add(k)
            for jtem in v:
                for ktem in jtem:
                    if ktem in alphabet_N:
                        set_n.add(ktem)
        return set_n

    def get_set_T(self):
        """
        get terminal set
        """
        set_t = set()
        for k, v in self.grammar.items():
            for jtem in v:
                for ktem in jtem:
                    if ktem in alphabet_T:
                        set_t.add(ktem)
        return set_t
                    
    def in_set(self, jtem, set):
        """
        if all elements in jtem belong with set, return true
        else, return false
        """
        flag = True
        for c in jtem:
            if c not in set:
                flag = False
                break
        return flag

    def delete_single_generator(self):
        """
        delete 单生成式
        """
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
        """
        delete useless non-terminal and terminal symbols
        """
        set_n0 = set()
        set_n1 = set()
        # collect terminal symbols
        for k, v in self.grammar.items():
            for jtem in v:
                if self.in_set(jtem, alphabet_T):
                    set_n1.add(k)
                    break
                    
        # collect non-terminal symbols can arrive terminals
        while set_n0 != set_n1:
            set_n0 = set_n1.copy()
            for k, v in self.grammar.items():
                for jtem in v:
                    if self.in_set(jtem, alphabet_T.union(set_n0)):
                        set_n1.add(k)
                        break

        # delete useless non-terminal symbol grammars
        useless_N = self.get_set_N() - set_n1
        for item in useless_N:
            self.grammar.pop(item, 0)

        # delete useless symbols in grammars
        for k, v in self.grammar.items():
            s = set()
            for jtem in v:
                for ktem in useless_N:
                    if ktem in jtem:
                        s.add(jtem)
            for jtem in s:
                self.grammar[k].remove(jtem)
        # end of algorithm 1 part

        set_0 = set(self.start)
        set_1 = set(self.start)
        # collect all symbols start symbol can arrive directly
        for item in set_0:
            for jtem in self.grammar[item]:
                for ktem in jtem:
                    set_1.add(ktem)
        # collect all symbols start symbol can arrive
        while set_0 != set_1:
            set_0 = set_1.copy()
            for item in set_0:
                if item in alphabet_N:
                    for jtem in self.grammar[item]:
                        for ktem in jtem:
                            set_1.add(ktem)
                    
        use_n = set_1.intersection(self.get_set_N())
        useless_N = self.get_set_N() - use_n
        use_t = set_1.intersection(self.get_set_T())
        useless_T = self.get_set_T() - use_t;

        # delete symbols can't be accessed
        for item in useless_N:
            self.grammar.pop(item, 0)
        for item in self.grammar:
            for jtem in self.grammar[item]:
                if self.in_set(jtem, useless_N.union(useless_T)):
                    self.grammar[item].remove(jtem)

    def conv2cnf(self):
        """
        convert CFG with epsilon, useless symbols and 单生成式 deleted to Chomsky Normal Foam
        """
        set_t_epsilon = alphabet_T.copy()
        set_t_epsilon.add(epsilon)
        dict_new_g = dict()
        # convert terminal symbols appearing at the right end of the generating equations to non-terminal symbols
        for k, v in self.grammar.items():
            set_del = set()
            set_add = set()
            for jtem in v:
                if not self.in_set(jtem, alphabet_N):
                    if not jtem in set_t_epsilon:
                        for ktem in jtem:
                            if ktem in set_t_epsilon:
                                new_fr = self.t_to_n(ktem, dict_new_g)
                                new_jtem = jtem.replace(ktem, new_fr, 1)
                                set_del.add(jtem)
                                if new_jtem not in self.grammar[k]:
                                    set_add.add(new_jtem)
            for jtem in set_del:
                v.remove(jtem)
            for jtem in set_add:
                v.append(jtem)
        for item in dict_new_g:
            self.grammar.update({item: [dict_new_g[item]]})
        # end of step 1

        # shorten the length of the right end of the generating equations to no more than 2
        dict_new_g = dict()
        for k, v in self.grammar.items():
            q = set()
            set_add = set()
            for jtem in v:
                if len(jtem) > 2:
                    q.add(jtem)
                    self.grammar[k].remove(jtem)
            while len(q) > 0:
                jtem = q.pop()
                new_jtem = self.shorten_g(jtem, dict_new_g)
                if len(new_jtem) > 2:
                    q.add(new_jtem)
                else:
                    set_add.add(new_jtem)

            for jtem in set_add:
                self.grammar[k].append(jtem)
        for item in dict_new_g:
            self.grammar.update({item: [dict_new_g[item]]})
    
    def shorten_g(self, jtem, dict):
        """
        single step in Chomsky Normal Form conversion
        """
        to_shorten = jtem[1:3]
        # shorten the length of the right end of the generating equations by one at a time
        for k, v in self.grammar.items():
            if v == to_shorten:
                s = replace_idx(jtem, 1, k)
                s = replace_idx(s, 2)
                return s
        for k, v in dict.items():
            if v == to_shorten:
                s = replace_idx(jtem, 1, k)
                s = replace_idx(s, 2)
                return s
        new_N = self.add_N(set(dict.keys()))
        dict.update({new_N: to_shorten})
        s = replace_idx(jtem, 1, new_N)
        s = replace_idx(s, 2)
        return s


    def t_to_n(self, terminal, dict):
        """
        return N if there is a N which has only one grammar N->ternimal; if hasn't, add new grammer N->terminal, return N.
        """
        for k, v in self.grammar.items():
            if v == terminal:
                return k
        for k, v in dict.items():
            if v == terminal:
                return k
        new_N = self.add_N(set(dict.keys()))
        dict.update({new_N: terminal})
        return new_N
        
    def cfg_to_cnf(self):
        print("---")
        self.delete_epsilon()
        print("after delete epsilon")
        self.printer()
        print("---")
        self.delete_useless()
        print("after delete useless")
        self.printer()
        print("---")
        self.delete_single_generator()
        print("after delete single generating equations")
        self.printer()
        print("---")
        self.conv2cnf()
        self.is_CNF = True

    def printer(self):
        for k, v in self.grammar.items():
            print(k+" -> ", end='')
            for jtem in v:
                if v[0] == jtem:
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
    g = CFG(grammars, start)
    g.cfg_to_cnf()
    g.printer()

if __name__ == "__main__":
    helper()
    main()
