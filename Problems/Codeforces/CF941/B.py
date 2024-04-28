T = int(input())

# white is 1, black is 0

def show_grid(grid, N, M):
    for i in range(1, N + 1):
        for j in range(1, M + 1):
            print(grid[i][j], end=" ")
        print()

def can_fill_to(grid, N, M, target_color):
    other_color = 0 if target_color == 1 else 1

    for row in [1, N]:
        all = True
        for col in range(1, M + 1):
            if grid[row][col] == target_color:
                all = False

        if all:
            return False

    for col in [1, M]:
        all = True

        for row in range(1, N + 1):
            if grid[row][col] == target_color:
                all = False

        if all:
            return False

    return True

def solve():
    N, M = [int(i) for i in input().split()]
    grid = [[]]
    for i in range(N):
        s = input()
        col = [-1]
        for i in s:
            col.append(int(i == "W"))
        grid.append(col)

    if can_fill_to(grid, N, M, 0) or can_fill_to(grid, N, M, 1):
        print("YES")
    else:
        print("NO")

for i in range(T):
    solve()
