#include <iostream>
#include <vector>
#include <string>

using namespace std;

#define MAX_N ((int) (5 * 1e5) + 10)
#define MAX_VALUE MAX_N

vector<int> pre_b[MAX_N];
vector<int> suf_b[MAX_N];

vector<int> sorted_pre;
vector<int> sorted_suf;

int N;
string T;
string S[MAX_N];

int prefix_discontinuous(const string& s) {
    int pre = 0;
    for (unsigned i = 0; i < s.length(); i++) {
        if (pre - T.length() == 0) break;
        if (s[i] == T[pre]) pre++;
    }

    return pre;
}

int suffix_discontinuous(const string& s) {
    int suf = 0;
    for (unsigned diff = 1; diff <= s.length(); diff++) {
        if (T.length() - suf == 0) break;
        if (s[s.length() - diff] == T[T.length() - suf - 1]) suf++;
    }

    return suf;
}

int main(void) {
    sorted_pre.reserve(MAX_VALUE);
    sorted_suf.reserve(MAX_VALUE);

    cin >> N >> T;

    for (int i = 0; i < N; i++) {
        cin >> S[i];

        int pre = prefix_discontinuous(S[i]);
        int suf = suffix_discontinuous(S[i]);

        // cout << suf << " " << S[i] << " " << T <<  endl;

        pre_b[pre].push_back(pre);
        suf_b[suf].push_back(suf);
    }

    // do the sorting
    sorted_pre.push_back(-1e9);
    sorted_suf.push_back(-1e9);
    for (int i = 0; i < MAX_N; i++) {
        for (auto k: pre_b[i]) sorted_pre.push_back(k);
        for (auto k: suf_b[i]) sorted_suf.push_back(k);
    }

    // for (auto k: sorted_pre) cout << k << " ";
    // cout << endl;

    // for (auto k: sorted_suf) cout << k << " ";
    // cout << endl;

    // two pointers
    int right = sorted_suf.size() - 1;

    long long ok_cases = 0;
    for (int left = 1; left != (int) sorted_pre.size(); left++) {
        while (sorted_suf[right] + sorted_pre[left] >= ((int) T.length())) {
            right--;
        }
        ok_cases += (sorted_suf.size() - (right + 1));
    }

    cout << ok_cases << endl;
}