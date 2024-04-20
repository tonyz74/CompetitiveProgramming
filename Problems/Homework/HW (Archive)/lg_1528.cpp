#include <iostream>
#include <algorithm>
using namespace std;

int N, M;
int S[50 + 1];
int F[1024 + 1];

int now = 0;
int best = 0;

void dfs(int person) {
    best = max(best, now);
    if (person == M) {
        return;
    }

    for (int i = 0; i < N; i++) {
        S[i] -= F[person];
        if (S[i] >= 0) {
            now++;
            dfs(person + 1);
            now--;
        }
        S[i] += F[person];
    }

    // if we didn't sort, we would need this
    // dfs(person + 1)
}

int main(void) {
    cin >> N;
    for (int i = 0; i < N; i++) cin >> S[i];
    cin >> M;
    for (int i = 0; i < M; i++) cin >> F[i];

    // Greedily use smallest mouth size first
    sort(F, F + M);

    dfs(0);
    cout << best << endl;
}