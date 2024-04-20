#include <vector>
#include <ctgmath>

using namespace std;

void fail() {
    printf("-1\n");
    exit(0);
}


// Strategy: eat the things lowest on the pyramid first,
// as this will waste the least energy. As you incrementally
// go up the pyramid, if you meet one type who can't meet
// their quota, simply quit.

int main(void) {
    int N, T;
    scanf("%d %d", &N, &T);

    // As the quotas are all integers, 'valid situations' will all 
    // be integral, so there is no need for any floating point
    // until the very end.

    vector<int> E(N + 1);
    E[0] = T;

    int alive = 0;

    for (int i = 1; i < N + 1; i++) {
        int energy_demand;
        scanf("%d", &energy_demand);
        int lvl;
        scanf("%d", &lvl);

        int demand = energy_demand * 5;
        int accum = 0;

        for (int j = alive; j <= lvl; j++) {
            int gotten = min(E[j], demand - accum);
            E[j] -= gotten;
            accum += gotten;

            // Ran out of energy for this stock, no
            // need to look at it again in the future.
            if (E[j] == 0) {
                alive++;
            }

            if (accum >= demand) {
                break;
            }
        }

        E[i] = accum / 5;

        if (E[i] < (demand / 5)) {
            fail();
        }
    }

    double total = 0.0;
    for (int i = alive; i < N + 1; i++) {
        total += 0.2 * E[i];
    }
    printf("%lf\n", total);
}
