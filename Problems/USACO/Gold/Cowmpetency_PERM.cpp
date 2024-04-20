#include <iostream>
#include <vector>

using namespace std;

struct mem {
    int a;
    int h;
};

int found = false;
int N, Q, C;
vector<int> c;
vector<mem > memory;

void dfs(int i) {
    if (found) return;

    // can check now
    if (i == N + 1) {
        // printf("found seq: ");
        // for (int j = 1; j <= N; j++) {
        //     printf("%d ", c[j]);
        // }
        // printf("\n");

        vector<int> pfx_max(N + 1);
        for (int j = 1; j <= N; j++) {
            pfx_max[j] = max(pfx_max[j - 1], c[j]);
        }

        for (int q = 1; q <= Q; q++) {
            int mx = pfx_max[memory[q].a];
            for (int i = 1; i < memory[q].h; i++) {
                if (c[i] > mx) return;
            }
            if (c[memory[q].h] <= mx) return;
        }

        found = true;
        return;
    }

    if (c[i] != 0) {
        dfs(i + 1);
        if (found) return;
    } else {
        for (int v = 1; v <= C; v++) {
            c[i] = v;
            dfs(i + 1);
            if (found) return;
            c[i] = 0;
        }
    }
}

void solve() {
    found = false;
    c.clear(); memory.clear();
    cin >> N >> Q >> C;

    c.resize(N + 1);
    memory.resize(Q + 1);

    for (int i = 1; i <= N; i++) {
        cin >> c[i];
    }

    for (int i = 1; i <= Q; i++) {
        cin >> memory[i].a >> memory[i].h;
    }

    dfs(1);
    if (!found) {
        printf("-1\n");
        return;
    }

    // printf("answer:\n");
    for (int i = 1; i <= N; i++) {
        printf("%d", c[i]);
        if (i != N) {
            printf(" ");
        }
    }
    printf("\n");
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}