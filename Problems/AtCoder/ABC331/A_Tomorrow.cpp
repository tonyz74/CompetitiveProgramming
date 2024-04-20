#include <iostream>

using namespace std;

int main(void) {
    int M; cin >> M;
    int D; cin >> D;

    int y, m, d; cin >> y >> m >> d;

    d++;
    if (d > D) {
        m++;
        d = 1;
    }

    if (m > M) {
        y++;
        m = 1; 
    }

    printf("%d %d %d\n", y, m, d);
}