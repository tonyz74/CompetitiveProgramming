#include <iostream>
#include <cmath>

using namespace std;

void solve() {
    int a, b, c;
    cin >> a >> b >> c;

    float average = ((float) (a + b)) / 2;
    
    int bigger = a;
    int smaller = b;
    if (a < b) {
        smaller = a;
        bigger = b;
    }

    float diff = (float) bigger - average;
    float max_each_time = (float) c;

    printf("%d\n", (int) ceil(diff / max_each_time));
}

int main(void) {
    int T;
    cin >> T;

    for (int i = 0; i < T; i++) {
        solve();
    }
}