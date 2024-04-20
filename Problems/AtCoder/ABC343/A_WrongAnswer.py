a, b = [int(i) for i in input().split()]
s = a + b
for i in range(10):
  if i != s:
    print(i)
    exit(0)