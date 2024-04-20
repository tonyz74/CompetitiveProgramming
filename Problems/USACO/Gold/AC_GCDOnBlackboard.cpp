#include <iostream>
#include <vector>

using namespace std;

using i64 = long long;

i64 gcd(i64 a, i64 b) {
    if (a == 0) return b;
    return gcd(b % a, a);
}

int main(void) {
    i64 N; cin >> N;
    vector<i64> blackboard(N + 1);
    vector<i64> pre(N + 1);
    vector<i64> post(N + 2);

    for (i64 i = 1; i <= N; i++) {
        cin >> blackboard[i];
    }

    pre[1] = blackboard[1];
    post[N] = blackboard[N];

    for (i64 i = 2; i <= N; i++) {
        pre[i] = gcd(pre[i - 1], blackboard[i]);
    }
    
    for (i64 i = N - 1; i >= 1; i--) {
        post[i] = gcd(post[i + 1], blackboard[i]);
    }

    i64 best = 1;
    for (i64 i = 1; i <= N; i++) {
        i64 L = -1, R = -1;

        if (i - 1 != 0) L = pre[i - 1];
        if (i + 1 != N + 1) R = post[i + 1];

        if (L == -1) L = R;
        else if (R == -1) R = L;

        best = max(best, gcd(L, R));
    }

    cout << best << endl;
}