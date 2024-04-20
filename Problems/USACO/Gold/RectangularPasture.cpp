#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

struct point {
    i64 x, y;
};

bool cmp_x(const point& lhs, const point& rhs) {
    return lhs.x < rhs.x;
}

bool cmp_y(const point& lhs, const point& rhs) {
    return lhs.y < rhs.y;
}

#define MAX_COORD (2500 + 5)


char state[MAX_COORD][MAX_COORD];
i64 pre[MAX_COORD][MAX_COORD];

int rect_sum(int t, int l, int b, int r) {
    int ans = pre[b][r];

    if (l >= 1) {
        ans -= pre[b][l - 1];
    }

    if (t >= 1) {
        ans -= pre[t - 1][r];
    }

    if (l >= 1 && t >= 1) {
        ans += pre[t - 1][l - 1];
    }

    return ans;
}

int main(void) {
    i64 N; cin >> N;
    vector<point> cows(N + 1);

    for (i64 i = 1; i <= N; i++) {
        cin >> cows[i].x >> cows[i].y;
    }

    std::sort(cows.begin() + 1, cows.end(), cmp_x);
    for (i64 i = 1; i <= N; i++) cows[i].x = i - 1; 
    std::sort(cows.begin() + 1, cows.end(), cmp_y);
    for (i64 j = 1; j <= N; j++) cows[j].y = j - 1;

    for (i64 i = 1; i <= N; i++) {
        // printf("%lld %lld\n", cows[i].x, cows[i].y);
        state[cows[i].y][cows[i].x] = 1;
    }

    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
            pre[i][j] += state[i][j];

            if (i >= 1) {
                pre[i][j] += pre[i - 1][j];
            }

            if (j >= 1) {
                pre[i][j] += pre[i][j - 1];
            }

            if (i >= 1 && j >= 1) {
                pre[i][j] -= pre[i - 1][j - 1];
            }
        }
    }

    i64 answer = 0;
    
    for (int cow1 = 1; cow1 <= N; cow1++) {
        for (int cow2 = cow1 + 1; cow2 <= N; cow2++) {

            int left = min(cows[cow1].x, cows[cow2].x);
            int right = max(cows[cow1].x, cows[cow2].x);
            int top = min(cows[cow1].y, cows[cow2].y);
            int bottom = max(cows[cow1].y, cows[cow2].y);

            i64 above = rect_sum(0, left, top, right);
            i64 below = rect_sum(bottom, left, N, right);

            answer += above * below;

        }
    }

    // individual cows + empty subset
    answer += N + 1;

    cout << answer << endl;
}