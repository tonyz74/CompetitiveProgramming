#include <iostream>
#include <vector>

using i64 = long long;

using namespace std;

using p64 = pair<i64, i64>;

i64 calc(i64 N, const vector<p64> &V) {
    i64 ans = 0;
    for (i64 i = 1; i <= N - 1; i++) {
        for (i64 j = i + 1; j <= N; j++) {
            ans += max(abs(V[j].first - V[i].first), abs(V[j].second - V[i].second));
        }
    }
    return ans;
}

int main(void) {
    i64 N; cin >> N;
    vector<p64> P(N + 1);

    i64 O = 0;
    vector<p64> odd_par(1);

    i64 E = 0;
    vector<p64> even_par(1);

    for (i64 i = 1; i <= N; i++) {
        cin >> P[i].first >> P[i].second;

        i64 s = P[i].first + P[i].second;
        if (s % 2 == 0) {
            E++;
            even_par.push_back(P[i]);
        } else {
            O++;
            odd_par.push_back(P[i]);
        }
    }

    i64 ans = 0;
    ans += calc(O, odd_par);
    ans += calc(E, even_par);

    cout << ans << endl;
}
