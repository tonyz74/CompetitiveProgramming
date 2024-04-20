#include <iostream>
#include <vector>
#include <string>

using namespace std;
using i64 = long long;

pair<i64, int> dp[3010][3010];

int main(void) {
    string S, T; cin >> S >> T;
    i64 N = S.size(), M = T.size();
    S = "$" + S;
    T = "$" + T;    

    for (i64 i = 1; i <= N; i++) {
        for (i64 j = 1; j <= M; j++) {
        }
    }

    for (i64 i = 1; i <= N; i++) {
        for (i64 j = 1; j <= M; j++) {
            printf("%2lld ", dp[i][j].first);
        }
        printf("\n");
    }

}