#include <iostream>
#include <vector>
#include <string_view>

using namespace std;

int K;
vector<int> words;

bool check(int width) {
    bool changed_line = 0;
    int lines = 1;
    int used = 0;
    int i = 0;

    while (i != (int) words.size()) {
        if (used + words[i] <= width) {
            changed_line = false;
            used += words[i];
            i++;
        } else {
            if (changed_line) return false;
            changed_line = true;
            used = 0;
            lines++;
        }
    }

    return lines <= K;
}

void read_in() {
    cin >> K;
    string S;
    while (cin >> S) {
        int V = 0;

        for (int i = 0; i < (int) S.size(); i++) {
            if (S[i] == '-') {
                words.push_back(V + 1);
                V = 0;
            } else {
                V++;
            }
        }

        words.push_back(V + 1);
    }

    words.back()--;
}

int main(void) {
    read_in();

    // for (int w: words) {
    //     printf("%d ", w);
    // }
    // printf("\n");

    int lo = 1, hi = 1e9;

    while (lo < hi) {
        int mid = (lo + hi) / 2;
        if (check(mid)) {
            hi = mid;
        } else {
            lo = mid + 1;
        }
    }

    printf("%d\n", lo);
}