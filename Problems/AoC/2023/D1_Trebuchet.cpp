#include <iostream>
#include <vector>

using namespace std;

typedef long long i64;

int main(void) {
    string S;
    i64 total = 0;

    while (cin >> S) {
        int first = -1;
        int last = -1;

        for (char c: S) {
            if (isdigit(c)) {
                int d = c - '0';

                if (first == -1) first = d;
                last = d;
            }
        }

        total += (first * 10 + last);
    }

    cout << total << endl;
}