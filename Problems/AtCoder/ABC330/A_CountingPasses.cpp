#include <iostream>

using namespace std;
int main(void) {
    int N, L; cin >> N >> L;
    int passes = 0;
    for (int i = 0; i < N; i++) {
        int a; cin >> a;
        if (a >= L) passes++;
    }

    printf("%d\n", passes);
}