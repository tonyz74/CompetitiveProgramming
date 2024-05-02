t = int(input())

for i in range(t):
    s = input()

    ans = 0
    n_ones = 0
    for i in range(len(s)):
        if s[i] == '0':
            if n_ones != 0:
                ans += n_ones + 1
        elif s[i] == '1':
            n_ones += 1
    print(ans)
