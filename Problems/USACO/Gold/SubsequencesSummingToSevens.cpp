#include <iostream>
#include <vector>

using namespace std;

using i64 = long long;

int main(void) {
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);

    i64 N; cin >> N;
    vector<i64> ids(N + 1);
    
    for (i64 i = 1; i <= N; i++) {
        cin >> ids[i];
    }

    vector<i64> first_pos(7, -1);
    vector<i64> last_pos(7, -1);

    vector<i64> presum(N + 1, 0);
    for (i64 i = 0; i <= N; i++) {
        if (i != 0) presum[i] = (presum[i - 1] + ids[i]) % 7;
        
        if (first_pos[presum[i]] == -1) {
            first_pos[presum[i]] = i;
        }

        last_pos[presum[i]] = i;
    }

    // for (i64 i = 1; i <= N; i++) {
    //     printf("%lld ", presum[i]);
    // }
    // cout << endl;

    i64 best = 0;
    for (i64 val = 0; val < 7; val++) {
        i64 first = first_pos[val];
        i64 last = last_pos[val];
        
        i64 start = first + 1;
        i64 end = last;

        if (start > end) {
            continue;
        }

        best = max(best, end - start + 1);
    } 

    cout << best << endl;
}