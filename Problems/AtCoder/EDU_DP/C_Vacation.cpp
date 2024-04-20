#include <iostream>
#include <vector>

using namespace std;
using i64 = long long;

i64 dp[(int) 1e5 + 5][3];
i64 gain[(int) 1e5 + 5][3];

int main(void) {
    i64 N; cin >> N;
    
    for (i64 i = 1; i <= N; i++) {
        cin >> gain[i][0] >> gain[i][1] >> gain[i][2];
    }

    dp[1][0] = gain[1][0];
    dp[1][1] = gain[1][1];
    dp[1][2] = gain[1][2];

    for (i64 day = 2; day <= N; day++) {
        // cannot do whatever last picked was
        for (i64 last_pick = 0; last_pick <= 2; last_pick++) {
            for (i64 new_pick = 0; new_pick <= 2; new_pick++) {
                if (new_pick == last_pick) continue;

                dp[day][new_pick] = max(dp[day][new_pick], dp[day - 1][last_pick] + gain[day][new_pick]);
            }
        }
    }

    cout << max(dp[N][0], max(dp[N][1], dp[N][2])) << endl;
}