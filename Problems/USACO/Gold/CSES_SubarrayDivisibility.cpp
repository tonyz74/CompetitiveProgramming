#include <iostream>
#include <map>
#include <vector>

using namespace std;

typedef long long i64;

int main(void) {
    i64 N; cin >> N;
    vector<i64> A(N + 1);
    vector<i64> presum(N + 1, 0);

    map<i64, i64> count;
    count[0] = 1;

    for (i64 i = 1; i <= N; i++) {
        cin >> A[i];

        if (A[i] < 0) {
            A[i] = (A[i] % N) + N;
        }
        presum[i] = (presum[i - 1] + A[i]) % N;

        // presum[j] - presum[i - 1] == 0 
        // -> range [i, j] sum to a multiple of N

        count[presum[i]]++;
    }

    i64 total_n = 0;
    for (auto p: count) {
        if (p.second >= 2) {
            total_n += ((p.second) * (p.second - 1)) / 2;
        }
    }

    cout << total_n << endl;
}