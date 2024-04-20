#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

#define MAX (1 << 10)

long long pows_10[] = {
    1,
    10,
    100,
    1000,
    10000,
    100000,
    1000000,
    10000000,
    100000000,
    1000000000,
    10000000000
};

int main(void) {
    int K;
    cin >> K;

    vector<long long> numbers;
    numbers.reserve(MAX + 1);

    for (int i = 1; i <= MAX; i++) {
        long long current = 0;

        int valid_n = 0;
        for (long long bit = 0; bit < 10; bit++) {
            if (i & (1 << bit)) {
                current += pows_10[valid_n++] * bit;
            }
        }

        if (current != 0) {
            numbers.push_back(current);
        }
    }

    sort(numbers.begin(), numbers.end());

    // for (int i = 0; i < 20; i++) {
    printf("%lld\n", numbers[K - 1]);
    // }
}