#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int n;
    cin >> n;

    int h;
    cin >> h;

    vector<int> f(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> f[i];
    }

    vector<int> d(n, 0);
    for (int i = 0; i < n; i++) {
        cin >> d[i];
    }

    vector<int> t(n - 1, 0);
    for (int i = 0; i < n - 1; i++) {
        cin >> t[i];
    }

    // Iterate through the possibilities for the pool he'll end at.
    // That way, we can greedily pick the best fish option at each
    // time period, knowing how much price he's paying for movement.
    //
    // We don't need to worry about order because we already know he will
    // definitely visit the N pools we found, so we're planning ahead of time
    // instead of simulating in his real time.

    for (int end_pool = 1; end_pool <= n; end_pool++) {
        int travel_cost = 0;

        for (int p = )
    }
}
