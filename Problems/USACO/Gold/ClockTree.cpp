#include <iostream>
#include <vector>

using namespace std;

int N;

#define MAX_N 2502

int clocks_save[MAX_N];
int clocks[MAX_N];
vector<int> tree[MAX_N];

bool works(int start) {
    memcpy(clocks, clocks_save, sizeof(clocks));
    // to make leaves 12, must first go to leaves
}

int main(void) {
    int N; cin >> N;

    for (int i = 1; i <= N; i++) {
        cin >> clocks[i];
    }

    for (int i = 1; i <= N - 1; i++) {
        int s, e; cin >> s >> e;
        tree[s].push_back(e);
        tree[e].push_back(s);
    }

    int ans = 0;
    for (int start = 1; start <= N; start++) {
        if (works(start)) {
            ans++;
        }
    }

    printf("%d\n", ans);
}