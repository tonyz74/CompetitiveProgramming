#include <iostream>
#include <string>
#include <vector>

using namespace std;

using i64 = long long;

i64 N;
string S;
vector<i64> E;

int main(void) {
    cin >> N;
    cin >> S;
    S.insert(0, " ");

    E.resize(N + 1);

    for (i64 i = 1; i <= N; i++) {
        cin >> E[i];
    }

    pair<i64, i64> all_G_range = { -1, -1 };
    pair<i64, i64> all_H_range = { -1, -1 };

    for (i64 i = 1; i <= N; i++) {
        if (S[i] == 'G') {
            if (all_G_range.first == -1) all_G_range.first = i;
            all_G_range.second = i;
        } else if (S[i] == 'H') {
            if (all_H_range.first == -1) all_H_range.first = i;
            all_H_range.second = i;
        }
    }

    // if they are the independent leader, the first G and first H will take the role.
    bool G_only = E[all_G_range.first] >= all_G_range.second;
    bool H_only = E[all_H_range.first] >= all_H_range.second;

    i64 total_pairs = 0;

    // the two independent leaders together
    if (G_only && H_only) {
        total_pairs++;
    }

    if (G_only) {
        for (i64 i = 1; i < all_G_range.first; i++) {
            if (S[i] == 'H' && E[i] >= all_G_range.first) {
                // printf("%d and %d\n", i, all_G_range.first);
                total_pairs++;
            }
        }
    }

    if (H_only) {
        for (i64 i = 1; i < all_H_range.first; i++) {
            if (S[i] == 'G' && E[i] >= all_H_range.first) {
                // printf("%d and %d\n", i, all_H_range.first);
                total_pairs++;
            }
        }
    }

    // printf("current: %lld\n", total_pairs);

    if (G_only && H_only) {
        i64 G_end = E[all_G_range.first];
        i64 H_end = E[all_H_range.first];

        if ((all_G_range.first < all_H_range.first && G_end >= all_H_range.first) ||
            (all_H_range.first < all_G_range.first && H_end >= all_G_range.first)) {

            // double counted the two independent leaders

            // we only need to minus once because only one order
            // would work, as there's a before and after requirement
            // printf("doubled up\n");
            total_pairs--;
        }
    }

    cout << total_pairs << endl;
}