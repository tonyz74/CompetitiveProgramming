T = int(input())

def solve():
    N, K = [int(i) for i in input().split()]
    out = []

    msb = 0
    for bit in range(19, 0 - 1, -1):
        if K & (1 << bit):
            msb = bit
            break

    for i in range(0, 19 + 1):
        if i == msb:
            continue

        if (1 << i) <= N:
            out.append(1 << i);

    rem = K - (1 << msb)
    out.append(rem);
    out.append(K + 1)
    out.append(K | (1 << (msb + 1)))

    print(len(out))
    for i in out:
        print(i, end=" ")
    print()

for i in range(T):
    solve()
