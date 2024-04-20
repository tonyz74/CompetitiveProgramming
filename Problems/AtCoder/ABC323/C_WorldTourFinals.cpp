#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <set>

using namespace std;

int main(void) {
    int N; cin >> N;
    int M; cin >> M;

    vector<int> A(M + 1);
    vector<string> S(N + 1);
    vector<int> scores(N + 1, 0);

    for (int i = 1; i <= M; i++) cin >> A[i];

    for (int i = 1; i <= N; i++) {
        cin >> S[i];

        scores[i] = i;
        for (int k = 1; k <= M; k++) {
            if (S[i][k - 1] == 'o') scores[i] += A[k];
        }
        // printf("scores[%d] is %d\n", i, scores[i]);
    }

    vector<int> dup = scores;
    sort(dup.begin(), dup.end(), greater<int>());

    for (int i = 1; i <= N; i++) {
        // cant try to reach for yourself
        int target = (scores[i] == dup[0]) ? dup[1] : dup[0];
        // printf("for player %d, scores[i] is %d, target is %d\n", i, scores[i], target);

        vector<int> remaining;
        for (int k = 1; k <= M; k++) {
            if (S[i][k - 1] == 'x') remaining.push_back(A[k]);
        }
        sort(remaining.begin(), remaining.end(), greater<int>());

        int cnt = 0;
        int my_current = scores[i];
        auto it = remaining.begin();
        while (my_current < target) {
            my_current += *it;
            cnt++;
            ++it;
        }

        cout << cnt << endl;
    }
}