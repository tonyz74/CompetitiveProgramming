N = int(input())

def read_grid():
    output = []

    for i in range(N):
        output.append(input())

    return output

A = read_grid()
B = read_grid()

for i in range(N):
    for j in range(N):
        if A[i][j] != B[i][j]:
            print(i + 1, j + 1)
            exit(0)
