#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long i64;

int main(void) {
    i64 N; cin >> N;
    vector<pair<i64, int> > A(N + 1);

    i64 after_sum = 0;

    for (int i = 1; i <= N; i++) {
        cin >> A[i].first;
        A[i].second = i;

        after_sum += A[i].first;
    }
    sort(A.begin() + 1, A.end());

    vector<i64> res(N + 1);

    vector<int> all_with_same;
    for (int i = 1; i <= N; i++) {
        // printf("[i = %d] ", i);

        while (i + 1 <= N && A[i].first == A[i + 1].first) {
            all_with_same.push_back(A[i].second);
            i++;
        }
        all_with_same.push_back(A[i].second);

        after_sum -= all_with_same.size() * A[i].first;
        // printf("(%lld) ", after_sum);
        for (int x: all_with_same) {
            // printf("%d ", x);
            res[x] = after_sum;
        } 

        all_with_same.clear();
    }

    for (int i = 1; i <= N; i++) {
        cout << res[i] << " ";
    }
    cout << endl;
}

// 1 1 2 4 4

// 1 4 1 4 2