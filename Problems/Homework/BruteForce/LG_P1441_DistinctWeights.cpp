#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

int n, m;
vector<int> a;

int skip[50];
int used = 0;

int max_reachable = 0;

void dfs(int i) {
    // printf("i %d\n", i);

    if (i == n + 1) {
        if (used != m) return;

        int n_unique = 0;
        unordered_set<int> reachable;
        reachable.insert(0);

        for (int j = 1; j <= n; j++) {
            if (skip[j]) continue;

            vector<int> add;

            for (int x: reachable) {
                add.push_back(x + a[j]);
            }

            for (int x: add) {
                if (!reachable.count(x)) {
                    // printf("new value %d\n", x);
                    n_unique++;
                    reachable.insert(x);
                }
            }
        }

        max_reachable = max(max_reachable, n_unique);

        return;
    }

    if (used <= m - 1) {
        // printf("used 1x\n");
        skip[i] = true;
        used++;
        dfs(i + 1);
        used--;
        skip[i] = false;
    }

    dfs(i + 1);
}

int main(void) {
    cin >> n >> m;
    a.resize(n + 1);

    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    dfs(1);

    cout << max_reachable << endl;
}