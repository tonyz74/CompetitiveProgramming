#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool intersecting(vector<pair<int, int>> &regions) {
    return whatever;
}

int main() {
    vector<pair<int, int>> A;
    A.push_back(make_pair(1, 4));
    A.push_back(make_pair(2, 5));
    A.push_back(make_pair(3, 8));
    A.push_back(make_pair(9, 11));

    int points = 0;

    sort(A.begin(), A.end());
    vector<pair<int, int>> current;
    int big_start = 0;
    int small_end = 0;
    current.push_back(A[0]);

    for (int i = 1; i < A.size(); i++) {
        current.push_back(A[i]);
        if (!intersecting(current) || i == A.size() - 1) {
            points++;
            current.clear();
            current.push_back(A[i]);
        }
    }

    cout << points << endl;
}
