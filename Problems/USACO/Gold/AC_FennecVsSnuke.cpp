#include <iostream>
#include <vector>

using namespace std;

#define MAX_N ((int) (1e5 + 4))

int N;
vector<int> tree[MAX_N];
int coloring[MAX_N];

// for each node, which node the parent is
int to_fennec[MAX_N];
// for each node, which child snuke is in
int to_snuke[MAX_N];

#define EMPTY 0
#define BLACK 2
#define WHITE 3

int fennec_pos, snuke_pos;

void down(int now, int from) {
    to_fennec[now] = from;
    for (int ch: tree[now]) {
        if (to_fennec[ch] == EMPTY) {
            down(ch, now);
        }
    }
}

bool seen[MAX_N];
int find_empty(int now, int safe_color) {
    if (seen[now]) return 0;
    seen[now] = true;
    int ans = 0;

    if (coloring[now] == EMPTY) {
        ans++;
    }

    for (int ch: tree[now]) {
        int color = coloring[ch];
        if (!seen[ch] && (color == safe_color || color == EMPTY)) {
            ans += find_empty(ch, safe_color);
        }
    }

    return ans;
}

int main(void) {
    cin >> N;

    for (int i = 1; i <= N - 1; i++) {
        int a, b; cin >> a >> b;
        tree[a].push_back(b);
        tree[b].push_back(a);
    }

    // assume fennec is at the root. there is always only
    // one path she can pick that leads to snuke,
    // similarly snuke will always pick the path that leads up
    down(1, -1);

    // snuke at N right now, trace back to fennec so she
    // always knows where to go
    int pos = N;
    while (pos != 1) {
        to_snuke[to_fennec[pos]] = pos;
        pos = to_fennec[pos];
    }
    
    // now simulate the game
    coloring[1] = BLACK;
    coloring[N] = WHITE;

    // if turn is even (or 0), fennec is currently playing,
    // otherwise snuke is currently playing
    fennec_pos = 1;
    snuke_pos = N;
    int turn = 0;

    while (true) {
        // fennec plays
        if (turn % 2 == 0) {
            if (coloring[to_snuke[fennec_pos]] == EMPTY) {
                fennec_pos = to_snuke[fennec_pos];
                coloring[fennec_pos] = BLACK;
                // printf("fennec picks %d\n", fennec_pos);
            } else {
                // fennec can't make any more moves
                break;
            }
        }

        // snuke plays
        if (turn % 2 == 1) {
            if (coloring[to_fennec[snuke_pos]] == EMPTY) {
                snuke_pos = to_fennec[snuke_pos];
                coloring[snuke_pos] = WHITE;
                // printf("snuke picks %d\n", snuke_pos);
            } else {
                // snuke can't make any more moves
                break;
            }
        }
        turn++;
    }

    int fennec_pickable = find_empty(1, BLACK);
    int snuke_pickable = find_empty(N, WHITE);

    if (turn % 2 == 0) {
        // printf("stopped during fennec's turn\n");
        if (fennec_pickable > snuke_pickable) {
            printf("Fennec\n");
        } else {
            printf("Snuke\n");
        }
    } else {
        // printf("stopped during snuke's turn\n");
        if (snuke_pickable > fennec_pickable) {
            printf("Snuke\n");
        } else {
            printf("Fennec\n");
        }
    }

    // printf("%d black left, %d white left\n", fennec_pickable, snuke_pickable);

}