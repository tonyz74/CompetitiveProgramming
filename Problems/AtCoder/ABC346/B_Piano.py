rep = "wbwbwwbwbwbw" * 500

W, B = [int(i) for i in input().split()]

for i in range(len(rep)):
    n_w = 0
    n_b = 0

    for j in range(i, len(rep)):
        if rep[j] == 'w':
            n_w += 1
        elif rep[j] == 'b':
            n_b += 1

        if (n_w == W and n_b == B):
            print("Yes")
            exit(0)

        elif (n_w > W or n_b > B):
            break

print("No")