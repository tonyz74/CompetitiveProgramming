#include <iostream>
#include <vector>
#include <string>
#include <cassert>

using namespace std;

bool cmp(pair<char, char> ab, pair<char, char> ba) {
    if (ab.first == ba.first && ab.second == ba.second) return true;
    if (ab.second == ba.first && ab.first == ba.second) return true;
    return false;
}

int main(void) {
    string S; cin >> S;
    int Q; cin >> Q;

    for (int q = 1; q <= Q; q++) {
        int l, r; cin >> l >> r;
        l--; r--;

        string qs;
        for (int i = l; i <= r; i++) {
            qs.push_back(S[i]);
        }

        while (qs.size() >= 2) {
            pair<char, char> back2 = make_pair(qs[qs.size() - 1], qs[qs.size() - 2]);
            qs.pop_back(); qs.pop_back();

            if (back2.first == back2.second) {
            } else if (cmp(back2, make_pair('C', 'O'))) {
                qs.push_back('W');
            } else if (cmp(back2, make_pair('O', 'W'))) {
                qs.push_back('C');
            } else if (cmp(back2, make_pair('C', 'W'))) {
                qs.push_back('O');
            } else {
                printf("huh?\n");
                assert(false);
            }
        }

        if (qs.size() == 0 || qs[0] != 'C') {
            printf("N");
        } else {
            printf("Y");
        }
    }
    printf("\n");
}