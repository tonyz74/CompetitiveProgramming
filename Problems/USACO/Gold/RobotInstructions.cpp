#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <map>
#include <algorithm>

using namespace std;
using i64 = long long;
using point = pair<i64, i64>;

struct hash_fn {
    std::size_t operator()(const point& p) const {
        return 239 * p.first + p.second;
    }
};

i64 N;
point dst;
i64 ans_at_num[80] = {0};

point curr_point;
const vector<point>* curr_v;

template<typename K, typename V, typename hash_fn>
struct hashmap {
    vector<vector<pair<K, V> > > data;
    
    hashmap() {
        data.resize(1e5 + 7);
    }

    hashmap(int cap) {
        data.resize(cap);
    }

    void insert(K key, V value) {
        size_t hash = hash_fn()(key);
        int pos = hash % (data.size());
        data[pos].push_back(make_pair(key, value));
    }

    pair<K, V>* search(K key) {
        size_t hash = hash_fn()(key);
        int pos = hash % (data.size());

        for (int i = 0; i < int(data[pos].size()); i++) {
            if (data[pos][i].first == key) {
                return &data[pos][i];
            }
        }

        return nullptr;
    }
};

vector<pair<point, i64> > opts_start;
hashmap<point, i64, hash_fn> opts_end[21];
hashmap<point, bool, hash_fn> exists_in_end;

void dfs(int i, int k, int type) {
    if (i == (int) curr_v->size()) {
        if (type == 1) {
            opts_start.push_back(make_pair(curr_point, k));
        } else {
            pair<point, i64>* pt;
            pt = opts_end[k].search(curr_point);
            if (pt != nullptr) {
                pt->second++;
            } else {
                opts_end[k].insert(curr_point, 1);

            }

            if (exists_in_end.search(curr_point) == nullptr) {
                exists_in_end.insert(curr_point, 1);
            }
        }


        return;
    }

    // pick this one
    curr_point.first += (*curr_v)[i].first;
    curr_point.second += (*curr_v)[i].second;
    dfs(i + 1, k + 1, type);
    curr_point.first -= (*curr_v)[i].first;
    curr_point.second -= (*curr_v)[i].second;

    dfs(i + 1, k, type);
}

int main(void) {
    cin >> N;
    cin >> dst.first >> dst.second;

    vector<point> moves_start(N / 2);
    for (i64 i = 0; i < N / 2; i++) {
        cin >> moves_start[i].first >> moves_start[i].second;
    }

    vector<point> moves_end(N - N / 2);
    for (i64 i = 0; i < N - N / 2; i++) {
        cin >> moves_end[i].first >> moves_end[i].second;
        moves_end[i].first *= -1;
        moves_end[i].second *= -1;
    }

    curr_v = &moves_start;
    curr_point = make_pair(0, 0);
    dfs(0, 0, 1);

    curr_v = &moves_end;
    curr_point = dst;
    dfs(0, 0, 2);

    for (auto p: opts_start) {
        if (!exists_in_end.search(p.first)) continue;
        for (int j = 0; j <= 20; j++) {
            auto it = opts_end[j].search(p.first);
            if (it != nullptr) {
                ans_at_num[p.second + j] += it->second;
            }
        }
    }

    for (i64 i = 1; i <= N; i++) {
        printf("%lld\n", ans_at_num[i]);
    }
}