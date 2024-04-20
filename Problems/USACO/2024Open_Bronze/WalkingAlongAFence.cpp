#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <cassert>

using namespace std;

#define int long long

using p = pair<int, int>;

int N, P;
map<p, int> post_to_i;
vector<p> posts;
set<p> has_conn;
vector<pair<p, p> > cows;
map<int, set<p> > at_x;
map<int, set<p> > at_y;

p find_current_pos(p point) {
    if (post_to_i.count(point)) {
        return make_pair(post_to_i[point], post_to_i[point]);
    }

    if (at_x[point.first].empty() == false) {
        auto greater_y = at_x[point.first].upper_bound(make_pair(point.second, 0));
        if (greater_y != at_x[point.first].begin() && greater_y != at_x[point.first].end()) {
            auto smaller_y = greater_y; smaller_y--;
            int above_idx = greater_y->second;
            int below_idx = smaller_y->second;

            if (has_conn.count(make_pair(above_idx, below_idx))) {
                return make_pair(above_idx, below_idx);
            }
        }
    }

    if (at_y[point.second].empty() == false) {
        // first one gteq
        auto greater_x = at_y[point.second].upper_bound(make_pair(point.first, 0));

        if (greater_x != at_y[point.second].begin() && greater_x != at_y[point.second].end()) {
            auto lesser_x = greater_x; lesser_x--;
            int rhs_idx = greater_x->second;
            int lhs_idx = lesser_x->second;

            if (has_conn.count(make_pair(rhs_idx, lhs_idx))) {
                return make_pair(rhs_idx, lhs_idx);
            }
        }
    }

    assert(false);
}

int pt_distance(p a, p b) {
    return abs(b.second - a.second) + abs(b.first - a.first);
}

signed main(void) {
    cin >> N >> P;
    cows.resize(N + 1);
    posts.resize(P + 1);

    for (int i = 1; i <= P; i++) {
        scanf("%lld %lld", &posts[i].first, &posts[i].second);
        at_x[posts[i].first].emplace(posts[i].second, i);
        at_y[posts[i].second].emplace(posts[i].first, i);
        post_to_i[posts[i]] = i;

        int next = i + 1;
        if (i == P) next = 1;

        has_conn.emplace(next, i);
        has_conn.emplace(i, next);
    }

    // 1 2 3 4
    vector<int> pfx(P + 2);
    {
        int cx = posts[1].first;
        int cy = posts[1].second;

        for (int i = 2; i <= P; i++) {
            pfx[i] = pfx[i - 1] + abs(cy - posts[i].second) + abs(cx - posts[i].first);
            cx = posts[i].first;
            cy = posts[i].second;
        }
    }

    auto calc_answer = [&] (p start_pos, p end_pos, p start_fences, p end_fences) {
        int start_big = max(start_fences.first, start_fences.second);
        int start_small = min(start_fences.first, start_fences.second);
        int end_small = min(end_fences.first, end_fences.second);
        int end_big = max(end_fences.first, end_fences.second);

        int increasing_ans = 0;

        // they can't be both on the bad line at the same time, we have
        // something that returns directly when same line

        if (start_big == P && start_small == 1) {
            increasing_ans += pt_distance(start_pos, posts[1]);
            increasing_ans += pfx[end_small];
            increasing_ans += pt_distance(end_pos, posts[end_small]);

        } else {

            if (end_small == 1 && end_big == P) {
                increasing_ans += pfx[P] - pfx[start_big];

                increasing_ans += pt_distance(start_pos, posts[start_big]);
                increasing_ans += pt_distance(end_pos, posts[P]);

            } else if (end_small < start_big) {
                // looped back from P, past 1
                increasing_ans += pfx[P] - pfx[start_big];
                increasing_ans += pt_distance(posts[1], posts[P]);
                increasing_ans += pfx[end_small];

                increasing_ans += pt_distance(start_pos, posts[start_big]);
                increasing_ans += pt_distance(end_pos, posts[end_small]);
            } else {
                // if did not loop back
                increasing_ans += pfx[end_small] - pfx[start_big];

                increasing_ans += pt_distance(start_pos, posts[start_big]);
                increasing_ans += pt_distance(end_pos, posts[end_small]);
            }
        }

        return increasing_ans;
    };

    for (int i = 1; i <= N; i++) {
        scanf("%lld %lld %lld %lld", &cows[i].first.first, &cows[i].first.second, &cows[i].second.first, &cows[i].second.second);

        if (cows[i].first == cows[i].second) {
            printf("0\n");
            continue;
        }

        p start_pos = cows[i].first;
        p end_pos = cows[i].second;
        p start_fences = find_current_pos(start_pos);
        p end_fences = find_current_pos(end_pos);

        int start_big = max(start_fences.first, start_fences.second);
        int end_small = min(end_fences.first, end_fences.second);
        int start_small = min(start_fences.first, start_fences.second);
        int end_big = max(end_fences.first, end_fences.second);

        // printf("%lld %lld, %lld %lld\n", start_fences.first, start_fences.second, end_fences.first, end_fences.second);

        // on the same fence
        int on_same_fence = false;
        on_same_fence |= (start_small == end_small) && (start_big == end_big);
        on_same_fence |= (start_small == start_big) && (start_small == end_small || start_small == end_big);
        on_same_fence |= (end_small == end_big) && (start_small == end_small || start_big == end_small);
        if (on_same_fence) {
            printf("%lld\n", pt_distance(start_pos, end_pos));
            continue;
        }

        int increasing_ans = calc_answer(start_pos, end_pos, start_fences, end_fences);
        int decreasing_ans = calc_answer(end_pos, start_pos, end_fences, start_fences);

        printf("%lld\n", min(increasing_ans, decreasing_ans));
    } 
}