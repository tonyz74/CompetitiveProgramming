#include <iostream>
#include <vector>

using namespace std;

#define MAX_N ((int) (2 * 1e5 + 7))

int N, M;
int A[MAX_N];
int B[MAX_N];

vector<int> graph[MAX_N];
int group_of[MAX_N];

int group_marker = 1;

void dfs(int x) {
    if (group_of[x] != 0) return;
    group_of[x] = group_marker;

    for (int conn: graph[x]) {
        if (group_of[conn] == 0) {
            dfs(conn);
        }
    }
}

int main(void) {
    cin >> N >> M;

    for (int i = 1; i <= M; i++) {
        cin >> A[i] >> B[i];

        graph[A[i]].push_back(B[i]);
        graph[B[i]].push_back(A[i]);
    }

    for (int i = 1; i <= N; i++) {
        if (group_of[i] == 0) {
            dfs(i);
            group_marker++;
        }
    }

    vector<int> nodes_in_group(group_marker + 2);
    vector<int> edges_in_group(group_marker + 2);

    for (int i = 1; i <= N; i++) {
        nodes_in_group[group_of[i]]++;
    }

    for (int i = 1; i <= M; i++) {
        edges_in_group[group_of[A[i]]]++;
    }

    long long ans = 0;
    for (int i = 1; i < group_marker; i++) {
        long long nodes = nodes_in_group[i];
        long long already_used = edges_in_group[i];

        ans += (nodes * (nodes - 1)) / 2 - already_used;
    }

    cout << ans << endl;
}
