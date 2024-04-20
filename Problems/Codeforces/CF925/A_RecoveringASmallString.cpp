#include <iostream>
#include <vector>
#include <cassert>
#include <string>
#include <algorithm>

using namespace std;

void solve() { 
    int v; cin >> v;
    vector<string> possible;
    for (int ch1 = 1; ch1 <= 26; ch1++) {
        for (int ch2 = 1; ch2 <= 26; ch2++) {
            for (int ch3 = 1; ch3 <= 26; ch3++) {
                if (ch1 + ch2 + ch3 == v) {
                    string S;
                    S += ('a' + ch1 - 1);
                    S += ('a' + ch2 - 1);
                    S += ('a' + ch3 - 1);
                    possible.push_back(S);
                }
            }
        }
    }

    std::sort(possible.begin(), possible.end());
    assert(possible.size() >= 1);
    printf("%s\n", possible[0].c_str());
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}