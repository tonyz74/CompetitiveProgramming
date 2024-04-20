#include <iostream>
#include <vector>

using namespace std;

#define MAX_N ((int)(1e5 + 5))

int group_cnt = 1;

int val[MAX_N];
int group[MAX_N];
vector<int> adj[MAX_N];

void dfs(int current, int from) {
    group[current] = group_cnt;

    for (int conn: adj[current]) {
        if (conn != from && val[conn] == val[current]) {
            dfs(conn, current);
        }
    }
}

int main(void) {
    freopen("milkvisits.in", "r", stdin);
    freopen("milkvisits.out", "w", stdout);

    int N, M; cin >> N >> M;

    string S; cin >> S;
    for (int i = 1; i <= N; i++) {
        val[i] = S[i - 1];
    }
    
    for (int i = 1; i <= N - 1; i++) {
        int a, b; cin >> a >> b;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    for (int start = 1; start <= N; start++) {
        if (group[start] == 0) {
            dfs(start, -1);
            group_cnt++;
        }
    }

    for (int i = 0; i < M; i++) {
        int A, B; cin >> A >> B;
        char wanted; cin >> wanted;

        if (group[A] == group[B] && val[A] == wanted) {
            printf("1");
        } else if (group[A] != group[B]) {
            printf("1");
        } else {
            printf("0");
        }
    }
    printf("\n");
}