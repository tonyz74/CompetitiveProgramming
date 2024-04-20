#include <iostream>
#include <vector>
#include <string>
#include <map>

using namespace std;

int main(void) {
    string S; cin >> S;
    map<char, int> occ;
    map<int, vector<char> > occ_rev;
    for (int i = 0; i < (int) S.length(); i++) {
        occ[S[i]]++;
    }

    for (auto p: occ) {
        occ_rev[p.second].push_back(p.first);
    }

    for (auto p: occ_rev) {
        if (p.second.size() != 2) {
            printf("No\n");
            return 0;
        }
    }

    printf("Yes\n");
}