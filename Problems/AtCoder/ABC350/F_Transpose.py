import sys
sys.setrecursionlimit(1000000000)

S = input()

stk = []
parens = {}

for i, c in enumerate(S):
    if c == "(":
        stk.append(i)
    elif c == ")":
        j = stk.pop()
        parens[j] = i
        parens[i] = j

LEFT_TO_RIGHT = 1
RIGHT_TO_LEFT = -1

def printchr(chr):
    print(chr, end="")

def caseflip(chr):
    if chr.isupper():
        return chr.lower()
    else:
        return chr.upper()

# print l to r, including both endpoints
def dfs(l, r, order = LEFT_TO_RIGHT):
    if r < l:
        return

    if order == LEFT_TO_RIGHT:
        i = l
        while i <= r:
            if S[i] == "(":
                dfs(i + 1, parens[i] - 1, RIGHT_TO_LEFT)
                i = parens[i] + 1
            else:
                printchr(S[i])
                i += 1

    elif order == RIGHT_TO_LEFT:
        i = r
        while i >= l:
            if S[i] == ")":
                dfs(parens[i] + 1, i - 1, LEFT_TO_RIGHT)
                i = parens[i] - 1
            else:
                printchr(caseflip(S[i]))
                i -= 1

dfs(0, len(S) - 1, LEFT_TO_RIGHT)
print()
