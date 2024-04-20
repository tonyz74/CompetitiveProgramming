#include <iostream>

using namespace std;

void solve() {
    string S; cin >> S;
    int N = (int) S.size();

    int min_ops = 1e9;
    for (int start = 0; start <= N - 3; start++) {
        // substring: [start, start + 3)
        string subst = S.substr(start, 3);
        // printf("substr: %s\n", subst.c_str());

        // will be impossible if like this
        if (subst[1] == 'M') continue;

        int expense = 0;
        // delete all from the sides, then change the two if necessary
        expense += start;                 // left side
        expense += (N - (start + 3));     // right side

        // printf("L: %d, R: %d\n", start, N - (start + 3));

        if (subst[0] == 'O') expense++;
        if (subst[2] == 'M') expense++;

        min_ops = min(min_ops, expense);
    }

    if (min_ops == 1e9) {
        printf("-1\n");
    } else {
        printf("%d\n", min_ops);
    }
}

int main(void) {
    int Q; cin >> Q;
    for (int i = 0; i < Q; i++) solve();
}