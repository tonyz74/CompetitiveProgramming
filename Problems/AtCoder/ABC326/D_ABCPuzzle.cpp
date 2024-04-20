#include <iostream>
#include <string>
#include <set>

bool found = false;

using namespace std;

int chars_placed[256];
char state[6][6];

int N;
string R; string C;
string row_fmt;

atomic_bool check_ok() {
    // only need to check uniqueness in columns now
    for (int c = 1; c <= N; c++) {
        int cnt[256] = {0};

        for (int r = 1; r <= N; r++) {
            cnt[(int) state[r][c]]++;
        }

        int A = (int) 'A';
        int B = (int) 'B';
        int C = (int) 'C';
        if (cnt[A] != 1 || cnt[B] != 1 || cnt[C] != 1) return false;
    }

    return true;
}

void search(int current_row) {
    if (current_row == N + 1) {
        if (check_ok()) {
            found = true;
        }

        return;
    }

    if (found) return;

    char v[] = {'A', 'B', 'C'};

    // swap order, most important in front
    int important = R[current_row - 1] - 'A';
    std::swap(v[0], v[important]);

    string remaining = row_fmt;
    remaining.erase(remaining.find(v[0]), 1);

    int n_dots = N - 3;
    for (int pre_dots = 0; pre_dots <= n_dots; pre_dots++) {
        int pos = 1;

        for (int i = 0; i < pre_dots; i++) {
            state[current_row][pos++] = '.';
        }

        state[current_row][pos] = 'A' + v[0];

        string dup = remaining;

        // permute according to remaining
        int k = N - pre_dots - 1;

        printf("k = %d\n", k);
        do {
            int d = pos;
            for (int i = 0; i < k; i++) {
                state[current_row][d] = dup[i];

                // cannot use this branch; doesn't satisfy C condition
                if (!chars_placed[d] && dup[i] != C[d]) goto skip;

                chars_placed[d]++;
                d++;
            }

            search(current_row + 1);

            d = pos;
            for (int i = 0; i < k; i++) {
                chars_placed[d]--;
            }

            skip: (void) 0;

        } while (next_permutation(dup.begin(), dup.end()));

        // remove a dot (front)
        remaining = remaining.substr(1);
    }
}

int main(void) {
    cin >> N;
    cin >> R >> C;

    row_fmt = "ABC";
    while ((int) row_fmt.size() < N) row_fmt.push_back('.');
    sort(row_fmt.begin(), row_fmt.end());

    search(1);

    if (!found) {
        printf("No\n");
    } else {
        printf("Yes\n");
        for (int r = 1; r <= N; r++) {
            for (int c = 1; c <= N; c++) {
                if (state[r][c] == 0) putchar('.');
                else putchar(state[r][c]);
            }

            putchar('\n');
        }
    }
}