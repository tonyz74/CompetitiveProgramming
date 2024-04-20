#include <iostream>

typedef long long ll;

using namespace std;

int main(void) {
    ll N; cin >> N;

    int num_twos = 0;
    while (N % 2 == 0) {
        N /= 2;
        num_twos++;
    }

    int num_threes = 0;
    while (N % 3 == 0) {
        N /= 3;
        num_threes++;
    }

    if (N == 1) cout << "Yes" << endl;
    else cout << "No" << endl;
}