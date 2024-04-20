for i in range(3, int(5 * 1e6 + 1)):
    if (i % 1e5 == 0):
        print(f'progress: {i / 1e5} cycles done')

    x = 2
    fail = False
    while x * x <= i:
        if i % x == 0:
            fail = True
            break
        x += 1
    
    if not fail:
        # print(f"{i} => {i % 4}")
        if i % 4 == 2:
            print(f"found mistake at {i}")
            exit(-1)