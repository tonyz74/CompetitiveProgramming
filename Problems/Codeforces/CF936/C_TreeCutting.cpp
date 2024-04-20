#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <functional>

using namespace std;
using i64 = long long;

void solve() {
    i64 N, K; cin >> N >> K;
    i64 lo = 1; i64 hi = N - 1;

    vector<vector<i64> > tree(N + 1);
    vector<i64> depths(N + 1);
    vector<i64> parent_of(N + 1);

    for (i64 i = 1; i <= N - 1; i++) {
        i64 a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    function<void(i64, i64, i64)> get_depth = [&] (i64 now, i64 from, i64 d) {
        parent_of[now] = from;
        depths[now] = d;
        for (i64 child: tree[now]) {
            if (child == from) continue;
            get_depth(child, now, d + 1);
        }
    };
    get_depth(1, 0, 1);

    vector<pair<i64, i64> > depth_sorted(1);
    // we want big depths to go in front
    for (i64 i = 1; i <= N; i++) {
        depth_sorted.push_back(make_pair(-depths[i], i));
    }
    std::sort(depth_sorted.begin() + 1, depth_sorted.end());


    auto check = [&] (i64 x) {
        vector<i64> size_of(N + 1, 1);
        i64 rem_cut = K;

        set<pair<i64, i64> > was_cut;

        i64 i = 1;
        while (rem_cut >= 1) {
            // ran out of things to combine, reached top
            if (i > N) {
                return false;
            }

            i64 me = depth_sorted[i].second;
            if (size_of[me] < x) {
                size_of[parent_of[me]] += size_of[me];
            } else if (parent_of[me] != 0) {
                // printf("cut %lld and %lld\n", me, parent_of[me]);
                rem_cut--;
                was_cut.insert(make_pair(me, parent_of[me]));
                was_cut.insert(make_pair(parent_of[me], me));
            }

            i++;
        }

        vector<i64> group_of(N + 1);
        vector<i64> group_size(N + 1);

        function<void(i64, i64, i64)> check_cc = [&] (i64 now, i64 from, i64 grp) {
            // printf("%lld: %lld\n", now, grp);
            group_size[grp]++;
            group_of[now] = grp;

            for (i64 child: tree[now]) {
                if (child == from || was_cut.count(make_pair(now, child))) continue;
                check_cc(child, now, grp);
            }
        };

        i64 marker = 1;
        for (i64 i = 1; i <= N; i++) {
            if (group_of[i] == 0) {
                check_cc(i, 0, marker);
                marker++;
            }

            if (group_size[group_of[i]] < x) {
                return false;
            }
        }

        return true;
    };

    // cout << check(3) << endl;
    // return;

    while (lo < hi) {
        // last true
        i64 mid = (lo + hi + 1) / 2;
        if (check(mid)) {
            lo = mid;
        } else {
            hi = mid - 1;
        }
    }

    cout << lo << endl;
}

int main(void) {
    i64 t; cin >> t;
    while (t--) solve();
}