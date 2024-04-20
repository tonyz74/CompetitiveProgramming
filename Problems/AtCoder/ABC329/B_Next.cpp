#include <set>
#include <iostream>
#include <iterator>

using namespace std;

int main(void) {
    set<int> s;
    int N; cin >> N;
    for (int i = 0; i < N; i++) {
        int x; cin >> x;
        s.insert(x);
    }

    auto it = s.end();
    it--;
    it--;
    cout << *it << endl;
}