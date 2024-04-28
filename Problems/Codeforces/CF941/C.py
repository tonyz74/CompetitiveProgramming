T = int(input())

def turn_name(turn):
    return "Bob" if turn == 1 else "Alice"

def solve():
    N = int(input())

    A = list(set([int(i) for i in input().split()]))
    A.sort()
    A.reverse()

    N = len(A)
    if N == 1:
        print("Alice")
        return

    turn = 0
    accum = 0

    while len(A) >= 2:
        A[-1] += accum

        if A[-1] == 1:
            A.pop()
            accum -= 1
            turn ^= 1
        else:
            break

    if len(A) == 1:
        print(turn_name(turn))
        return

    print(turn_name(turn))

    # for i in range(len(A) - 1):
    #     A[i] += accum

    # print(A, accum)
    # print("idk")

for i in range(T):
    # print("\n\nTC", i)
    solve()
