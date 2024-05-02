#include <iostream>
#include <stack>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>

#define MAX_N (int(1e6 + 7))
#define MAX_M MAX_N

#define PATH_LIMIT 36500

using namespace std;

int N, M;
vector<int> graph[MAX_N];
bool has_self_loop[MAX_N];

vector<bool> color_is_cycle(1);
vector<vector<int> > color_contents(1);

int cnt = 0;
int color = 0;

int low[MAX_N];
int dfn[MAX_N];
int color_of[MAX_N];
stack<int> stk;
bool vis[MAX_N];

void tarjan(int x) {
    dfn[x] = low[x] = ++cnt;
    stk.push(x);
    vis[x] = true;

    for (int conn: graph[x]) {
        if (dfn[conn] == 0) {
            tarjan(conn);
            low[x] = min(low[conn], low[x]);
        } else {
            // already been visited. can i make a jump?
            // only if its an scc candidate (i.e. not already part
            // of a smaller scc node x cannot join because it never
            // reached node x before it was popped).
            if (vis[conn]) {
                low[x] = min(low[x], dfn[conn]);
            }
        }
    }

    // no way to go up later, remove this as an scc now
    if (low[x] == dfn[x]) {
        int top;
        int new_color = ++color;
        int sz = 0;

        vector<int> contents;

        do {
            top = stk.top();
            contents.push_back(top);
            stk.pop();
            vis[top] = false;
            color_of[top] = new_color;
            sz++;
        } while (top != x);

        if (sz >= 2 || (sz == 1 && has_self_loop[x])) {
            // printf("color is cycle %d yes\n", new_color);
            color_is_cycle.push_back(true);
        } else {
            color_is_cycle.push_back(false);
        }

        color_contents.push_back(contents);
    }
}

int main(void) {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> N >> M;

    vector<pair<int, int> > edges(M + 1);
    for (int i = 1; i <= M; i++) {
        int a, b; cin >> a >> b;
        if (a == b) {
            has_self_loop[a] = true;
        }

        graph[a].push_back(b);
        edges[i].first = a;
        edges[i].second = b;
    }

    for (int i = 1; i <= N + 1; i++) {
        if (dfn[i] == 0) {
            tarjan(i);
        }

        // printf("node %d => color %d\n", i, color_of[i]);
        // printf("%d %d\n", low[i], dfn[i]);
    }

    // printf("\n\n");

    // 
    // part 2 -- computing answer
    //

    int C = color + 7;

    vector<vector<int> > rdag(C + 1);
    vector<int> in_degree(C + 1, 0);

    for (int i = 1; i <= M; i++) {
        int a = edges[i].first, b = edges[i].second;
        int ca = color_of[a], cb = color_of[b];

        if (ca == cb) continue;

        // we have to add in reverse, reverse dag for topo later
        // printf("%d conn %d\n", cb, ca);
        rdag[cb].push_back(ca);
        in_degree[ca]++;
    }

    // now we know the central node is our dst
    // topo in reverse (flip edges) to find
    // n ways to get there from each point.
    deque<int> zeroes;
    for (int i = 1; i <= color; i++) {
        if (in_degree[i] == 0) {
            zeroes.push_front(i); 
        }
    }

    vector<int> dp(C + 1, 0);
    int dst_color = color_of[N + 1];
    dp[dst_color] = 1;
    // assert(color_is_cycle[color_of[N + 1]] == false);

    int mx = 0;

    while (!zeroes.empty()) {
        int me = zeroes.front();
        // printf("me %d\n", me);
        zeroes.pop_front();

        // at least one way to get there and i'm a cycle, i must be infinite
        if (color_is_cycle[me] && dp[me] != 0) {
            dp[me] = PATH_LIMIT + 7;
        }
        mx = max(mx, dp[me]);

        for (int conn: rdag[me]) {
            dp[conn] += dp[me];
            dp[conn] = min(dp[conn], PATH_LIMIT + 7);
            in_degree[conn]--;

            mx = max(mx, dp[conn]);

            if (in_degree[conn] == 0) {
                zeroes.push_back(conn);
            }
        }

        // for (int i = 1; i <= color; i++) {
        //     printf("%d ", dp[i]);
        // }
        // printf("\n");
    }

    vector<int> occ;
    if (mx > PATH_LIMIT) {
        cout << "zawsze" << endl;
        for (int i = 1; i <= color; i++) {
            if (dp[i] > PATH_LIMIT) occ.push_back(i);
        }
    } else if (mx <= PATH_LIMIT) {
        cout << mx << endl;
        for (int i = 1; i <= color; i++) {
            if (dp[i] == mx) occ.push_back(i);
        }
    }

    int size = 0;
    vector<int> output;
    for (int c: occ) {
        for (int i: color_contents[c]) {
            if (i != N + 1) {
                size++;
                output.push_back(i);
            }
        }
    }

    cout << size << endl;
    std::sort(output.begin(), output.end());
    for (int j: output) {
        cout << j << " ";
    }
    cout << endl;
}
