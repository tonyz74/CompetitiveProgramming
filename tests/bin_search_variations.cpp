#include <iostream>

int main(void) {
    int lo = 0;
    int hi = 1e9;

    // find first true
    while (lo < hi) {
        int mid = (lo + hi) / 2;
    }

    // find last true
    while (lo < hi) {
        int mid = (lo + hi + 1) / 2;
    }

    // better way
    while (lo + 5 < hi) { 
    }
    vector<int> vec = {lo, lo + 1, ..., hi};
    int ans = max(func(vec[i]));
}