#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

int main(void) {
    auto solve = [&] () {
        int n; cin >> n;
        string s; cin >> s;

        string rev = s;
        std::reverse(rev.begin(), rev.end());
        
        string opt1 = s;
        string opt2 = rev + s;

        string ans = min(opt1, opt2);
        cout << ans << endl;
    };

    int t; cin >> t;
    while (t--) solve();
}