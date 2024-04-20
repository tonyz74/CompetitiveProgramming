#include <iostream>
#include <algorithm>

using namespace std;


unsigned long long gcd(unsigned long long a, unsigned long long b) {
   if (b == 0)
   return a;
   return gcd(b, a % b);
}

unsigned long long lcm(unsigned long long a, unsigned long long b) {
    return (a * b) / gcd(a, b);
}

void solve() {
    int n, x, y;
    cin >> n >> x >> y;

    // put the biggest numbers on x, smallest numbers on y
    int pre_num_x = n / x;
    int pre_num_y = n / y;
    
    unsigned long long g = lcm(x, y);
    unsigned long long num_both = n / g;

    unsigned long long nx = pre_num_x - num_both;
    unsigned long long ny = pre_num_y - num_both;

    // printf("for n: %d, x: %d, y: %d, lcm = %d, nx = %d, ny = %d\n", n, x, y, g, nx, ny);

    // sum of last num_x1 numbers - sum of first num_y1 numbers
    unsigned long long plus = nx * n - ((nx * (nx - 1)) / 2);
    unsigned long long minus = ((ny * (ny + 1)) / 2);

    if (plus >= minus) {
        printf("%llu\n", plus - minus);
    } else {
        printf("-%llu\n", minus - plus);
    }
}

int main(void) {
    int T;
    cin >> T;
    for (int i = 0; i < T; i++) solve();
}