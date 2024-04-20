#!/usr/bin/python3

N = int(input())
S = input()

from itertools import permutations
from math import sqrt

squares = set()

for perm in permutations(S):
    # print(perm)
    x = int("".join(list(perm)))
    # print(x)
    st = int(sqrt(x))
    if (x == (st * st)):
        squares.add(x)

squares = list(squares)
squares.sort()
for i in squares:
    print(i, end=" ")
print()