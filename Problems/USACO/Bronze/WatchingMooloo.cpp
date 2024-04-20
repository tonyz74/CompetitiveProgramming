#include <iostream>
#include <vector>

using namespace std;

typedef long long i64;

int main(void) {
    i64 N, K; cin >> N >> K;
    vector<i64> days(N + 1);
    for (int i = 0; i < N; i++) cin >> days[i];

    i64 total_price = 0;

    for (int i = 0; i < N; i++) {
        // start off with a subscription for one day
        total_price += K + 1;
        // printf("buying a subscription at day %lld\n", days[i]);
        
        // while it's afforable to keep adding days instead of skipping
        // then buying a new subscription, keep going.
        while (i != N - 1 && days[i + 1] - days[i] < K + 1) {
            total_price += days[i + 1] - days[i];
            // printf("extending subscription for %lld days\n", days[i + 1] - days[i]);
            i++;
        }
    }

    cout << total_price << endl;
}