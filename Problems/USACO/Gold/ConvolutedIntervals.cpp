#include <iostream>
#include <vector>
#include <map>

using namespace std;

typedef long long i64;

int main(void) {
    i64 N, M; cin >> N >> M;

    vector<pair<i64, i64> > intervals(N);
    for (i64 i = 0; i < N; i++) {
        cin >> intervals[i].first >> intervals[i].second;
    }

    vector<i64> events(2 * M + 12, 0); 
    
    map<i64, i64> a_freq, b_freq;
    for (auto inter: intervals) {
        a_freq[inter.first]++;
        b_freq[inter.second]++;
    }

    // btw, they can pick the same interval

    for (auto && [a1, n_a1]: a_freq) {
        for (auto && [a2, n_a2]: a_freq) {
            events[a1 + a2] += (n_a1 * n_a2);
        }
    }

    for (auto && [b1, n_b1]: b_freq) {
        for (auto && [b2, n_b2]: b_freq) {
            events[b1 + b2 + 1] -= (n_b1 * n_b2);
        }
    }

    i64 total = 0;

    // for (i64 ev: events) {
    //     printf("%lld ", ev);
    // }
    // printf("\n");

    for (i64 i = 0; i <= 2 * M; i++) {
        total += events[i];

        cout << total << endl;
    }
}