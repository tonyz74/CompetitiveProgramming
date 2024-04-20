#include <iostream>
#include <string>
#include <string_view>

using namespace std;

bool is_palindrome(const string_view& sv) {
    int sz = sv.size();

    if (sz % 2 == 1) {
        // odd length
        int mid = sz / 2;
        for (int dist = 1; dist <= mid; dist++) {
            if (sv[mid - dist] != sv[mid + dist]) {
                return false;
            }
        }

        return true;
    } else {
        // even length
        int midl = sz / 2 - 1;
        int midr = midl + 1;

        if (sv[midl] != sv[midr]) {
            return false;
        }

        for (int dist = 1; dist <= midl; dist++) {
            if (sv[midl - dist] != sv[midr + dist]) {
                return false;
            }
        }

        return true;
    }
}

int main(void) {
    string S;
    cin >> S;

    // printf("%d\n", is_palindrome(S));

    // just brute force it, it's fine
    string_view sv = S;
    int max_len = 1;

    for (int i = 0; i < S.size(); i++) {
        for (int len = 1; i + len <= S.size(); len++) {
            string_view slice = sv.substr(i, len);
            if (is_palindrome(slice)) {
                max_len = max(max_len, (int) slice.length());
            }
        }
    }

    printf("%d\n", max_len);
}