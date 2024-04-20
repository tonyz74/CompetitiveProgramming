t = int(input())

for tt in range(t):
    a = [int(i) for i in input()]
    b = [int(i) for i in input()]
    l = len(a)
    
    f = False
    for x in range(l):
        if f is True:
            if a[x] > b[x]:
                a[x], b[x] = b[x], a[x]
        
        if a[x] != b[x] and f is False:
            f = True
            
            # ensure a always has bigger one
            if a[x] < b[x]:
                a[x], b[x] = b[x], a[x]
            
    
    print("".join([str(i) for i in a]))
    print("".join([str(i) for i in b]))
    