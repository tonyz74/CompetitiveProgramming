#include <iostream>
#include <vector>

using namespace std;

#define MAX_N ((int) 1e5 + 4)

vector<int> s_edge[MAX_N];
vector<int> d_edge[MAX_N];

int marker = 1;
int group_of[MAX_N];
int coloring[MAX_N];

int fail = 0;

void dfs(int curr, int color) {
    group_of[curr] = marker;
    coloring[curr] = color;

    for (int x: d_edge[curr]) {
        if (coloring[x] != 0 && coloring[x] == coloring[curr]) {
            fail = true;
        }
        if (!group_of[x]) {
            dfs(x, (color == 1) ? 2 : 1);
        }
    }

    for (int x: s_edge[curr]) {
        if (coloring[x] != 0 && coloring[x] != coloring[curr]) {
            fail = true;
        }
        if (!group_of[x]) {
            dfs(x, color);
        }
    }
}

int main(void) {
    freopen("revegetate.in", "r", stdin);
    freopen("revegetate.out", "w", stdout);

    int N, M; cin >> N >> M;

    for (int i = 0; i < M; i++) {
        string type; cin >> type;
        int start, end;
        cin >> start >> end;

        if (type == "S") {
            s_edge[start].push_back(end);
            s_edge[end].push_back(start);
        } else {
            d_edge[end].push_back(start);
            d_edge[start].push_back(end);
        }
    }

    vector<vector<int> > comps(MAX_N);
    for (int i = 1; i <= N; i++) {
        if (group_of[i] == 0) {
            dfs(i, 1);
            marker++;
        }
        comps[group_of[i]].push_back(i);
    }

    if (fail) {
        printf("0\n");
        return 0;
    }

    printf("1");
    for (int i = 1; i < marker; i++) {
        printf("0");
    }
    printf("\n");
}