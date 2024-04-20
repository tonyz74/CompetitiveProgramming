from random import shuffle, choice, randint
from string import ascii_lowercase

letters = list(ascii_lowercase)

shuffle(letters)
letters = letters[:10]
print(100, "".join(letters))

for i in range(100):
    dup = str("".join(letters))
    if (i % 4 == 0):
        pass
    elif i % 4 == 1:
        dup.replace(choice(letters), choice(letters))
    elif i % 4 == 2:
        x = randint(1, 25)
        dup = dup[:x - 1] + dup[x:]
    elif i % 4 == 3:
        x = randint(1, 25)
        dup = dup[:x] + choice(letters) + dup[x:]
    print("".join(dup))
