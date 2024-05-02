T = int(input())

def solve():
    N = int(input())
    A = [int(i) for i in input().split()]
    B = [int(i) for i in input().split()]

    ops = 0

    all_ok = True
    for i in range(N):
        if A[i] > B[i]:
            all_ok = False
            break

    if all_ok:
        print(0)
        return

    for i in range(N, -1, -1):
        # first i, last i
        first_i = A[:i]
        last_i = B[N - i:N]

        ok = True
        for j in range(i):
            if first_i[j] > last_i[j]:
                ok = False
                break

        if ok:
            print(N - i)
            return

for i in range(T):
    solve()
