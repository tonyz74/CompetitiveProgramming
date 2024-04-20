#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

struct pair_hash {
  size_t operator() (const pair<long long, long long>& p) const {
      return ((size_t) p.first << 32) | p.second;
  }
};

unordered_map<pair<long long, long long>, pair<long long, long long>, pair_hash > info;
vector<vector<long long> > graph;
vector<pair<long long, long long> > pos;
vector<bool> explored;

void solve(long long me, long long from) {
    if (explored[me]) {
        return;
    }
    explored[me] = true;
    auto rel = info[make_pair(from, me)];
    pos[me] = make_pair(
        pos[from].first + rel.first,
        pos[from].second + rel.second
    );

    for (long long ep: graph[me]) {
        solve(ep, me);
    }
}

int main(void) {
    long long N, M;
    cin >> N >> M;

    graph.resize(N + 1, vector<long long>());
    pos.resize(N + 1);
    explored.resize(N + 1, 0);

    for (long long i = 0; i < M; i++) {
        long long a, b, x, y;
        cin >> a >> b >> x >> y;
        graph[a].push_back(b);
        graph[b].push_back(a);

        info[make_pair(a, b)] = make_pair(x, y);
        info[make_pair(b, a)] = make_pair(-x, -y);
    }

    pos[0] = make_pair(0, 0);
    solve(1, 0);

    for (long long i = 1; i <= N; i++) {
        if (explored[i]) {
            printf("%lld %lld\n", pos[i].first, pos[i].second);
        } else {
            printf("undecidable\n");
        }
    }
}