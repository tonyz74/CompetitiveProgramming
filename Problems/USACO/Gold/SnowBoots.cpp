#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

i64 N, B;
i64 best = 1e18;

struct boot {
    i64 depth;
    i64 step;
};

vector<i64> F;
vector<boot > boots;

bool has_reached[1024][1024];

void dfs(i64 pos, i64 boot) {
    if (has_reached[pos][boot] || pos > N) {
        return;
    }
    has_reached[pos][boot] = true;

    if (pos == N) {
        best = min(best, boot);
    }

    for (i64 i_next = pos + 1; i_next <= pos + boots[boot].step; i_next++) {
        if (F[i_next] <= boots[boot].depth) dfs(i_next, boot);
    }

    for (i64 next_boot = boot + 1; next_boot <= B; next_boot++) {
        if (F[pos] <= boots[next_boot].depth) dfs(pos, next_boot);
    }
}

int main(void) {
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);

    cin >> N >> B;

    F.resize(N + 5);
    boots.resize(N + 5);

    for (i64 i = 1; i <= N; i++) cin >> F[i];

    for (int i = 1; i <= N; i++) {
        cin >> boots[i].depth >> boots[i].step;
    }

    dfs(1, 1);
    cout << best - 1 << endl;
}