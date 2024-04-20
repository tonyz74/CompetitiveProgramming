#include <iostream>
#include <vector>
#include <set>
#include <map>

using namespace std;

int main(void) {
    int N, M, L; cin >> N >> M >> L;
    vector<int> a(N + 1);
    vector<int> sides(M + 1);
    
    for (int i = 1; i <= N; i++) cin >> a[i];
    
    multiset<int> valid_sides;
    for (int i = 1; i <= M; i++) {
        cin >> sides[i];
        valid_sides.insert(sides[i]);
    }

    map<int, vector<int> > barred;
    for (int i = 0; i < L; i++) {
        int m, s; cin >> m >> s;
        barred[m].push_back(s);
    }

    int best = 0;

    for (int i = 1; i <= N; i++) {
        for (int side: barred[i]) {
            valid_sides.erase(sides[side]);
        }

        if (valid_sides.size() >= 1) {
            auto back = valid_sides.end(); back--;
            best = max(best, *back + a[i]);
        }

        for (int side: barred[i]) {
            valid_sides.insert(sides[side]);
        }
    }

    cout << best << endl;
}