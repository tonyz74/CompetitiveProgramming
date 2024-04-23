T = int(input())

for i in range(T):
    N = int(input())
    A = [int(i) for i in input().split()]

    freq = {}
    for i in A:
        if i not in freq:
            freq[i] = 0

        freq[i] += 1
    
    ans = 0
    for k in freq.keys():
        ans += freq[k] // 3
    
    print(ans)