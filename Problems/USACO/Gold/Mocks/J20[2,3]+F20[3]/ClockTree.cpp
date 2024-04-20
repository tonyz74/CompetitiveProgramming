#include <iostream>
#include <vector>
#include <set>
#include <cassert>

using namespace std;

#define MAX_N (2501)

int N;

struct clock_val {
    int data;

    clock_val() {}

    clock_val(int i): data(i) {
        assert(data <= 12 && data >= 1);
    }

    clock_val operator+=(const int a) {
        assert(a <= 12);
        data -= 1;
        data += a;
        data %= 12;
        data += 1;

        return *this;
    }
};

vector<int> tree[MAX_N];

int curr_root = 0;
vector<clock_val> og_state;
vector<clock_val> state;

// returns value BEFORE equalizing, parent equalizes me

int dfs(int now, int from) {
    for (int child: tree[now]) {
        if (child == from) continue;

        state[child] += 1;

        // I will change by however much it takes to set this child to 12
        int d = dfs(child, now);
        // printf("dfs(%d) => %d\n", child, d);
        state[now] += 12 - d;

    }

    if (from != -1) {
        state[from] += 1;
    }
    return state[now].data;
}

bool check_root(int rt) {
    curr_root = rt;
    state = og_state;
    dfs(rt, -1);

    // pretending we always go right back to the root,
    // so if we're left with 2 nodes but we just skip the last
    // step back, and still are a 12, it's okay, so an extra addition
    // onto root (so root = 1) is fine.
    // printf("state root: %d\n", state[rt].data);
    if (state[rt].data == 1 || state[rt].data == 12) {
        return true;
    }

    return false;
}

int main(void) {
    freopen("clocktree.in", "r", stdin);
    freopen("clocktree.out", "w", stdout);

    cin >> N;
    og_state.resize(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> og_state[i].data;
    } 

    for (int i = 1; i <= N - 1; i++) {
        int s, e; cin >> s >> e;
        tree[s].push_back(e);
        tree[e].push_back(s);
    }

    int tot = 0;
    for (int root = 1; root <= N; root++) {
        tot += check_root(root);
    }
    printf("%d\n", tot);
}