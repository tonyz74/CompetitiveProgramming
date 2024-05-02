T = int(input())

def to_name(x):
    if x == 0:
        return "Alice"
    else:
        return "Bob"

def flip(v):
    return 'D' if v == 'U' else 'U'

def solve():
    N = int(input())
    S = list(input())

    down = 0
    up = 0

    turn = 0
    while len(S) != 0:
        has_U = False
        pos_U = -1

        for i in range(len(S)):
            if S[i] == 'U':
                has_U = True
                pos_U = i
                break

        if not has_U:
            print('YES' if turn == 1 else 'NO')
            return

        L = len(S)
        before = -1
        after = -1

        if L >= 3:
            before = pos_U - 1
            if before == -1:
                before = L - 1

            after = pos_U + 1
            if after == L:
                after = 0

        res = []
        for i in range(L):
            if i == before or i == after:
                res.append(flip(S[i]))
            elif i != pos_U:
                res.append(S[i])
        S = list(res)

        turn ^= 1

    print('YES' if turn == 1 else 'NO')

for i in range(T):
    solve()
