s = input()
mp = {}
max_val = 0

for char in s:
    if char not in mp:
        mp[char] = 0
    mp[char] += 1
    max_val = max(max_val, mp[char])

best_chr = []
for k in mp.keys():
    if mp[k] == max_val:
        best_chr.append(k)

print(sorted(best_chr)[0])
