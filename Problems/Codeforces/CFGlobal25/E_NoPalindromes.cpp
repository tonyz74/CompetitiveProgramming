#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <string_view>

using namespace std;

bool is_palindrome(string_view sv) {
    int i = 0;
    int j = sv.length() - 1;

    while (i < j) {
        if (sv[i] != sv[j]) return false;
        i++; j--;
    }
    return true;
}

void solve() {
    string s; cin >> s;
    int n = s.length();

    if (!is_palindrome(s)) {
        cout << "YES" << endl;
        cout << 1 << endl;
        cout << s << endl;
        return;
    }

    map<char, int> occ;
    for (int i = 0; i < n; i++) {
        occ[s[i]]++;
    }

    if (occ.size() == 1) {
        cout << "NO" << endl;
        return;
    }

    char ch1 = s[0];
    int first_diff = 0;
    for (int i = 0; i < n - 1; i++) {
        if (s[i] != ch1) {
            first_diff = i;
            break;
        }
    }

    string_view front = string_view(s).substr(0, first_diff + 1);
    string_view back = string_view(s).substr(first_diff + 1);
    if (!is_palindrome(back)) {
        cout << "YES" << endl;
        cout << 2 << endl;
        cout << front << " " << back << endl;
        return;
    }

    // remember we're 0 indexed, 1 means 2nd pos, n / 2 means middle pos

    // could only be two distinct chars now
    if (first_diff == n / 2) {
        cout << "NO" << endl;
        return;
    } else if (first_diff == 1) {
        cout << "NO" << endl;
        return;
    } else {
        front = string_view(s).substr(0, first_diff + 2);
        back = string_view(s).substr(first_diff + 2);
        cout << "YES" << endl;
        cout << 2 << endl;
        cout << front << " " << back << endl;
        return;
    }
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}