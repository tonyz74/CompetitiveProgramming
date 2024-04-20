#include <iostream>
#include <vector>
#include <string>
#include <cstdio>
#include <cstring>

using namespace std;

int char_counts[27];
int tmp_cc_1[27];
int tmp_cc_2[27];

int main(void) {
    freopen("blocks.in", "r", stdin);
    freopen("blocks.out", "w", stdout);

    int N; cin >> N;

    for (int i = 0; i < N; i++) {
        string S1, S2;
        cin >> S1 >> S2;

        memset(tmp_cc_1, 0, sizeof(tmp_cc_1));
        memset(tmp_cc_2, 0, sizeof(tmp_cc_1));

        for (char c: S1) tmp_cc_1[(int) c - 'a' + 1]++;
        for (char c: S2) tmp_cc_2[(int) c - 'a' + 1]++;

        for (int i = 1; i <= 26; i++) {
            char_counts[i] += max(tmp_cc_1[i], tmp_cc_2[i]);
        }
    }

    for (int i = 1; i <= 26; i++) cout << char_counts[i] << endl;
}