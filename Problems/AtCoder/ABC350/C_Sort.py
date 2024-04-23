N = int(input())
A = [-1] + [int(i) for i in input().split()]

pos_of = dict()
for i in range(1, N + 1):
    pos_of[A[i]] = i

ops = []

for i in range(1, N + 1):
    # set the ith element to proper value
    if pos_of[i] == i:
        pass
    else:
        # print(len(ops))
        current_val = A[i]
        pos_my_val = pos_of[i]

        pos_of[i] = i
        pos_of[current_val] = pos_my_val

        ops.append((i, pos_my_val))

        A[i] = i
        A[pos_my_val] = current_val

        # for j in A[1:]:
        #     print(j, end=", ")
        # print()

print(len(ops))
for i in ops:
    print(i[0], i[1])