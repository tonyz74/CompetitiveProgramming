from pprint import pprint

H, W, K = [int(i) for i in input().split()]

grid = [
]
for i in range(H):
    row = list(input())
    grid.append(row)

def rotate_by_90(in_grid):
    ret = [[0 for j in range(len(in_grid))] for i in range(len(in_grid[0]))]
    for i in range(len(in_grid)):
        for j in range(len(in_grid[0])):
            ret[j][i] = in_grid[i][j]

    return ret

def solve_horizontal(width, height, state):
    dp = [[-1 for j in range(width)] for i in range(height)]
    ans = -1

    for row in range(height):
        # starting from this point to this + K, how many O's?
        mp = {
            'x': 0,
            'o': 0,
            '.': 0
        }

        start_col = 0
        end_col = start_col
        for i in range(min(K, width)):
            mp[state[row][i]] += 1
            end_col += 1
        end_col = K - 1

        # maintain sliding window of length K
        while end_col < width:
            # print(f'at {start_col} => {end_col} with {mp}')
            if mp['x'] == 0:
                dp[row][start_col] = mp['o']
            else:
                dp[row][start_col] = -1
            
            ans = max(dp[row][start_col], ans)
            
            # shuffle forwards by one
            mp[state[row][start_col]] -= 1
            start_col += 1
            end_col += 1

            if end_col == width:
                break
            mp[state[row][end_col]] += 1
    
    return ans

max_val_H = solve_horizontal(W, H, grid)

old_width = W
W = H
H = old_width
grid = rotate_by_90(grid)
max_val_V = solve_horizontal(W, H, grid)

if max(max_val_H, max_val_V) != -1:
    print(K - max(max_val_H, max_val_V))
else:
    print(-1)