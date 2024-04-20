#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

const int MAX_N = 1000 + 5;
const int MOD = 998244353;

long long gcd(long long a, long long b, long long& x, long long& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    long long x1, y1;
    long long d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

long long mod_inv(long long val) {
    long long x, y;
    long long g = gcd(val, MOD, x, y);
    assert(g == 1);
    return (x % MOD + MOD) % MOD;
}

#define RED '.'
#define GREEN '#'

int H, W;
int marker = 1;
int groups[MAX_N][MAX_N];
int grid[MAX_N][MAX_N];

vector<pair<int, int> > get_adj(int row, int col) {
    vector<pair<int, int> > v = {
        { row + 1, col },
        { row - 1, col },
        { row, col + 1 },
        { row, col - 1 }
    };

    vector<pair<int, int> > ret;
    for (auto x: v) {
        if (x.first < 0 || x.first >= H || x.second < 0 || x.second >= W) {
            continue;
        }

        ret.push_back(x);
    }

    return ret;
}

void flood_fill(int row, int col) {
    groups[row][col] = marker;
    auto neighbors = get_adj(row, col);

    for (auto nb: neighbors) {
        int r = nb.first;
        int c = nb.second;

        if (grid[r][c] == GREEN && groups[r][c] == 0) {
            flood_fill(r, c);
        }
    }
}

int main(void) {
    cin >> H >> W;
    for (int i = 0; i < H; i++) {
        string S; cin >> S;
        for (int j = 0; j < W; j++) {
            grid[i][j] = S[j];
        }
    }

    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            if (grid[i][j] == GREEN && groups[i][j] == 0) {
                flood_fill(i, j);
                marker++;
            }
        }
    } 

    int base = marker - 1;
    long long total = 0;
    long long n_cases = 0;

    for (int i = 0; i < H; i++) for (int j = 0; j < W; j++) {
        if (grid[i][j] == GREEN) continue;

        auto neighbors = get_adj(i, j);
        set<int> s;
        n_cases++;

        for (auto nb: neighbors) {
            if (grid[nb.first][nb.second] == GREEN) {
                s.insert(groups[nb.first][nb.second]);
            }
        }

        total += base + 1 - s.size();
        total %= MOD;
    }

    long long inv = mod_inv(n_cases);
    printf("%lld\n", (inv * total) % MOD);
}
