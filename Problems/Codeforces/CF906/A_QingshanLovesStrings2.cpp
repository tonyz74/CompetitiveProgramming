#include <iostream>
#include <vector>
#include <string>

using namespace std;

void print_bitstr(const vector<int>& v) {
    for (int i = 0; i < (int) v.size(); i++) {
        printf("%d", v[i]);
    }
    printf("\n");
}

void solve() {
    int n; cin >> n;
    string S; cin >> S;

    int n_zeroes = 0, n_ones = 0;
    vector<int> a(n);
    for (int i = 0; i < n; i++) {
        a[i] = S[i] - '0';
        if (a[i] == 0) n_zeroes++;
        else n_ones++;
    }

    if (n_zeroes != n_ones) {
        printf("-1\n");
        return;
    }

    int head = 0; int tail = n - 1;

    vector<int> ops;

    int times = 0;

    while (head < tail) {
        if (times >= 300) {
            printf("-1\n");
            return;
        }
        times++;

        // printf("iteration: %d\n", times);
        // print_bitstr(a);
        while (a[head] != a[tail] && head <= tail) {
            head++;
            tail--;
        }

        // printf("now [%d %d]\n", head, tail);

        if (head >= tail) break;

        // now identical
        if (a[head] == 1) {
            // must place at front
            a.insert(a.begin() + head, { 0, 1 });
            // printf("front: ");
            // print_bitstr(a);
            ops.push_back(head);
        } else {
            // must place at back
            a.insert(a.begin() + tail + 1, { 0, 1 });
            // printf("back: ");
            // print_bitstr(a);
            ops.push_back((tail + 1));
        }

        tail += 2;
    }

    printf("%d\n", (int) ops.size());
    for (int x: ops) {
        printf("%d ", x);
    }
    printf("\n");
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}