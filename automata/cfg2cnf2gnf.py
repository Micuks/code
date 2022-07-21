from hashlib import new


grammars = {}
epsilon = '0'
l_alphabet_N = ['A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L',
                'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z']
l_alphabet_T = ['a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l',
                'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z']
alphabet_N = set(l_alphabet_N)
alphabet_T = set(l_alphabet_T)
INF = 26


def replace_idx(text, idx=0, pat=''):
    """
    replace pattern at text[idx]
    """
    return '%s%s%s' % (text[:idx], pat, text[idx+1:])


def comparator_n_idx(a):
    if a[0] in l_alphabet_N:
        return l_alphabet_N.index(a[0])
    else:
        return INF


class CFG:
    def __init__(self, grammar, start):
        self.grammar = grammar
        self.start = start
        self.is_CNF = False
        self.is_GNF = False

    # 消除epsilon生成式
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

        # collect all non-terminal symbols that can arrive epsilon
        set2 = set1.copy()
        # clean epsilon grammars
        k_to_del = set()
        for k, v in self.grammar.items():
            to_del = set()
            for jtem in v:
                if k != self.start and jtem == epsilon:
                    to_del.add(jtem)
                    continue
                for ktem in set2:
                    i = jtem.find(ktem)
                    while i != -1 and len(jtem) > 1:
                        new_n = replace_idx(jtem, i)
                        if new_n not in v:
                            v.append(new_n)
                        i = jtem.find(ktem, i+1)

            for jtem in to_del:
                v.remove(jtem)
            # remove keys whose value list is empty
            if not v:
                k_to_del.add(k)

        # remove keys whose value list is empty
        for key in k_to_del:
            self.grammar.pop(key, 0)

        # add new start symbol if there is a grammar: S->epsilon
        if self.start in set2:
            self.grammar[self.start].remove(epsilon)
            self.add_s1()

    def add_n(self, set=set()):
        """
        add new unused Non-Terminal
        """
        set_n = self.get_set_n()
        set_n = set_n.union(set)
        for i in range(len(l_alphabet_N)):
            if l_alphabet_N[i] not in set_n:
                return l_alphabet_N[i]
        return str()

    def add_s1(self):
        """
        add new start non-terminal
        """
        new_n = self.add_n()
        self.grammar.update({new_n: [epsilon]})
        self.grammar[new_n].append(self.start)
        self.start = new_n
        return

    def get_set_n(self):
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

    def get_set_t(self):
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
        # return set(jtem) <= set
        flag = True
        for c in jtem:
            if c not in set:
                flag = False
                break
        return flag

    # 消除单生成式
    def delete_single_generator(self):
        """
        消除单生成式
        """
        for item in self.grammar:
            set0 = set()
            set1 = set(item)
            while set0 != set1:
                set0 = set1.copy()
                for jtem in set0:
                    if jtem not in self.grammar:
                        continue
                    for ktem in self.grammar[jtem]:
                        if ktem not in set0 and len(ktem) == 1 and ktem in alphabet_N:
                            set1.add(ktem)
            for jtem in set1:
                if jtem not in self.grammar:
                    continue
                if len(self.grammar[jtem]) > 0:
                    self.grammar[item].extend(self.grammar[jtem])
                    self.grammar[item] = list(set(self.grammar[item]))  # 去除重复
            for jtem in set1:
                if jtem in self.grammar[item]:
                    self.grammar[item].remove(jtem)

    # 消除无用符号
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
        useless_n = self.get_set_n() - set_n1
        for item in useless_n:
            self.grammar.pop(item, 0)

        # delete useless symbols in grammars
        for k, v in self.grammar.items():
            s = set()
            for jtem in v:
                for ktem in useless_n:
                    if ktem in jtem:
                        s.add(jtem)
            for jtem in s:
                v.remove(jtem)
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

        use_n = set_1.intersection(self.get_set_n())
        useless_n = self.get_set_n() - use_n

        # delete symbols can't be accessed
        for item in useless_n:
            self.grammar.pop(item, 0)

    # 转换为Chomsky范式
    def conv2cnf(self):
        """
        convert CFG without epsilon, useless symbols and 单生成式 to Chomsky Normal Form
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
                        new_jtem = str(jtem)
                        set_del.add(jtem)
                        for ktem in new_jtem:
                            if ktem in set_t_epsilon:
                                new_fr = self.t_to_n(ktem, dict_new_g)
                                new_jtem = new_jtem.replace(ktem, new_fr, 1)
                        if new_jtem not in v:
                            set_add.add(new_jtem)
            for jtem in set_del:
                v.remove(jtem)
            for jtem in set_add:
                v.append(jtem)
        self.grammar.update(dict_new_g)
        # end of step 1

        # shorten the length of the right end of the generating equations to no more than 2
        dict_new_g = dict()
        for k, v in self.grammar.items():
            q = set()
            set_add = set()
            to_del = set()
            for jtem in v:
                if len(jtem) > 2:
                    q.add(jtem)
                    to_del.add(jtem)
            for jtem in to_del:
                v.remove(jtem)
            while len(q) > 0:
                jtem = q.pop()
                new_jtem = self.shorten_g(jtem, dict_new_g)
                if len(new_jtem) > 2:
                    q.add(new_jtem)
                else:
                    set_add.add(new_jtem)

            for jtem in set_add:
                v.append(jtem)
        for item in dict_new_g:
            self.grammar.update({item: [dict_new_g[item]]})

    def shorten_g(self, jtem, dict):
        """
        single step in Chomsky Normal Form conversion
        """
        to_shorten = jtem[1:3]
        # shorten the length of the right end of the generating equations by one at a time
        for k, v in self.grammar.items():
            if len(v) == 1 and v[0] == to_shorten:
                s = replace_idx(jtem, 1, k)
                s = replace_idx(s, 2)
                return s
        for k, v in dict.items():
            if len(v) == 1 and v[0] == to_shorten:
                s = replace_idx(jtem, 1, k)
                s = replace_idx(s, 2)
                return s
        new_n = self.add_n(set(dict.keys()))
        dict.update({new_n: to_shorten})
        s = replace_idx(jtem, 1, new_n)
        s = replace_idx(s, 2)
        return s

    def t_to_n(self, terminal, dict):
        """
        return N if there is an N which has only one grammar N->terminal; if hasn't, add new grammar N->terminal, return N.
        """
        for k, v in self.grammar.items():
            if len(v) == 1 and v[0] == terminal:
                return k
        for k, v in dict.items():
            if len(v) == 1 and v[0] == terminal:
                return k
        new_n = self.add_n(set(dict.keys()))
        dict.update({new_n: [terminal]})
        return new_n

    # convertion: var->Aw  A->b  =>  var->bw
    def replace_first_var(self, var, A):
        res = []
        for item in self.grammar[var]:
            if item[0] == A:
                tmp = [v + item[1:] for v in self.grammar[A]]
                res.extend(tmp)
            else:
                res.append(item)
        res = list(set(res))
        self.grammar[var] = res

    # 消除直接左递归
    def eliminate_direct_left_recursion(self, var):
        beta = []
        alpha = []

        for item in self.grammar[var]:
            if item[0] == var:
                alpha.append(item[1:])
            else:
                beta.append(item)

        if alpha == []:  # no direct_left_recursion
            return

        new_n = self.add_n()
        beta.extend([v + new_n for v in beta])
        self.grammar[var] = beta
        alpha.extend([v + new_n for v in alpha])
        self.grammar[new_n] = alpha

    # 消除左递归
    def eliminate_left_recursion(self):
        sorted_var = sorted(self.grammar)
        for i in range(len(sorted_var)):
            for j in range(i):
                self.replace_first_var(sorted_var[i], sorted_var[j])
            self.eliminate_direct_left_recursion(sorted_var[i])

    def conv2gnf(self, old_set_n):
        set_t = self.get_set_t()
        sorted_old_keys = sorted(list(old_set_n))
        sorted_old_keys.reverse()

        for k in sorted_old_keys:
            v = self.grammar[k]
            to_add = list()
            to_del = list()
            for item in v:
                if item[0] not in set_t:
                    to_del.append(item)
                    to_add.extend(self.conv2t(item))
            for item in to_del:
                v.remove(item)
            v.extend(to_add)
            v = list(set(v))

    def conv2t(self, item):
        q_item = list(item)
        ret_item = list()
        while(q_item):
            qtop = q_item.pop(0)
            for jtem in self.grammar[qtop[0]]:
                new_item = replace_idx(qtop, 0, jtem)
                if(new_item[0] in alphabet_T):
                    ret_item.append(new_item)
                else:
                    q_item.append(new_item)
        return ret_item

    def cfg_to_cnf(self):
        self.delete_epsilon()
        self.delete_single_generator()
        self.delete_useless()
        self.conv2cnf()
        self.is_CNF = True
    
    def cnf_to_gnf(self):
        old_set_n = self.get_set_n()
        self.eliminate_left_recursion()
        print("after eliminate left recursion")
        self.printer()
        print('---')
        self.conv2gnf(old_set_n)
        self.is_GNF = True

    def printer(self):
        for k, v in self.grammar.items():
            start_flag = '*' if k == self.start else ''
            print(f'{k}{start_flag} -> {" | ".join(v)}')


def helper():
    print("""
    Context Free Grammar Converter

    - Elimite epsilon-generation
    - Elimite single-generation
    - Elimite useless symbols
    - Convert Context Free Grammar to Chomsky Normal Form
    - Elimite left recursion
    - Convert Context Free Grammar to Greibach Normal Form

    ---
    Input example:
    4
    S->bA
    S->aB
    A->bAA|aS|a
    B -> aBB | bS | b
    S
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
        vals = [j.strip() for j in vals]
        if key in grammars:
            grammars[key].extend(vals)
        else:
            grammars.update({key: vals})

    start = input("input the start non-terminal symbol:")
    g = CFG(grammars, start)
    print()
    print("---")
    g.delete_epsilon()
    print("after delete epsilon")
    g.printer()
    print("---")
    g.delete_single_generator()
    print("after delete single generating equations")
    g.printer()
    print("---")
    g.delete_useless()
    print("after delete useless")
    g.printer()
    print('---')
    g.cfg_to_cnf()
    print("after convert to cnf")
    g.printer()
    print('---')
    # g.eliminate_left_recursion()
    # print("after eliminate left recursion")
    # g.printer()
    # print('---')
    print("after convert to gnf")
    g.cnf_to_gnf()
    g.printer()
    print('--- end of output ---')



if __name__ == "__main__":
    helper()
    main()
    # input()
