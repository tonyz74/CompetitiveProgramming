#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <functional>

using namespace std;

int main(void) {
    freopen("cereal.in", "r", stdin);
    freopen("cereal.out", "w", stdout);

    int N, M;
    cin >> N >> M;
    vector<int> F(N + 1);
    vector<int> S(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> F[i] >> S[i];
    }

    vector<int> ans(N + 1);
    vector<int> take(M + 1, -1);
    vector<int> cereal_of(N + 1, -1);

    int ans_now = 0;

    // kick cow i out
    function<void(int)> kick = [&] (int i) {
        // printf("kick %d\n", i);

        // nothing happens, was the second choice
        // anyways, no further recursion
        if (cereal_of[i] == S[i]) {
            // printf(" %d now none\n", i);
            cereal_of[S[i]] = -1;
            return;
        }

        // initially was the first choice

        // kick out whoever currently has our second choice
        int has_2nd = take[S[i]];
        // now we have our second choice
        cereal_of[i] = S[i];

        if (has_2nd == -1) {
            ans_now++;
            take[S[i]] = i;
        } else if (take[S[i]] > i) {
            take[S[i]] = i;
            kick(has_2nd);
        }
    };

    for (int i = N; i >= 1; i--) {
        // just take the favorite
        // printf("considering i == %d\n", i);
        if (take[F[i]] == -1) {
            take[F[i]] = i;
            cereal_of[i] = F[i];
            ans_now++;
            // printf("adding here\n");
        } else {
            // somebody before me has taken my favorite
            // i will take it back because i am in front
            int old = take[F[i]];
            take[F[i]] = i;
            cereal_of[i] = F[i];
            kick(old);
        }

        ans[i] = ans_now;
    }

    for (int i = 1; i <= N; i++) {
        printf("%d\n", ans[i]);
    }
}