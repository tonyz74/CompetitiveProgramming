#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <set>

using namespace std;

struct number {
    int n_digits = 0;
    int ending_0s = 0;

    bool operator<(const number& rhs) const {
        return make_pair(ending_0s, n_digits) < make_pair(rhs.ending_0s, rhs.n_digits);
    }
};

void solve() {
    int n, m; cin >> n >> m;
    multiset<number> a;

    for (int i = 0; i < n; i++) {
        number num;
        string S; cin >> S;

        for (int j = (int) S.size() - 1; j >= 0; j--) {
            if (S[j] == '0') num.ending_0s++;
            else break;
        }
        num.n_digits = S.size();

        a.insert(num);
    }

    while (a.size() >= 1) {
        {
            // anna does her turn
            auto back = a.end(); back--;
            number to_flip = *back;
            a.erase(back);

            to_flip.n_digits -= to_flip.ending_0s;
            to_flip.ending_0s = 0;
            a.insert(to_flip);
        }

        if (a.size() >= 2) {
            // sasha protects
            number start = *a.begin();
            auto back = a.end(); back--;
            number end = *back;
            a.erase(a.begin());
            a.erase(back);

            number new_num;
            new_num.n_digits = end.n_digits + start.n_digits;
            new_num.ending_0s = start.ending_0s;
            a.insert(new_num);
        } else {
            break;
        }
    }

    if (a.begin()->n_digits >= m + 1) {
        printf("Sasha\n");
    } else {
        printf("Anna\n");
    }
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}