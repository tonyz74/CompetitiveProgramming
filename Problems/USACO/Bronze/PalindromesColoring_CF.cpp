#include <iostream>
#include <map>

using namespace std;

void solve() {
    int n, k; cin >> n >> k;
    string S; cin >> S;

    map<char, int> n_occurences;
    for (char c: S) {
        n_occurences[c]++;
    }

    int n_pairs = 0;
    int n_singles = 0;
    for (pair<char, int> occurence: n_occurences) {
        n_pairs += occurence.second / 2;
        n_singles += occurence.second % 2;
    }

    int base_level = n_pairs / k;

    // convert the extra pairs to singles
    n_singles += 2 * (n_pairs % k);

    if (n_singles >= k) {
        cout << (base_level * 2) + 1 << endl;
    } else {
        cout << base_level * 2 << endl;
    }
}

int main(void) {
    int T; cin >> T;
    for (int i = 0; i < T; i++) solve();
}