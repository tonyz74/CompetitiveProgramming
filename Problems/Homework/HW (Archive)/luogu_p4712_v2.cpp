#include <iostream>
#include <vector>
#include <ctgmath>

using namespace std;

void fail() {
    cout << -1 << endl;
    exit(0);
}

int main(void) {
    int N, T;
    cin >> N >> T;

    vector<double> E(N + 1);
    E[0] = T;
    int available = 0;

    for (int i = 1; i < N + 1; i++) {
        int energy_demand;
        cin >> energy_demand;
        int lvl;
        cin >> lvl;

        double demand = energy_demand;

        double accum = 0.0;

        for (int j = available; j <= lvl; j++) {
            double gotten = min(E[j], (demand * 5.0 - accum)); 
            E[j] -= gotten;
            accum += gotten;
            
            if (E[j] == 0.0) {
                available++;
            }

            if (accum >= demand * 5.0) {
                break;
            }
        }

        E[i] = accum * 0.2;

        if (E[i] < demand) {
            fail();
        }
    }

    double total = 0.0;
    for (int i = available; i < N + 1; i++) {
        total += 0.2 * E[i];
    }
    printf("%lf\n", total);
}
