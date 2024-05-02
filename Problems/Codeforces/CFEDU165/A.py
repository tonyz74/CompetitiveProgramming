t = int(input())

def solve():
    n = int(input())
    p = [(int(i) - 1) for i in input().split()]

    for i in range(n):
        if p[p[i]] == i:
            # best friend of my best friend is me, invite them and me
            print(2)
            return
    print(3)

for i in range(t):
    solve()
