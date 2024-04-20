#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

unordered_map<int, vector<int> > T;
unordered_set<string> combos;

void solve(string s, int i) {
    if (i >= s.length()) {
        combos.insert(s);
        return;
    }

    // change the character
    for (int new_val: T[s[i] - '0']) {
        string dup = s;
        dup[i] = new_val + '0';
        solve(dup, i);
    }

    // skip the character
    solve(s, i + 1);
}

int main(void) {
    string num;
    cin >> num;

    int N;
    cin >> N;

    for (int i = 0; i < N; i++) {
        int from, to;
        cin >> from >> to;
        T[from].push_back(to);
    }

    solve(num, 0);

    // for (string s: combos) {
    //     cout << s << endl;
    // }
    cout << combos.size() << endl;
}