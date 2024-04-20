#!/usr/bin/python3

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

def get_n_divisors(pf: dict[int, int]):
    n = 1
    for k in pf:
        n *= pf[k] + 1
        n %= MOD_BASE
    return n

A, B = map(int, input().split())
# B %= MOD_BASE

is_square_num = True
pf = find_prime_factorization(A)

for key in pf:
    pf[key] *= B
    if (pf[key] % 2 != 0):
        is_square_num = False
    pf[key] %= MOD_BASE

val = get_n_divisors(pf)
B_odd = B % 2 == 1
ans = val * B
ans %= MOD_BASE

ONE_HALF = 499122177

if (is_square_num and B_odd):
    ans -= 1

ans *= ONE_HALF
ans %= MOD_BASE

print(ans)