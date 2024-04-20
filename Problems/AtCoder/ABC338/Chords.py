N = int(input())
ranges = []

for i in range(N):
    a, b = sorted([int(i) for i in input().split()])
    ranges.append((a, b))
ranges.sort()

push_events = []
pop_events = []

for i in range(N):
    push_events.append((ranges[i][0], i + 1))
    pop_events.append((ranges[i][1], i + 1))

push_events.sort()
pop_events.sort()

push = 0
pop = 0
stack = []

intersect = False

for i in range(1, 2 * N + 1):
    if push != len(push_events) and push_events[push][0] == i:
        # print(f"pushed {push_events[push][1]} at {push_events[push][0]}")
        stack.append(push_events[push][1])
        push += 1

    if pop != len(pop_events) and pop_events[pop][0] == i:
        top = stack[-1]
        # print(f"popped {top} at {pop_events[pop][0]}")
        if top != pop_events[pop][1]:
            intersect = True
            break
        stack.pop()
        pop += 1

if intersect:
    print("Yes")
else:
    print("No")
