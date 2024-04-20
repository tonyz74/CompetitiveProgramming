#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

using alphabet = map<char, int>;

int main(void) {
    string S; cin >> S;
    vector<alphabet> pre(S.size() + 1);

    alphabet alpha;
    for (int i = 1; i <= (int) S.size(); i++) {
        char c = S[i - 1];
        alpha[c]++;
        pre[i] = alpha;
    }

    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) {
        int L, R; cin >> L >> R;

        // first two ways of constructing an irreducible anagram
        if (R == L || (S[R - 1] != S[L - 1])) {
            printf("Yes\n");
            continue;
        }

        alphabet start = pre[L - 1];
        alphabet my_chars = pre[R];

        for (auto p: start) {
            my_chars[p.first] -= p.second;

            if (my_chars[p.first] == 0) {
                my_chars.erase(p.first);
            }
        }

        if (my_chars.size() >= 3) {
            printf("Yes\n");
            continue;
        }

        printf("No\n");
    }
}