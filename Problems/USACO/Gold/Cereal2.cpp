#include <iostream>
#include <vector>
#include <set>

using namespace std;
using i64 = long long;

#define MAX_N ((i64) 1e5 + 2)
#define MAX_M ((i64) 1e5 + 2)

i64 marker = 1;
i64 group_id[MAX_M];

struct cow {
    i64 fav;
    i64 second_fav;
    i64 id;
};

vector<pair<i64, i64> > graph[MAX_M];
cow cows[MAX_N];

vector<i64> comps[MAX_M];
cow cycle_edge[MAX_M];
bool done_before[MAX_M];

void dfs(i64 curr, i64 prev) {
    group_id[curr] = marker;

    for (auto p: graph[curr]) {
        i64 conn = p.second;

        if (group_id[conn] != 0 && conn != prev) {
            cycle_edge[marker] = cows[p.first];
        }

        if (group_id[conn] == 0) {
            dfs(conn, curr);
        }
    }
}

i64 seen[MAX_M];
i64 picked[MAX_M];

vector<i64> ordering;

void search_st(i64 curr) {
    seen[curr] = true;

    for (pair<i64, i64> edge: graph[curr]) {
        if ((picked[edge.second] && picked[curr]) || done_before[edge.first]) {
            continue;
        }

        if (picked[edge.second]) {
            picked[curr] = true;
        } else if (picked[curr]) {
            picked[edge.second] = true;
        } else {
            if (cows[edge.first].fav == edge.second) {
                picked[edge.second] = true;
            } else {
                picked[curr] = true;
            }
        }

        ordering.push_back(edge.first);
        done_before[edge.first] = true;

        if (!seen[edge.second]) search_st(edge.second);
    }
}

int main(void) {
    i64 N, M; cin >> N >> M; 

    for (i64 i = 1; i <= N; i++) {
        cin >> cows[i].fav >> cows[i].second_fav;
        cows[i].id = i;
        graph[cows[i].fav].push_back(make_pair(i, cows[i].second_fav));
        graph[cows[i].second_fav].push_back(make_pair(i, cows[i].fav));
    }

    for (i64 m = 1; m <= M; m++) {
        if (group_id[m] == 0) {
            dfs(m, -1); 
            marker++;
        }
        comps[group_id[m]].push_back(m);
    }


    for (i64 mark = 1; mark < marker; mark++) {
        if (comps[mark].size() == 1) continue;

        // if a tree
        if (cycle_edge[mark].fav == 0) {
            search_st(comps[mark][0]);
        } else {
            picked[cycle_edge[mark].fav] = 1;
            ordering.push_back(cycle_edge[mark].id);
            done_before[cycle_edge[mark].id] = true;
            search_st(cycle_edge[mark].fav);
        }
    }

    printf("%lld\n", N - ordering.size());

    for (i64 x: ordering) {
        printf("%lld\n", x);
    }

    for (i64 i = 1; i <= N; i++) {
        if (!done_before[i]) {
            printf("%lld\n", i);
        }
    }
}