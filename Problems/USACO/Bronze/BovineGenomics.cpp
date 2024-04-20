#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main(void) {
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);

    int N, M;
    cin >> N >> M;

    vector<string> spotty(N);
    for (int i = 0; i < N; i++) cin >> spotty[i];

    vector<string> plain(N);
    for (int i = 0; i < N; i++) cin >> plain[i];

    int total = 0;

    for (int location = 0; location < M; location++) {
        bool in_spots[1024] = {};
        for (int i = 0; i < N; i++) in_spots[(int) spotty[i][location]] = true;

        bool all = true;
        for (int i = 0; i < N; i++) {
            if (in_spots[(int) plain[i][location]]) {
                all = false;
                break;
            }
        }

        if (all) {
            total++;
        }
    }

    cout << total << endl;
}