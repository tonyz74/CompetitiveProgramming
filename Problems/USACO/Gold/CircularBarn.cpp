#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define MAX_A ((int) (5 * 1e6 + 4))
using i64 = long long;

bool table[MAX_A];
set<i64> primes_by_mod[4];

void sieve() {
    table[1] = true;
    primes_by_mod[1].insert(1);

    for (i64 i = 2; i < MAX_A; i++) {
        if (!table[i]) {
            // this value is prime
            primes_by_mod[i % 4].insert(i);

            i64 j = 1;
            while (i * j < MAX_A) {
                table[i * j] = true;
                j++;
            }
        }
    }
}

i64 biggest_lteq(const set<i64>& S, i64 x) {
    auto ub = S.upper_bound(x);
    // no element is greater than X
    if (ub == S.end()) {
        return *S.rbegin();
    }

    --ub;
    return *ub;    
}

// assuming the first player gets this quantity (will be a multiple of 4),
// how many moves will the game go on for? Just considering this room, imagine
// they always stay in the same place (1 room or something)
i64 moves_to_lose(i64 x) {
    // + 1 to do the actual loss
    return (2 * (x / 4)) + 1;
}

void solve() {
    int N; cin >> N;
    vector<int> a(N);
    for (int i = 0; i < N; i++) {
        cin >> a[i];
    }

    // each player makes N iterations (so * 2) until they're back
    // at the same room.
    i64 return_time = N * 2;

    // the number of iterations of the game (FJ and FN's moves are considered
    // two seperate iterations) for FJ to win or for FN to win.
    i64 FJ_min_win = 1e18;
    i64 FN_min_win = 1e18;

    for (int i = 0; i < N; i++) {
        i64 time_to_room = i * 2;

        // printf("room %d\n", i);

        if (a[i] % 4 == 0) {
            // this room is FJ's loss
            i64 loss_iters = moves_to_lose(a[i]);
            // 2 steps of the game goes by every time the two farmers reach this room,
            // they will have to cycle back here loss_iters / 2 times, and it costs
            // time_to_room to initially reach here, and it'll take loss_iters moves to
            // actually complete the move set.
            i64 loss_time = (loss_iters / 2) * return_time + time_to_room + loss_iters;
            // printf("fj loses in %lld iterations, which is %lld time\n", loss_iters, loss_time);
            FN_min_win = min(FN_min_win, loss_time);
        } else {
            // this room is FJ's win
            i64 largest_congruent = biggest_lteq(primes_by_mod[a[i] % 4], a[i]);
            i64 mult_4 = a[i] - largest_congruent;
            i64 win_iters = 1 + moves_to_lose(mult_4);
            i64 win_time = (win_iters / 2 - 1) * return_time + time_to_room + win_iters;
            // printf("(%d) %d => %lld, %lld, %lld\n", i, a[i], largest_congruent, win_time, win_iters);
            // printf("fj wins in %lld iterations (%lld), which is %lld time\n", win_iters, largest_congruent, win_time);
            FJ_min_win = min(FJ_min_win, win_time);
        }
    }

    // printf("%lld, %lld\n", FJ_min_win, FN_min_win);
    if (FJ_min_win < FN_min_win) {
        printf("Farmer John\n");
    } else {
        printf("Farmer Nhoj\n");
    }
}

int main(void) {
    sieve();
    int T; cin >> T;
    while (T--) solve();
}