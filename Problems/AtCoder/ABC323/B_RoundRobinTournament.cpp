#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

int main(void) {
    int N; cin >> N;

    vector<string> robin(N);
    vector<pair<int, int> > wins(N);

    for (int i = 0; i < N; i++) {
        wins[i].second = i + 1;
    }

    for (int s = 0; s < N; s++) {
        cin >> robin[s];
    }

    for (int player = 1; player <= N; player++) {
        int p = player - 1;

        for (int i = 0; i < N; i++) {
            if (robin[i][p] == 'o') {
                wins[p].first++;
            }
        }
    }

    sort(wins.begin(), wins.end());
    for (auto &p : wins) {
        cout << p.second << " ";
    }
    cout << endl;
}