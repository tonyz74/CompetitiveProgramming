#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;
using i64 = long long;

int main(void) {
    i64 N; cin >> N;

    string S; cin >> S;
    S = "$" + S;

    vector<i64> C(N + 1);
    for (i64 i = 1; i <= N; i++) cin >> C[i];

    vector<i64> one_zero(N + 5);
    vector<i64> zero_one(N + 5);

    for (i64 i = 1; i <= N; i++) {
        one_zero[i] = one_zero[i - 1];
        zero_one[i] = zero_one[i - 1];

        // in 101010, odd must be 1, even must be 0
        if (i % 2 == 1 && S[i] == '0') {
            one_zero[i] += C[i];
        } else if (i % 2 == 0 && S[i] == '1') {
            one_zero[i] += C[i];
        }

        // in 01010101 odd must be 0, even 1
        if (i % 2 == 1 && S[i] == '1') {
            zero_one[i] += C[i];
        } else if (i % 2 == 0 && S[i] == '0') {
            zero_one[i] += C[i];
        }
    }

    for (i64 pad = 1; pad <= 3; pad++) {
        one_zero[N + pad] = one_zero[N];
        zero_one[N + pad] = zero_one[N];
    }

    i64 ans = 1e18;

    auto get_cost = [&] (i64 i, i64 val) {
        i64 accum = 0;
        if ((S[i] - '0') != val) {
            accum += C[i];
        }
        if ((S[i + 1] - '0') != val) {
            accum += C[i + 1];
        }
        return accum;
    };

    // pick i, i + 1 to be equal, the rest all must be not equal
    for (i64 i = 1; i <= N - 1; i++) {
        // consider if they're both ones

        // case 1: T[i] = 0, T[i + 1] = 0
        i64 cost1 = get_cost(i, 0);

        // i - 1 mustve been 1
        if ((i - 1) % 2 == 0) {
            cost1 += zero_one[i - 1];
            cost1 += one_zero[N] - one_zero[i + 1];
        } else {
            cost1 += one_zero[i - 1];
            cost1 += zero_one[N] - zero_one[i + 1];
        }

        // case 2, both 1
        i64 cost2 = get_cost(i, 1);

        // i - 2 must have a 0, even pos
        if ((i - 1) % 2 == 0) {
            cost2 += one_zero[i - 1];
            cost2 += zero_one[N] - zero_one[i + 1];
        } else {
            // printf("odd\n");
            cost2 += zero_one[i - 1];
            cost2 += one_zero[N] - one_zero[i + 1];
        }

        // printf("%lld: %lld, %lld\n", i, cost1, cost2);
        ans = min(ans, min(cost1, cost2));
    }

    cout << ans << endl;
}