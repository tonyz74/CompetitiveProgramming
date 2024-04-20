#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    freopen("factory.in", "r", stdin);
    freopen("factory.out", "w", stdout);

    int N; cin >> N;
    vector<vector<int> > tree(N + 1);

    for (int i = 0; i < N - 1; i++) {
        int s, e; cin >> s >> e;
        tree[s].push_back(e);
    }

    int answer = -1;
    for (int i = 1; i <= N; i++) {
        if (tree[i].empty()) {
            if (answer == -1) answer = i;
            else { answer = -1; break; }
        } 
    }
    printf("%d\n", answer);
}