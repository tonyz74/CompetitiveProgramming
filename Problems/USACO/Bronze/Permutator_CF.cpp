#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

int main(void) {
    i64 N; cin >> N;
    vector<i64> A(N);
    vector<i64> B(N);

    for (int i = 0; i < N; i++) cin >> A[i];
    for (int i = 0; i < N; i++) cin >> B[i];

    vector<i64> pre(N);
    for (i64 i = 0; i < N; i++) {
        i64 k = (N - i) * (i + 1);
        pre[i] = k * A[i];
    }  

    std::sort(pre.begin(), pre.end());
    std::sort(B.begin(), B.end(), greater<i64>());

    i64 total = 0;
    for (int i = 0; i < N; i++) {
        total += pre[i] * B[i];
    }

    cout << total << endl;
}