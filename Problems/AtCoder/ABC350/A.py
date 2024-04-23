contest = input()[3:].lstrip('0')

if len(contest) == 0:
    print("No")
    exit(0)

contest = int(contest)
# print(contest)

if contest != 316 and contest <= 349:
    print("Yes")
else:
    print("No")