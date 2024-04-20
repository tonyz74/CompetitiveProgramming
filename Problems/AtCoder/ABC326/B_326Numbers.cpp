#include <iostream>
#include <cmath>

using namespace std;

bool verify(int n) {
    int back = n % 10;
    n /= 10;

    int mid = n % 10;
    n /= 10;

    int front = n % 10;
    n /= 10;

    return front * mid == back;
}

int main(void) {
    int N; cin >> N;
    for (int i = N; i <= 919; i++) {
        if (verify(i)) {
            printf("%d\n", i);
            return 0;
        }
    }
}