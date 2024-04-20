#include <iostream>
#include <vector>

using namespace std;

#define MAX_N ((int) 1e5 + 7)

void solve() {
    int N, Q, C;
    cin >> N >> Q >> C;

    vector<int> sum(N + 1);
    vector<int> A(N + 1);
    vector<int> is_pmax(N + 1);
    vector<int> not_pmax(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    // printf("alive\n");

    // position H must be pmax
    // position a + 1 to h - 1 cannot be pmax
    for (int i = 1; i <= Q; i++) {
        int a, h; cin >> a >> h;
        sum[a + 1]++;
        sum[h]--; 
        is_pmax[h] = 1;
    }


    int cnt = 0;
    for (int i = 1; i <= N; i++) {
        cnt += sum[i];
        not_pmax[i] = !(cnt == 0);
    }

    // for (int i = 1; i <= N; i++) {
    //     printf("%d ", not_pmax[i]);
    // }
    // printf("\n");
    // for (int i = 1; i <= N; i++) {
    //     printf("%d ", is_pmax[i]);
    // }
    // printf("\n");

    int mx = A[1];
    int prev = -1;

    for (int i = 1; i <= N; i++) {
        if (A[i] == 0) {
            if (is_pmax[i]) {
                A[i] = mx + 1;
            } else {
                // printf("set %d to 1\n", i);
                A[i] = 1;
            }

            // we can modify it to increase the value if it either
            // has no constraints, or if it has to be a prefix max value,
            // because if we were to modify prev it'd be because everything
            // before prev wasn't large enough, and we're not allowed to make
            // something that's not the prefix max greater than everything before.
            if (!not_pmax[i]) {
                prev = i;
            }
        }

        if (not_pmax[i] && A[i] > mx && prev != -1) {
            A[prev] = A[i];
        }

        mx = max(mx, A[i]);
    }

    mx = A[1];
    bool fail = false;
    for (int i = 1; i <= N; i++) {
        if (not_pmax[i] && A[i] > mx) {
            // printf("failed (t1)\n");
            fail = true; 
        } else if (is_pmax[i] && A[i] <= mx) {
            // printf("failed (t2)\n");
            fail = true;
        } else if (A[i] > C) {
            // printf("failed (t3)\n");
            fail = true;
        }
        mx = max(mx, A[i]);

        if (fail) {
            // printf("failed\n");
            cout << -1 << endl;
            return;
        }
    }

    for (int i = 1; i <= N; i++) {
        cout << A[i];
        if (i != N) {
            cout << " ";
        }
    }
    cout << endl;
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}