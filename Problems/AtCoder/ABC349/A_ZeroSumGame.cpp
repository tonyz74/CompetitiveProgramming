#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N; cin >> N;
    vector<int> A(N + 1);
    int s = 0;
    for (int i = 1; i <= N - 1; i++) {
        cin >> A[i];
        s += A[i];
    }

    printf("%d\n", -s);
}