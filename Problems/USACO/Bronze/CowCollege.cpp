#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long ll;

int main(void) {
    int N; cin >> N;
    vector<ll> c(N);
    for (int i = 0; i < N; i++) cin >> c[i];

    sort(c.begin(), c.end());

    ll max_money = 0;
    ll tuition = c[0];
    ll best_tuition = 1e9;

    for (int i = 0; i < N; i++) {
        while (c[i] < tuition) { i++; }
        tuition = c[i];

        ll profit = (N - i) * tuition;
        if (profit > max_money) {
            max_money = profit;
            best_tuition = tuition;
        }
    }

    cout << max_money << " " << best_tuition << endl;
}