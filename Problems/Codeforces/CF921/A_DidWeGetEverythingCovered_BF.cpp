#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int ok = true;
string build;
string src;

string fail_str;

void dfs(int i, int mx, int k) {
    if (ok == false) return;

    if (i == mx + 1) {
        int i1 = 0;
        for (int j = 0; j < (int) src.size(); j++) {
            if (build[i1] == src[j]) {
                i1++;
            }
        }

        if (i1 != mx) {
            ok = false;
            fail_str = build;
        }

        return;
    }

    for (int chr = 'a'; chr < 'a' + k; chr++) {
        build.push_back(chr);
        dfs(i + 1, mx, k);
        build.pop_back();
    }
}

void solve() {
    ok = true;
    src.clear();
    build.clear();

    int n, k, m; cin >> n >> k >> m;
    cin >> src;

    dfs(1, n, k);
    if (ok == true) {
        printf("YES\n");
    } else {
        printf("NO\n");
        // printf("%s\n", fail_str.c_str());
    }
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}