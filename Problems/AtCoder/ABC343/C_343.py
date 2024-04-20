N = int(input())

def is_palindrome(x: int):
    s = str(x)
    i = 0
    j = len(s) - 1

    while i < j:
        b = s[i]
        e = s[j]
        if b != e:
            return False
        i += 1
        j -= 1

    return True

i = 0
ans = 0
while i ** 3 <= N:
    if is_palindrome(i ** 3):
        ans = i ** 3
    i += 1

print(ans)