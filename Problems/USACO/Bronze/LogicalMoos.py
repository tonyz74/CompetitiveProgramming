from bisect import bisect_left, bisect_right

N, Q = [int(i) for i in input().split()]

true = True
false = False

expr = input()
words = expr.split()

blocks = [i.strip() for i in expr.split("or")]
values = []
ranges = []

true_blocks = []

block_pfx_has_false = [-1] * N
block_sfx_has_false = [-1] * N

pos = 0
for i, expr in enumerate(blocks):
    end = pos + len(expr.split()) - 1
    ranges.append((pos, end))
    
    x = 1
    for j in range(pos, end + 1):
        if j % 2 == 0:
            x &= words[j] == "true"
            block_pfx_has_false[j] = (x == 0)

    y = 1
    for j in range(end, pos - 1, -1):
        if j % 2 == 0:
            y &= words[j] == "true"
            block_sfx_has_false[j] = (y == 0)

    pos = end + 2
    values.append(x)

    if values[i]:
        true_blocks.append(i)

# print(block_pfx_has_false)

output = []

for query in range(Q):
    inp = input().split()
    L, R, target = [int(inp[0]), int(inp[1]), inp[2] == "true"]
    L -= 1
    R -= 1

    # find group indices
    left_group = bisect_right(ranges, (L, 1e9)) - 1
    right_group = bisect_right(ranges, (R, 1e9)) - 1

    if len(true_blocks) >= 1 and (true_blocks[0] < left_group or true_blocks[-1] > right_group):
        # going to become true no matter what, this is good if our target is true
        # and bad otherwise.

        if target == True:
            output.append('Y') 
        else:
            output.append('N')
    else:
        # making a true depends on this subsequence of blocks only, so if there's a false
        # present anywhere, we cannot make a true.

        has_false = False

        if ranges[left_group][0] < L:
            has_false = has_false or block_pfx_has_false[L - 2]

        if ranges[right_group][1] > R:
            has_false = has_false or block_sfx_has_false[R + 2] 

        # print(has_false)

        if has_false and target == True:
            output.append('N')
        else:
            output.append('Y')

print("".join(output))