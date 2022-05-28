class State:
    def __init__(self, name, is_start=False, is_final=False):
        if type(name) != str or type(is_start) != bool or type(is_final) != bool:
            raise Exception("Illegal argument type")
        self.name = name
        self.start = is_start
        self.final = is_final
        self.transactions = {}

    def add_transaction(self, terminal, pop, to_state, push):
        if (terminal, pop) in self.transactions:
            self.transactions[(terminal, pop)].append({'to_state': to_state, 'push': push})
        else:
            self.transactions[(terminal, pop)] = [{'to_state': to_state, 'push': push}]

    def is_start(self):
        return self.start

    def is_final(self):
        return self.final

    def itr_transactions(self, terminal, pop):
        for trans in self.transactions[(terminal, pop)]:
            yield trans

    def  has_transaction(self, terminal, pop):
        return (terminal, pop) in self.transactions

    def print_transactions(self):
        def print_to_states(ter, p):
            for trans in self.transactions[(ter, p)]:
                yield '({}, {})'.format(trans['to_state'].name, trans['push'])

        for terminal, pop in self.transactions:
            print('&({}, {}, {}) = {{'.format(self.name, terminal, pop), end='')
            print(', '.join(print_to_states(terminal, pop)), end='')
            print('}')


class CFG:
    def __init__(self, grammar, start):
        self.grammar = grammar
        self.start = start
        self.is_cnf = False
        self.is_gnf = False
        self.first_state = None

    def remove_lambda(self):
        for v in self.grammar:
            if 'λ' in self.grammar[v]:
                self.grammar[v].remove('λ')
                for v1 in self.grammar:
                    for s in self.grammar[v1]:
                        i = s.find(v)
                        while i != -1 and len(s) > 1:
                            add = s.replace(v, '', 1)
                            if add not in self.grammar[v1]:
                                self.grammar[v1].append(add)
                            i = s.find(v, i+1)

    def remove_unit(self):
        for v in self.grammar:
            r = []
            for v1 in self.grammar[v]:
                if len(v1) == 1 and v1.isupper() and v1 not in r:
                    r.append(v1)
                    self.grammar[v].extend(self.grammar[v1])
            self.grammar[v] = list(set(self.grammar[v]))
            for v1 in r:
                self.grammar[v].remove(v1)

    def remove_useless(self):
        use = set()
        for v in self.grammar:
            for s in self.grammar[v]:
                if s.islower():
                    use.add(v)
                    break

        for v in self.grammar:
            if v in use or not self.check_useless(v, use):
                continue
            for v1 in self.grammar:
                if v1 != v and v1 not in use:
                    self.check_useless(v1, use)

        useless = set(grammars.keys()) - use

        # remove useless set form grammar
        for v in useless:
            self.grammar.pop(v, 0)

        for v in self.grammar:
            r = []
            for s in self.grammar[v]:
                for v1 in useless:
                    if v1 in s:
                        r.append(s)
                        break
            for s in r:
                self.grammar[v].remove(s)

        q = [self.start]
        reachable = set(self.start)
        while len(q) > 0:
            v = q.pop(0)
            for s in self.grammar[v]:
                for w in s:
                    if w.isupper() and w not in reachable:
                        if w not in self.grammar:
                            self.grammar[v].remove(s)
                            break
                        reachable.add(w)
                        q.append(w)

        not_reachable = use - reachable
        for v in not_reachable:
            self.grammar.pop(v, 0)

    def check_useless(self, v, use_set):
        for s in self.grammar[v]:
            found = True
            for w in s:
                if w.isupper() and w not in use_set:
                    found = False
                    break
            if found:
                use_set.add(v)
                return True
        return False

    def cfg_to_cnf(self):
        self.remove_lambda()
        self.remove_unit()
        self.remove_useless()
        self.is_cnf = True

    def eliminate_left_recursion(self, v, new_grammars):
        left_recursion = list(filter(lambda a: a[0] == v, self.grammar[v]))
        non_recursion = list(set(self.grammar[v]) - set(left_recursion))
        v_list = []

        new_v = chr(ord(v) + 1 if ord(v) + 1 < 91 else 'A')
        while new_v in self.grammar or new_v in new_grammars:
            new_v = chr(ord(new_v) + 1 if ord(new_v) + 1 < 91 else 'A')

        for s in non_recursion:
            v_list.append(s + new_v)

        new_v_list = []
        for s in left_recursion:
            new_v_list.append(s[1:] + new_v)
        new_v_list.append('λ')

        self.grammar[v] = v_list
        new_grammars[new_v] = new_v_list

    def cnf_to_gnf(self):
        if not self.is_cnf:
            raise Exception("grammar is not in normal form")

        new_grammars = {}
        for v in self.grammar:
            for s in self.grammar[v]:
                if s[0] == v:
                    self.eliminate_left_recursion(v, new_grammars)
                    break

        self.grammar.update(new_grammars)
        self.cfg_to_cnf()

        # T to V
        new_v = 'A'
        while new_v in self.grammar:
            new_v = chr(ord(new_v) + 1)

        new_grammars = {}
        for v in self.grammar:
            for s in self.grammar[v]:
                for w in s[1:]:
                    if w.islower() and w not in new_grammars:
                        new_grammars[w] = new_v
                        new_v = chr(ord(new_v) + 1)
                        while new_v in self.grammar:
                            new_v = chr(ord(new_v) + 1)
            for w in new_grammars:
                for s in self.grammar[v]:
                    self.grammar[v][self.grammar[v].index(s)] = s.replace(w, new_grammars[w])

        for v in new_grammars:
            self.grammar[new_grammars[v]] = [v]

        for v in self.grammar:
            r = set()
            for s in self.grammar[v]:
                if s[0].isupper():
                    r.add(s)
                    for s1 in self.grammar[s[0]]:
                        if s1[0].islower():
                            self.grammar[v].append(s1 + s[1:])
            for s in r:
                self.grammar[v].remove(s)

        self.is_gnf = True

    def create_machine(self):
        if not self.is_gnf:
            raise Exception("grammar is not GNF")

        q0 = State('q0', is_start=True)
        q1 = State('q1')
        qf = State('qf', is_final=True)

        q0.add_transaction('λ', 'z', q1, self.start + 'z')
        print('&(q0, λ, z) = {{(q1, {}z)}}'.format(self.start))

        for v in self.grammar:
            for s in self.grammar[v]:
                q1.add_transaction(s[0], v, q1, s[1:] if len(s) > 1 else 'λ')
        q1.add_transaction('λ', 'z', qf, 'z')
        q1.print_transactions()

        self.first_state = q0

    def execute(self, input_string):
        if self.first_state is None:
            raise Exception("Machine is not created")

        accept = False
        for trans in self.first_state.itr_transactions('λ', 'z'):
            stack = ['z']
            stack.pop(0)
            for a in reversed(trans['push']):
                stack.insert(0, a)
            if self.check_string(input_string, trans['to_state'], stack[:]):
                accept = True
                break

        if not accept:
            print("Rejected")

    def check_string(self, input_string, state, stack):
        if len(stack) == 0:
            return False

        if len(input_string) == 0:
            if state.is_final():
                print("Accepted")
                return True
            for trans in state.itr_transactions('λ', 'z'):
                new_stack = stack[:]
                new_stack.insert(0, trans['push'])
                if self.check_string(input_string, trans['to_state'], new_stack):
                    return True
            return False

        elif not state.has_transaction(input_string[0], stack[0]):
            return False

        pop = stack.pop(0)
        for trans in state.itr_transactions(input_string[0], pop):
            new_stack = stack[:]
            if trans['push'] != 'λ':
                for a in reversed(trans['push']):
                    new_stack.insert(0, a)

            if self.check_string(input_string[1:] if len(input_string) > 1 else '', trans['to_state'], new_stack):
                return True


grammars = {}
varList = set()

n = int(input("Enter number of grammars> "))
for t in range(n):
    g = input()
    x = g.split('->')
    var = x[0].strip()
    to = x[1].split('|')
    to = [s.strip() for s in to]
    grammars[var] = to

c = CFG(grammars, 'S')
c.cfg_to_cnf()
print(grammars)
c.cnf_to_gnf()
c.cfg_to_cnf()
c.create_machine()

s_in = input("Enter string> ")
c.execute(s_in)
