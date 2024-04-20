#include <iostream>

using namespace std;

#define MAX_N 100

int main(void) {
    int N; cin >> N;
    long long S, M, L; cin >> S >> M >> L;

    long long best_price = 1e18;

    for (long long s = 0; s <= (MAX_N / 6) + 1; s++) {
        for (long long m = 0; m <= (MAX_N / 8) + 1; m++) {
            for (long long l = 0; l <= (MAX_N / 12) + 1; l++) {

                long long num_eggs = 6 * s + 8 * m + 12 * l;
                if (num_eggs >= (long long) N) {
                    long long price = s * S + m * M + l * L;
                    best_price = min(best_price, price);
                }
            }
        }
    }

    printf("%lld\n", best_price);
}