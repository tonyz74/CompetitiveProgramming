#include <iostream>
#include <vector>
#include <bitset>

using namespace std;

void print_as_bs(string prepend, int x) {
    cout << prepend << ": " << bitset<3>(x).to_string() << endl;
}

void solve() {
    int a, b, c, d, m;
    cin >> a >> b >> c >> d >> m;

    print_as_bs("a", a);
    print_as_bs("b", b);
    print_as_bs("c", c);
    print_as_bs("d", d);
    print_as_bs("m", m);
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}