n = int(input())
king, _ = map(int, input().split())
ministers = [tuple(map(int, input().split())) for i in range(n)]

ministers.sort(key = lambda v: (v[0] * v[1]), reverse = False)

max_val = 0
mult = king
for m in ministers:
    max_val = max(mult // m[1], max_val)
    mult *= m[0]

print(max_val)