#include <iostream>
#include <vector>
#include <set>

using namespace std;

set<int> results;

using vi = vector<int>;

void erase_first(vi &x, int tgt) {
    int n = 0;
    while (n != (int) x.size() && x[n] != tgt) n++;
    if (n != (int) x.size()) x.erase(x.begin() + n);
}

void search(int day, vi b1, vi b2, int b1_sum, int b2_sum) {
    if (day == 6) { results.insert(b1_sum); return; }

    if (day % 2 == 0) {
        for (auto it = b1.begin(); it != b1.end(); it++) {
            // even numbered days take one from the first barn
            vi new_b1 = b1;
            erase_first(new_b1, *it);

            vi new_b2 = b2;
            new_b2.push_back(*it);

            search(day + 1, new_b1, new_b2, b1_sum - *it, b2_sum + *it);
        }
    } else {
        for (auto it = b2.begin(); it != b2.end(); it++) {
            // even numbered days take one from the first barn
            vi new_b2 = b2;
            erase_first(new_b2, *it);

            vi new_b1 = b1;
            new_b1.push_back(*it);

            search(day + 1, new_b1, new_b2, b1_sum + *it, b2_sum - *it);
        }
    }
}

int main(void) {
    freopen("backforth.in", "r", stdin);
    freopen("backforth.out", "w", stdout);

    vi b1; b1.resize(10);
    vi b2; b2.resize(10);

    for (int i = 0; i < 10; i++) cin >> b1[i];
    for (int i = 0; i < 10; i++) cin >> b2[i];

    search(2, b1, b2, 1000, 1000);
    cout << results.size() << endl;
}