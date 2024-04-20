#!/usr/bin/python3

# kinda sad, python's just too slow, even with pypy

import sys
sys.setrecursionlimit(2**31 - 1)

H, W = [int(i) for i in input().split()]
grid = [input() for i in range(H)]
groups = [[0 for i in range(W)] for i in range(H)]

def neighbors(row, col):
    keep = []
    adj = [
        (row - 1, col),
        (row + 1, col),
        (row, col - 1),
        (row, col + 1)
    ]
    for near in adj:
        if near[0] < 0 or near[0] >= H:
            continue
        if near[1] < 0 or near[1] >= W:
            continue
        keep.append(near)
    return keep

marker = 1
def flood_fill(row, col):
    groups[row][col] = marker
    for near in neighbors(row, col):
        if groups[near[0]][near[1]] == 0 and grid[near[0]][near[1]] == "#":
            flood_fill(near[0], near[1])

for i in range(H):
    for j in range(W):
        if grid[i][j] == "#" and groups[i][j] == 0:
            flood_fill(i, j)
            marker += 1

base_case = marker - 1
n_cases = 0
together = 0

for i in range(H):
    for j in range(W):
        if grid[i][j] == "#":
            continue

        # we only care about red now. let's set this red to green...
        surrounding_groups = set()
        for nr, nc in neighbors(i, j):
            if groups[nr][nc] != 0:
                surrounding_groups.add(groups[nr][nc])
        # print(surrounding_groups)

        # nobody around
        together += base_case + 1 - len(surrounding_groups)
        n_cases += 1

minv = pow(n_cases, -1, 998244353)
print((minv * together) % 998244353)