#include <vector>
#include <algorithm>
#include <iostream>

using namespace std;

void setIO() {
    #ifndef TZ74_LOCAL_TESTING
    freopen("lemonade.in", "r", stdin);
    freopen("lemonade.out", "w", stdout);
    #endif
}

int main(void) {
    setIO();
    int N; cin >> N;
    vector<int> W(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> W[i];
    }
    std::sort(W.begin() + 1, W.end());
    std::reverse(W.begin() + 1, W.end());

    int cows = 0;
    for (int i = 1; i <= N; i++) {
        if (cows <= W[i]) {
            cows++;
        }
    }

    cout << cows << endl;
}