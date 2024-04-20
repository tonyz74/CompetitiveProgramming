#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <bitset>
#include <set>

#define DIM 200004

using bits = std::bitset<DIM>;

// optimizations
// 1. left shift and right shift can be replaced with
//    a saved version for both past shots and targets
// 2. replace lots of Fs in a row is basically just 3F s
// 3. replace lots of Ls in a row and an R in the middle as just
//    only some Ls
// 4. same for R
// 5. cut time in half by only iterating through half of commands,
//    and if the answer's correct just do that for those test cases
//    (hash & memory trick to identify)
// 6. cut DIM in half, because we can't actually reach 1e5 and -1e5

// O(N) method: split up into change operations, and then you
// only need to think of one change at a time (shifted)

using namespace std;

int main(void) {
    int T; cin >> T;
    int C; cin >> C;
    string commands;

    bits targets;
    bits future_shots;
    bits past_shots;

    vector<int> shots(2 * C + 1);
    vector<bool> has_target(2 * C + 1);

    vector<int> target_pos(T);
    for (int i = 0; i < T; i++) {
        cin >> target_pos[i];
        targets.set(target_pos[i] + C, true);
        has_target[target_pos[i] + C] = true;
    }

    cin >> commands;

    int pos = 0;
    vector<bool> new_hit_at(C + 1);

    for (int i = 0; i < C; i++) {
        char c = commands[i];

        if (c == 'F') {
            shots[pos + C]++;
            future_shots.set(pos + C, 1);

            if (has_target[pos + C] && shots[pos + C] == 1) {
                new_hit_at[i] = true;
            }
        }
        else if (c == 'L') pos--;
        else if (c == 'R') pos++;
    }

    int best_ans = (targets & future_shots).count();

    pos = 0;
    for (int i = 0; i < C; i++) {
        // change to L or R
        if (commands[i] == 'F') {
            bits dup = future_shots;

            // try replacing with R (right shift by one, minus one if this is a unique hit)
            int rshift_ans = 0;
            int lshift_ans = 0;

            // this place won't be a hit anymore
            if (new_hit_at[i]) {
                rshift_ans--;
                lshift_ans--;
            }

            dup >>= 1;
            rshift_ans += ((dup | past_shots) & targets).count();

            dup = future_shots;
            dup <<= 1;
            lshift_ans += ((dup | past_shots) & targets).count();

            best_ans = max(best_ans, lshift_ans);
            best_ans = max(best_ans, rshift_ans);

        } else if (commands[i] == 'L') {
            // switch to fire
            bits dup = future_shots;
            dup >>= 1;
            // i'm firing here after all
            dup.set(pos + C, 1);

            best_ans = max(best_ans, (int) ((dup | past_shots) & targets).count());

            // now for switching to right (rshift twice now)
            dup.set(pos + C, 0);
            dup >>= 1;
            best_ans = max(best_ans, (int) ((dup | past_shots) & targets).count());
        } else if (commands[i] == 'R') {
            
            // switch to fire
            bits dup = future_shots;
            dup <<= 1;
            dup.set(pos + C, 1);
            best_ans = max(best_ans, (int) ((dup | past_shots) & targets).count());

            dup.set(pos + C, 0);
            dup <<= 1;
            best_ans = max(best_ans, (int) ((dup | past_shots) & targets).count());
        }

        // go on, with no changes made
        if (commands[i] == 'R') pos++;
        else if (commands[i] == 'L') pos--;

        // remove this from future shots if there are no more
        // shots reaching this point
        if (commands[i] == 'F') {
            shots[pos + C]--;
            if (shots[pos + C] == 0) {
                future_shots.set(pos + C, 0);
            }
            past_shots.set(pos + C, 1);
        }
    }

    cout << best_ans << endl;
}