Q = int(input())

state = []
for q in range(Q):
    ty, arg = [int(i) for i in input().split()]
    
    if ty == 1:
        state.append(arg)
    else:
        print(state[-arg])
