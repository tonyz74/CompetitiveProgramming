#include <iostream>
#include <map>
#include <string>

using namespace std;

bool discontig_in(const string& haystack, const string& needle) {
    int ni = 0;

    for (int i = 0; i < (int) haystack.size(); i++) {
        if (toupper(haystack[i]) == needle[ni]) {
            ni++;
        }

        if (ni == (int) needle.size()) return true;
    }

    return false;
}

int main(void) {
    string S, T; cin >> S >> T;

    bool ok = false;
    string opt1 = T;
    ok |= discontig_in(S, opt1);

    if (T[2] == 'X') {
        string opt2 = string({T[0], T[1]});
        ok |= discontig_in(S, opt2);
    }

    if (ok) {
        printf("Yes\n");
    } else {
        printf("No\n");
    }
}