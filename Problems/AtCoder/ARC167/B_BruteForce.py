#!/usr/bin/python3

import math

MOD_BASE = 998244353

def find_prime_factorization(N: int):
    pf: dict[int, int] = {}

    pf[2] = 0
    while (N % 2 == 0):
        pf[2] += 1
        N //= 2

    if (pf[2] == 0):
        del pf[2]

    i = 3
    while i * i <= N:
        while (N % i == 0):
            prev = pf.get(i)
            pf[i] = prev + 1 if prev is not None else 1
            N //= i
        i += 2

    if (N > 2):
        pf[N] = 1
    
    return pf

def n_divisors(pf: dict[int, int]):
    n = 1
    for k in pf:
        n *= pf[k] + 1
    return n

A, B = map(int, input().split())
C = A ** B

pf = find_prime_factorization(A)

for key in pf:
    pf[key] *= B

n_div = n_divisors(pf)
# print(n_div)

# this changes if perfect square
prod_factors = C ** (n_div / 2)
print(int(math.log(prod_factors, A)) % MOD_BASE)
