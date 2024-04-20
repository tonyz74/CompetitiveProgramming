#include <iostream>
#include <set>
#include <vector>
#include <unordered_map>

using namespace std;

using p = pair<int, int>;

int main(void) {
    int N;
    cin >> N;

    vector<p> A(N + 1);
    unordered_map<int, int> n_seen_before;
    set<p> values;

    for (int i = 1; i <= N; i++) {
        cin >> A[i].first;
        A[i].second = n_seen_before[A[i].first];
        n_seen_before[A[i].first]++;
    }

    values.insert(A[1]);
    set<p>::iterator mid_ptr = values.begin();
    cout << A[1].first << endl;

    int sub = 0;

    for (int i = 2; i <= N; i++) {
        values.insert(A[i]);

        // get it back to its original position
        if (A[i] > (*mid_ptr)) {
            // median will have shifted right by one
            sub++;
        } else if (A[i] < (*mid_ptr)) {
            sub--;
        }

        // printf("\ninserted A[i]: %d\n", A[i]);
        // printf("after inserting, sub is %d, mid is %d\n", sub, *mid_ptr);

        if (sub == -2) {
            mid_ptr--;
            sub = 0;
        } else if (sub == 2) {
            sub = 0;
            mid_ptr++;
        }

        // printf("after some contemplation, mid is now %d\n", *mid_ptr);

        if (i % 2 == 1) {
            cout << (mid_ptr->first) << endl;
        }
    }
}