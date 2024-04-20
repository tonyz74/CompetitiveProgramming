#include <iostream>

using namespace std;

// comfortably 1e8 ops a second

char state[5001][20000];

int main(void) {
    long long total = 0;
    
    for (int i = 0; i <= 5000; i++) {
        for (int j = 0; j <= 20000; j++) {
            total += 5000 * i + j;
            state[i][j] = 'a' + total % 26;
        }
    }

    for (int i = 0; i < 5000; i++) {
        long long rsum = 0;
        for (int j = 0; j < 20000; j++) {
            rsum += (long long) state[i][j];
        }
        printf("%lld\n", rsum);
    }
}