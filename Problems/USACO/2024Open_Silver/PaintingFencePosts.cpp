#include <iostream>
#include <vector>
#include <algorithm>
#include <set>
#include <map>
#include <unordered_map>
#include <cassert>

using namespace std;
using i64 = long long;

using p = pair<i64, i64>;

i64 N, P;

set<p> connected;
map<p, int> post_index;
vector<p> posts;

unordered_map<i64, set<p> > at_x;
unordered_map<i64, set<p> > at_y;

map<p, int> orig_idx;

void get_ordered_posts() {
    unordered_map<i64, vector<pair<i64, i64> > > same_x;
    unordered_map<i64, vector<pair<i64, i64> > > same_y;

    vector<pair<i64, i64> > unordered_posts(P + 1);
    for (i64 i = 1; i <= P; i++) {
        i64 x, y; cin >> x >> y;
        unordered_posts[i].first = x;
        unordered_posts[i].second = y;

        orig_idx[make_pair(x, y)] = i;

        same_x[x].push_back(make_pair(y, i));
        same_y[y].push_back(make_pair(x, i));
    } 

    for (auto p: same_x) {
        std::sort(same_x[p.first].begin(), same_x[p.first].end());
    }
    for (auto p: same_y) {
        std::sort(same_y[p.first].begin(), same_y[p.first].end());
    }

    vector<vector<i64> > graph(P + 1);
    for (i64 i = 1; i <= P; i++) {
        pair<i64, i64> p = unordered_posts[i];
        i64 x = p.first;
        i64 y = p.second;

        i64 pos_y = std::lower_bound(same_x[x].begin(), same_x[x].end(), make_pair(y, 0ll)) - same_x[x].begin();
        i64 n_above = same_x[x].size() - (pos_y + 1);
        i64 n_below = pos_y;

        if (n_above % 2 == n_below % 2) {
            printf("-1\n");
            exit(0);
        }

        if (n_above % 2 == 1) {
            graph[i].push_back(same_x[x][pos_y + 1].second);
            // printf("connect %d to %d (same x), above\n", i, same_x[x][pos_y + 1].second);
        } else if (n_below % 2 == 1) {
            graph[i].push_back(same_x[x][pos_y - 1].second);
            // printf("connect %d to %d (same x), below\n", i, same_x[x][pos_y - 1].second);
        }

        i64 pos_x = std::lower_bound(same_y[y].begin(), same_y[y].end(), make_pair(x, 0ll)) - same_y[y].begin();
        i64 n_right = same_y[y].size() - (pos_x + 1);
        i64 n_left = pos_x;

        if (n_right % 2 == n_left % 2) {
            printf("-1\n");
            exit(0);
        }

        if (n_right % 2 == 1) {
            graph[i].push_back(same_y[y][pos_x + 1].second);
            // printf("connect %d to %d (same y), right\n", i, same_y[y][pos_x + 1].second);
        } else if (n_left % 2 == 1) {
            graph[i].push_back(same_y[y][pos_x - 1].second);
            // printf("connect %d to %d (same y), left\n", i, same_y[y][pos_x - 1].second);
        }
    }

    i64 start = 1;
    vector<i64> seen(P + 1, 0);

    while (!seen[start]) {
        seen[start] = true;
        posts.push_back(unordered_posts[start]);

        i64 next = -1;
        for (i64 x: graph[start]) {
            if (!seen[x]) {
                next = x; break;
            }
        }

        if (next == -1) break;
        start = next;
    } 
}

p get_closest_posts(p pt) {
    if (post_index.count(pt)) {
        return make_pair(post_index[pt], post_index[pt]);
    }

    if (!at_x[pt.first].empty()) {
        auto up = at_x[pt.first].upper_bound(make_pair(pt.second, 0));
        if (up != at_x[pt.first].begin() && up != at_x[pt.first].end()) {
            auto down = up; down--;

            if (connected.count({ up->second, down->second })) {
                return make_pair(up->second, down->second);
            }
        }
    }

    if (!at_y[pt.second].empty()) {
        auto right = at_y[pt.second].upper_bound(make_pair(pt.first, 0));
        if (right != at_y[pt.second].begin() && right != at_y[pt.second].end()) {
            auto left = right; left--;

            if (connected.count({ right->second, left->second })) {
                return make_pair(right->second, left->second);
            }
        }
    }

    // should not happen
    // printf("try %lld %lld\n", pt.first, pt.second);
    assert(false);
}

i64 dist(p A, p B) {
    return abs(A.first - B.first) + abs(A.second - B.second);
}

int main(void) {
    cin >> N >> P;
    posts.resize(1);

    get_ordered_posts();

    for (i64 i = 1; i <= P; i++) {
        p pos = posts[i];
        // printf("%lld %lld\n", pos.first, pos.second);
        at_x[pos.first].insert(make_pair(pos.second, i));
        at_y[pos.second].insert(make_pair(pos.first, i));
        post_index[pos] = i;

        i64 next = i + 1;
        if (i == P) next = 1;

        connected.insert(make_pair(i, next));
        connected.insert(make_pair(next, i));
    }

    i64 perim = 0;
    vector<i64> psum(2 * P + 1);
    {
        p now = posts[1];
        for (i64 i = 2; i <= P; i++) {
            psum[i] = psum[i - 1] + dist(now, posts[i]);
            now = posts[i];
        }

        psum[P + 1] = psum[P] + dist(posts[1], posts[P]);
        perim = psum[P + 1];

        now = posts[1];
        i64 j = 2;
        for (i64 i = P + 2; i <= 2 * P; i++) {
            psum[i] = psum[i - 1] + dist(now, posts[j]);
            now = posts[j];
            j++;
        }
        
    }

    auto transform_posts = [&] (i64 S, i64 E) {
        i64 len = E - S;
        if (len < 0) {
            len += P;
        }

        // printf("len %lld\n", len);
        return make_pair(S, S + len);
    };

    auto post_dist = [&] (i64 S, i64 E) {
        auto ps = transform_posts(S, E);
        // printf("going to start ps 1 %lld, ps 2 %lld\n", ps.first, ps.second);
        return psum[ps.second] - psum[ps.first];
    };

    auto whole_dist = [&] (p S, p E, p S_idx, p E_idx) {
        int S_b = max(S_idx.first, S_idx.second); int S_s = min(S_idx.first, S_idx.second);
        int E_b = max(E_idx.first, E_idx.second); int E_s = min(E_idx.first, E_idx.second);

        i64 sp = (S_b == P && S_s == 1) ? 1 : S_b;
        i64 ep = (E_b == P && E_s == 1) ? P : E_s;

        i64 ans = dist(S, posts[sp]) + dist(E, posts[ep]);
        ans += post_dist(sp, ep);

        // printf("going to start %lld, end %lld got %lld\n", sp, ep, post_dist(sp, ep));

        return make_pair(ans, make_pair(sp, ep));
    };

    vector<i64> diff_array(2 * P + 2, 0);

    for (i64 i = 1; i <= N; i++) {
        p p1, p2;
        cin >> p1.first >> p1.second >> p2.first >> p2.second;

        p sps = get_closest_posts(p1); 
        p eps = get_closest_posts(p2); 

        int min_start = min(sps.first, sps.second);
        int max_start = max(sps.first, sps.second);
        int min_end = min(eps.first, eps.second);
        int max_end = max(eps.first, eps.second);

        // printf("%d %d %d %d\n", min_start, max_start, min_end, max_end);
        if (min_start == min_end && max_start == max_end) {
            continue;
        }

        pair<i64, p> ans1 = whole_dist(p1, p2, sps, eps);
        i64 length = ans1.first;

        i64 start_post = -1; i64 end_post = -1;
        // printf("cow %lld goes positive %lld, negative %lld\n", i, length, perim - length);

        // go along this side
        if (length < perim - length) {
            start_post = ans1.second.first;
            end_post = ans1.second.second;
        } else {
            pair<i64, p> ans2 = whole_dist(p2, p1, eps, sps);
            start_post = ans2.second.first;
            end_post = ans2.second.second;
        }

        auto tf = transform_posts(start_post, end_post);
        diff_array[tf.first]++;
        diff_array[tf.second + 1]--;
    }

    i64 cnt = 0;
    vector<i64> touches(2 * P + 4, 0);
    for (i64 i = 1; i <= 2 * P + 1; i++) {
        cnt += diff_array[i];
        touches[i] = cnt;
    }

    vector<i64> orig_ans(P + 1);

    for (i64 i = 1; i <= P; i++) {
        orig_ans[orig_idx[posts[i]]] += touches[i] + touches[P + i];
    }

    for (i64 i = 1; i <= P; i++) {
        printf("%lld\n", orig_ans[i]);
    }
}