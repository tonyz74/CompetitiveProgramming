#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

int N;
string match;
vector<string> S;

bool is_eq(string &a) {
    int len_diff = a.length() - match.length();
    if (len_diff != 0 && len_diff != -1 && len_diff != 1) {
        return false;
    }

    int smaller = min(a.length(), match.length());

    int prefix = 0;
    for (int i = 0; i < smaller; i++) {
        if (a[i] != match[i]) break;
        prefix++;
    }

    // if they're equal
    if (prefix == smaller) return true;

    int suffix = 0;
    for (int slen = 1; slen <= smaller; slen++) {
        int i_match = match.length() - slen;
        int i_a = a.length() - slen;
        if (a[i_a] != match[i_match]) break;
        suffix++;
    }

    // remove single character
    if (a.length() == match.length() - 1 && prefix + suffix + 1 >= match.length()) return true;
    // add single character
    if (a.length() == match.length() + 1 && prefix + suffix >= match.length()) return true;
    // change single character
    if (a.length() == match.length() && prefix + suffix + 1 >= match.length()) return true;

    return false;
}

int main(void) {
    cin >> N >> match;
    S.resize(N);
    for (int i = 0; i < N; i++) cin >> S[i];

    int total = 0;
    vector<int> ok;
    ok.reserve(N + 1);

    for (int i = 0; i < N; i++) {
        if (is_eq(S[i])) {
            total++;
            ok.push_back(i + 1);
        }
    }

    cout << total << endl;
    for (int x: ok) cout << x << " ";
    cout << endl;
}