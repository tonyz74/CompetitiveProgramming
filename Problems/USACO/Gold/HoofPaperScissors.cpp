#include <iostream>
#include <map>
#include <vector>

using namespace std;

using state = map<char, int>;

int main(void) {
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    int N; cin >> N;

    state curr;
    vector<state> pre(N + 1);

    vector<char> moves = { 'H', 'P', 'S' };
    map<char, char> beats = {
        { 'H', 'S' },
        { 'P', 'H' },
        { 'S', 'P' }
    };

    for (int i = 1; i <= N; i++) {
        char c; cin >> c;
        curr[c]++;
        pre[i] = curr;
    }

    int best_wins = 0;

    // enumerate which she starts with
    for (char start: moves) {

        // find the best location to switch moves
        for (int i = 1; i <= N; i++) {
            int wins_before_this = pre[i - 1][beats[start]];

            for (char new_move: moves) {
                int wins_after_this = pre[N][beats[new_move]] - pre[i - 1][beats[new_move]];
                best_wins = max(best_wins, wins_before_this + wins_after_this);
            }
        }

    }

    cout << best_wins << endl;
}