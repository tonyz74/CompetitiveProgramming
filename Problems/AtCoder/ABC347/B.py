S = input()

uniq = set()

for L in range(len(S)):
  for R in range(L, len(S)):
    uniq.add(S[L:R+1])
    
print(len(uniq))