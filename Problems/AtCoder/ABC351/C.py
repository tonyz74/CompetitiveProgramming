N = int(input())
A = [int(i) for i in input().split()]

vec = []

for elem in A:
    vec.append(elem)

    # append O(1) pop O(1)
    # each time we do this we remove 1
    # N at most
    # amortized O(N)
    while len(vec) > 1 and vec[-1] == vec[-2]:
        vec.pop()
        vec.append(vec.pop() + 1)

# for i in vec:
#     print(i, end=" ")
# print()
print(len(vec))
