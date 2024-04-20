#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;
using i64 = long long;

int main(void) {
    i64 N; cin >> N;
    vector<i64> a(N);
    vector<i64> old_a(N);
    for (int i = 0; i < N; i++) {
        cin >> old_a[i];
        a[i] = old_a[i];
    }

    std::sort(a.begin(), a.end());

    i64 orig_ans = 0;

    vector<i64> ps(N, 0);
    for (i64 i = 0; i < N; i++) {
        i64 before = (i != 0) ? ps[i - 1] : 0;
        ps[i] = before + a[i];
        orig_ans += (i + 1) * a[i];
    }

    i64 Q; cin >> Q;
    for (i64 q = 1; q <= Q; q++) {
        i64 i, to; cin >> i >> to;
        i--;
        
        if (to == old_a[i]) {
            printf("%lld\n", orig_ans);
            continue;
        }

        i64 ans_now = orig_ans;
        i64 orig_pos = std::lower_bound(a.begin(), a.end(), old_a[i]) - a.begin();

        auto first_gt = std::upper_bound(a.begin(), a.end(), to);
        i64 new_pos = -1;
        new_pos = (first_gt - a.begin());

        ans_now -= ps[N - 1] - ps[orig_pos];
        ans_now += ps[N - 1] - ((new_pos - 1 >= 0) ? ps[new_pos - 1] : 0);
        if (new_pos <= orig_pos) {
            ans_now -= old_a[i]; 
        }

        // printf("%lld %lld\n", orig_pos, new_pos);

        ans_now -= (orig_pos + 1) * old_a[i];
        if (to >= old_a[i]) new_pos--;
        ans_now += (new_pos + 1) * to;

        cout << ans_now << endl;
    }
    
}