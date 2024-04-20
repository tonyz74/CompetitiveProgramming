#include <stdio.h>
#include <cstring>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#define WORD_SIZE 10
#define WORD_LIST_LENGTH 200

using namespace std;

int main(void) {
    vector<string> P;

    while (true) {
        string word;
        cin >> word;

        if (word == ".") {
            break;
        } else {
            P.push_back(word);
        }
    }
    
    string S;
    S.reserve(10 * 10 * 10 * 10 * 10);
    string tmp;

    while (cin >> tmp) {
        S.append(tmp);
    }


    // first check if it's at least one part exists,
    // if it doesn't even start with a valid value just
    // give up and say 0

    int ok = 0;
    for (int w = 0; w < (int) P.size(); w++) {
        if (memcmp(S.c_str(), P[w].c_str(), P[w].size()) == 0) {
            ok = 1;
            break;
        }
    }
    
    if (ok == 0) {
        printf("0\n");
        return 0;
    }

    // DP[i] -> max prefix with the string at length i
    vector<int> DP(S.length() + 1, 0);

    int best = 0;
    int first_valid_len = -1;


    for (int l = 1; l < (int) DP.size(); l++) {
        for (int w = 0; w < (int) P.size(); w++) {
            int wlen = P[w].length();
            int idx = l - wlen;
            if (idx >= 0) {
                if (first_valid_len == -1 || (idx < first_valid_len || DP[idx] != 0)) {
                    if (memcmp(P[w].c_str(), S.c_str() + idx, wlen) == 0) {
                        DP[l] = max(DP[l], DP[idx] + wlen);
                    }
                }
            }
        }

        if (DP[l] != 0 && first_valid_len == -1) {
            first_valid_len = l;
        }

        best = max(best, DP[l]);
    }

    // for (int i = 0; i < DP.size(); i++) {
    //     printf("%d ", DP[i]);
    // }

    printf("%d\n", best);
}
