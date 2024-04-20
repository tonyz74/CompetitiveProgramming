#include <iostream>
#include <vector>
#include <map>

using namespace std;

using i64 = long long;

int main(void) {

    int N; cin >> N;
    vector<int> A(N + 1);
    vector<int> B(N + 1);
    vector<int> C(N + 1);

    for (int i = 1; i <= N; i++) cin >> A[i];
    for (int i = 1; i <= N; i++) cin >> B[i];
    for (int i = 1; i <= N; i++) cin >> C[i];

    // value -> num of B[C[i]] = value
    map<i64, i64> cache;

    for (int i = 1; i <= N; i++) {
        i64 c = C[i];
        i64 val = B[c];
        cache[val]++;
    }

    i64 tot = 0;
    for (int i = 1; i <= N; i++) {
        tot += cache[A[i]];
    }

    cout << tot << endl;
}