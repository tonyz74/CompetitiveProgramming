#include <iostream>
#include <vector>
#include <string>

using namespace std;

bool invalid_pairs[256][256];

int main(void) {
    ios::sync_with_stdio(false);

    string S, T; cin >> S >> T;

    // remember the pair with itself!!
    for (char c1 = 'a'; c1 <= 'r'; c1++) {
        for (char c2 = c1; c2 <= 'r'; c2++) {

            string Ss;
            string Tt;

            for (char c: S) if (c == c1 || c == c2) Ss.push_back(c);
            for (char c: T) if (c == c1 || c == c2) Tt.push_back(c);

            if (Ss != Tt) {
                invalid_pairs[(int) c1][(int) c2] = true;
                invalid_pairs[(int) c2][(int) c1] = true;
            }
        }
    }

    int Q; cin >> Q;
    for (int q = 0; q < Q; q++) {
        bool fail = false;
        string desc; cin >> desc;

        for (int i = 0; i < (int) desc.size(); i++) {
            for (int j = i; j < (int) desc.size(); j++) {
                if (invalid_pairs[(int) desc[i]][(int) desc[j]]) {
                    fail = true;
                    goto outer;
                }
            }
        }

        outer:
        if (fail) cout << "N";
        else cout << "Y";
    }

    cout << endl;
}