#include <iostream>
#include <vector>
#include <cstring>
#include <map>
#include <set>
#include <unordered_set>

using namespace std;
using i32 = int;

struct edge {
    i32 dst, wt;
    edge(i32 d, i32 w) : dst(d), wt(w) {}
};

#define MAX_N ((i32) (3 * 1e5 + 4))
#define UNDEFINED_DIST 1e9

i32 N, S;
map<i32, i32> down_cache;
vector<i32> dist_down;
unordered_set<i32> blacklist;
vector<vector<edge> > tree;
map<pair<i32, i32>, i32> edge_weights;

void clear_dists() {
    for (i32 i = 1; i <= N; i++) dist_down[i] = UNDEFINED_DIST;
}

i32 get_distances(i32 now) {
    dist_down[now] = 0;
    for (edge e: tree[now]) {
        if (dist_down[e.dst] == UNDEFINED_DIST && !blacklist.count(e.dst)) {
            dist_down[now] = max(dist_down[now], get_distances(e.dst) + e.wt);
        }
    }

    return dist_down[now];
}

vector<i32> get_furthest_path(i32 now) {
    clear_dists();
    get_distances(now);
    vector<i32> path;

    vector<i32> seen(N + 1, 0);
    while (true) {
        path.push_back(now);
        seen[now] = true;
        i32 max_dist_down = -1e9;
        i32 next = -1;
        for (edge e: tree[now]) {
            if (dist_down[e.dst] > max_dist_down && !seen[e.dst]) {
                max_dist_down = dist_down[e.dst];
                next = e.dst;
            }
        }
        if (next == -1) break;
        now = next;
    }

    return path;
}

vector<i32> get_diameter() {
    vector<i32> far = get_furthest_path(1);
    return get_furthest_path(far.back());
}

i32 dia_len;
vector<i32> dia;
i32 dia_total_dist = 0;
map<i32, i32> dist_left;
multiset<i32> state;
unordered_set<i32> added_by_j;

// distance between nodes x and y (must be on diameter),
i32 get_dist_between(i32 x, i32 y) {
    return dist_left[y] - dist_left[x];
}

void erase_one(i32 x) {
    state.erase(state.find(x));
}

i32 get_dist_right(i32 x) {
    return dia_total_dist - dist_left[x];
}

int main(void) {
    cin >> N >> S;
    tree.resize(N + 1);
    dist_down.resize(N + 1);
    for (i32 i = 1; i <= N - 1; i++) {
        i32 s, e, w; cin >> s >> e >> w;
        edge_weights[make_pair(s, e)] = w;
        edge_weights[make_pair(e, s)] = w;
        tree[s].push_back(edge(e, w));
        tree[e].push_back(edge(s, w));
    }

    dia = get_diameter();
    dia_len = dia.size();

    for (i32 i = 0; i < dia_len; i++) {
        blacklist.insert(dia[i]);
        i32 prev = 0;
        if (i != 0) {
            prev = dist_left[dia[i - 1]] + edge_weights[make_pair(dia[i - 1], dia[i])];
        }
        dist_left[dia[i]] = prev;
    }
    dia_total_dist = dist_left[dia.back()];

    clear_dists();
    for (i32 i = 0; i < dia_len; i++) {
        down_cache[dia[i]] = get_distances(dia[i]);
    }

    dist_down.clear();

    i32 ans = 1e9;
    i32 j = 0;
    state.insert(get_dist_right(dia[j]));
    for (i32 i = 0; i < dia_len; i++) {
        state.insert(dist_left[dia[i]]);
        erase_one(get_dist_right(dia[j]));
        j = max(j, i);

        while (j != dia_len - 1 && get_dist_between(dia[i], dia[j + 1]) <= S) {
            state.insert(dist_down[dia[j]]);
            added_by_j.insert(dia[j]);
            j++;
        }
        state.insert(get_dist_right(dia[j]));

        ans = min(ans, *state.rbegin());

        erase_one(dist_left[dia[i]]);
        if (added_by_j.count(dia[i])) {
            erase_one(dist_down[dia[i]]);
            added_by_j.erase(dia[i]);
        }
    }

    printf("%lld\n", ans);
}