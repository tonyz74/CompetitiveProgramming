#include <iostream>
#include <vector>
#include <map>

using namespace std;

using i64 = long long;

int main(void) {
    string S; cin >> S;

    // 202 * 10 mod 2019 == 1
    const int ten_inv = 202;

    vector<i64> inv10s(S.size() + 2, 1);
    inv10s[1] = ten_inv;

    vector<i64> presum(S.size() + 1);

    vector<i64> cache(S.size() + 1);
    map<i64, i64> n_occurences;

    i64 total = 0;

    for (i64 i = 1; i <= (i64) S.size(); i++) {
        presum[i] = (10 * presum[i - 1] + S[i - 1] - '0') % 2019;
        inv10s[i + 1] = (inv10s[i] * ten_inv) % 2019;

        cache[i] = (presum[i - 1] * inv10s[i]) % 2019;

        n_occurences[cache[i]]++;

        i64 target = (presum[i] * inv10s[i + 1]) % 2019;
        total += n_occurences[target];
    }

    cout << total << endl;
}