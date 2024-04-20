#include <iostream>

using namespace std;

#define MODULUS 998244353 

long long ways[5005] = {0};

int main(void) {
    int Q, K;
    cin >> Q >> K;

    ways[0] = 1;

    for (int i = 0; i < Q; i++) {
        char op;
        cin >> op;

        int X;
        cin >> X;

        if (op == '+') {
            for (int i = K; i >= 0; i--) {
                if (i - X >= 0) {
                    ways[i] += ways[i - X];
                    ways[i] %= MODULUS;
                }
            }
        } else {
            // think about "undoing" the operation.
            // we WANT the operation to cascade.
            for (int i = 0; i <= K; i++) {
                if (i - X >= 0) {
                    ways[i] -= ways[i - X];

                    ways[i] = (MODULUS + ways[i]);
                    ways[i] %= MODULUS;
                }
            }
        }

        // printf("%d\n", ways[K]);
        cout << ways[K] << endl;
    }
}