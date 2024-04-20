#include <iostream>
#include <vector>
#include <cassert>

using namespace std;

#define MAX_N ((long long) (2e5 + 5))
#define MAX_M ((long long) (2e5 + 5))
using i64 = long long;

i64 a[MAX_N] = {0};
i64 v[MAX_N * 4] = {0};
i64 lazy[MAX_N * 4] = {0};

#define get_mid() ((h + t) / 2)

void update(i64 x) {
    v[x] = v[x * 2] + v[x * 2 + 1];
}

void build_tree(i64 x, i64 h, i64 t) {
    if (x >= MAX_N * 4) return;
    if (h == t) {
        v[x] = a[h];
        return;
    }

    build_tree(x * 2, h, get_mid());
    build_tree(x * 2 + 1, get_mid() + 1, t);
    update(x);
}

void lazy_propagate(i64 x, i64 h, i64 t) {
    if (x >= MAX_N * 4) return;
    if (lazy[x] != 0) {
        lazy[x * 2] += lazy[x];
        lazy[x * 2 + 1] += lazy[x];

        // add the actual values to the v array
        v[x * 2] += (get_mid() - h + 1) * lazy[x];
        v[x * 2 + 1] += (t - get_mid()) * lazy[x];

        // DONT FORGET
        lazy[x] = 0;
    }
}

void update_range(i64 x, i64 h, i64 t, i64 h1, i64 t1, i64 k) {
    if (x >= MAX_N * 4) return;
    if (h1 <= h && t1 >= t) {
        v[x] += k * (t - h + 1);
        lazy[x] += k;
        return;
    }

    lazy_propagate(x, h, t);
    if (h1 <= get_mid()) update_range(x * 2, h, get_mid(), h1, t1, k);
    if (t1 > get_mid()) update_range(x * 2 + 1, get_mid() + 1, t, h1, t1, k);
    update(x);
}

i64 get_range_sum(i64 x, i64 h, i64 t, i64 h1, i64 t1) {
    if (x >= MAX_N * 4) return 0;
    if (h1 <= h && t1 >= t) {
        i64 result = v[x];
        return result;
    }

    lazy_propagate(x, h, t);
    i64 ans = 0;
    if (h1 <= get_mid()) ans += get_range_sum(x * 2, h, get_mid(), h1, t1);
    if (t1 > get_mid()) ans += get_range_sum(x * 2 + 1, get_mid() + 1, t, h1, t1);

    return ans;
}

i64 N, M;
i64 B[MAX_M];

int main(void) {
    cin >> N >> M;

    // I HAVE TO INDEX IN 1~N
    for (int i = 1; i <= N; i++) {
        cin >> a[i];
    }
    build_tree(1, 1, N); 

    for (int i = 1; i <= M; i++) {
        cin >> B[i];
        B[i] += 1;
    }

    for (int i = 1; i <= M; i++) {
        i64 pile_pos = B[i];

        i64 rem = get_range_sum(1, 1, N, pile_pos, pile_pos);
        update_range(1, 1, N, pile_pos, pile_pos, -rem);

        if (pile_pos != N) {
            i64 first_cycle_used = min(rem, N - pile_pos);
            if (first_cycle_used != 0) {
                update_range(1, 1, N, pile_pos + 1, pile_pos + first_cycle_used, 1);
            }
            rem -= first_cycle_used;
        }

        pile_pos = 1;
        i64 n_cycles = rem / N;
        i64 leftover = rem % N;

        if (n_cycles) {
            update_range(1, 1, N, 1, N, n_cycles);
        }
        if (leftover) {
            update_range(1, 1, N, 1, leftover, 1);
        }
    }

    for (int i = 1; i <= N; i++) {
        printf("%lld ", get_range_sum(1, 1, N, i, i));
    }
    printf("\n");

}