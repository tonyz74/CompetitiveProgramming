#include <iostream>
#include <vector>
#include <map>

using namespace std;
using i64 = long long;

int main(void) {
    int N; cin >> N;
    map<i64, int> occ;
    map<int, i64> score_of;

    occ[0] = N;
    for (int i = 1; i <= N; i++) {
        score_of[i] = 0;
    }

    int T; cin >> T;
    for (int i = 1; i <= T; i++) {
        int a; cin >> a;
        i64 b; cin >> b;

        i64 old_score = score_of[a];
        occ[old_score]--;
        if (occ[old_score] == 0) occ.erase(old_score);

        occ[old_score + b]++;
        score_of[a] = old_score + b;

        printf("%d\n", (int) occ.size());
    }
}