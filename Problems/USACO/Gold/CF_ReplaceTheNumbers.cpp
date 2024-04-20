#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_VAL ((int) (5 * 1e5 + 4))
int dst[MAX_VAL];

vector<pair<int, int> > queries;

int main(void) {
    vector<int> a;

    for (int i = 1; i < MAX_VAL; i++) {
        dst[i] = i; 
    }

    int Q; cin >> Q; 
    for (int i = 1; i <= Q; i++) {
        int ty; cin >> ty;
        if (ty == 1) {
            int x; cin >> x;
            queries.push_back(make_pair(x, 0));
        } else {
            int x, y; cin >> x >> y;
            queries.push_back(make_pair(x, y));
        }
    }

    for (auto rit = queries.rbegin(); rit != queries.rend(); rit++) {
        auto q = *rit;
        if (q.second != 0) {
            dst[q.first] = dst[q.second];
        } else {
            a.push_back(dst[q.first]);
        }
    }

    std::reverse(a.begin(), a.end());
    for (int x: a) cout << x << " ";
    cout << endl;
}