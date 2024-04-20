#include <iostream>
#include <vector>
#include <set>

using namespace std;

int main(void) {
    int N, M; cin >> N >> M;

    vector<int> totals(N + 1, 0);
    set<pair<int, int> > sorted_totals;

    for (int i = 1; i <= N; i++) {
        sorted_totals.insert(make_pair(0, -i));
    }

    for (int i = 1; i <= M; i++) {
        int x; cin >> x;

        auto fnd = sorted_totals.find(make_pair(totals[x], -x));
        sorted_totals.erase(fnd);
        sorted_totals.insert(make_pair(totals[x] + 1, -x));
        totals[x]++;

        // for (pair<int, int> e: sorted_totals) {
        //     printf("(%d %d) ", e.first, -e.second);
        // }
        // printf("\n");

        auto e = sorted_totals.end();
        e--;
        printf("%d\n", -e->second);
    }
}