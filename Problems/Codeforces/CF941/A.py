T = int(input())

def solve():
    n, k = [int(i) for i in input().split()]
    a = [int(i) for i in input().split()]

    freq_dict = {}
    for i in a:
        if i not in freq_dict:
            freq_dict[i] = 0
        freq_dict[i] += 1

    freq = list(freq_dict.values())
    freq.sort()
    freq.reverse()

    while True:
        worked = False

        front = freq[0]

        if len(freq) == 1:
            freq[0] = min(freq[0], k - 1)
            break

        if freq[0] >= k:
            freq[1] += freq[0] - 1
            freq = freq[1:]
            worked = True

        if not worked:
            break

    print(sum(freq))

for i in range(T):
    solve()
