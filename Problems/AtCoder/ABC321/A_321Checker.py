x = input()
for (i, ch) in enumerate(x):
    if (i + 1 < len(x)):
        if (ord(x[i + 1])) >= ord(x[i]):
            print("No")
            exit(0)

print("Yes")