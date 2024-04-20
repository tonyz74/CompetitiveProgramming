#include <iostream>
#include <vector>
#include <map>
#include <string>

using namespace std;

void solve() {
    int n, k, m; cin >> n >> k >> m;
    string s; cin >> s; s = "." + s;

    if (n > m) {
        printf("NO\n");
        for (int i = 1; i <= n; i++) {
            printf("a");
        }
        printf("\n");
        return;
    }

    vector<map<char, int> > next(m + 1);
    map<char, int> last_seen;
    for (int chr = 'a'; chr <= 'a' + k - 1; chr++) last_seen[chr] = 1e9;

    for (int i = m; i >= 1; i--) {
        last_seen[s[i]] = i;
        next[i] = last_seen;
    }

    string build;
    int i = 1;
    int fail = false;

    for (int n_pos = 1; n_pos <= n; n_pos++) {
        if (i >= m + 1) {
            fail = true;
            break;
        }

        int choice = 'B';
        int furthest_next = -1;

        for (int next_chr = 'a'; next_chr <= 'a' + k - 1; next_chr++) {
            if (next[i][next_chr] > furthest_next) {
                choice = next_chr;
                furthest_next = next[i][next_chr];
            }
        }

        if (furthest_next == 1e9) {
            fail = true;
            build.push_back(choice);
            break;
        }

        i = furthest_next + 1;
        build.push_back(choice);
        // printf("picked %c\n", choice);
    }

    if (fail) {
        printf("NO\n");
        printf("%s", build.c_str());
        for (int extra = 0; extra < n - (int) build.size(); extra++) {
            printf("a");
        }
        printf("\n");
    } else {
        printf("YES\n");
    }
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}