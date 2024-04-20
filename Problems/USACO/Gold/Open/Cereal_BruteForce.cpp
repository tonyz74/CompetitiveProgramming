#include <iostream>
#include <set>
#include <map>
#include <vector>

using namespace std;

int main(void) {
    // freopen("cereal.in", "r", stdin);
    // freopen("cereal.out", "w", stdout);

    int N, M;
    cin >> N >> M;
    vector<int> F(N + 1);
    vector<int> S(N + 1);

    for (int i = 1; i <= N; i++) {
        cin >> F[i] >> S[i];
    }

    for (int rm = 0; rm <= N - 1; rm++) {
        int ans = 0;
        int i = rm + 1;
        vector<bool> taken(M + 1, 0);

        for (; i <= N; i++) {
            if (!taken[F[i]]) {
                taken[F[i]] = true;
                ans++;
            } else if (!taken[S[i]]) {
                taken[S[i]] = true;
                ans++;
            }
        }

        cout << ans << endl;
    }
}