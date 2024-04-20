#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

int max_equalities(const vector<int>& a, const vector<int>& b) {
    // obj going to pos
    map<int, int> lut_b;

    for (int i = 0; i < (int) b.size(); i++) {
        lut_b[b[i]] = i;
    }

    // spin 0 to K - 1 times
    int K = (int) a.size();
    vector<int> off_benefit((int) a.size());

    for (int idx_in_a = 0; idx_in_a < (int) a.size(); idx_in_a++) {
        int obj = a[idx_in_a];

        if (!lut_b.count(obj)) continue;
        int idx_in_b = lut_b[obj];

        if (idx_in_a >= idx_in_b) {
            off_benefit[idx_in_a - idx_in_b]++;
        } else {
            // take mod
            int move_back = idx_in_b - idx_in_a;
            off_benefit[K - move_back]++;
        }
    }

    int max_benefit = 0;
    for (int bene: off_benefit) {
        max_benefit = max(max_benefit, bene);
    }

    return max_benefit;
}

int main(void) {
    int N, K; cin >> N >> K;

    set<int> a_has;
    set<int> b_has;

    vector<int> a(K);
    for (int i = 0; i < K; i++) {
        cin >> a[i];
        a_has.insert(a[i]);
    }

    vector<int> b(K);
    for (int i = 0; i < K; i++) {
        cin >> b[i];
        b_has.insert(b[i]);
    }

    int max_eq = max_equalities(a, b);
    // printf("max_eq: %d\n", max_eq);

    std::reverse(b.begin(), b.end());
    max_eq = max(max_eq, max_equalities(a, b));

    // printf("max_eq: %d\n", max_eq);

    // for this, count the element simultaneously in both
    int outer_common = 0;
    for (int i = 1; i <= N; i++) {
        if (a_has.count(i) == false && b_has.count(i) == false) {
            outer_common++;
        }
    }

    printf("%d\n", max_eq + outer_common);

}