from random import randint

N = randint(200, 200)
seen = set()

print(N)

def get_coord():
    return randint(-60, 61)

for i in range(N):
    x = get_coord()
    y = get_coord()

    while (x, y) in seen:
        x = get_coord()
        y = get_coord()

    seen.add((x, y))
    print(x, y)