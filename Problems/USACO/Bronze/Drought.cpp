#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdlib>

using namespace std;

typedef long long i64;

i64 N;
vector<i64> H;

struct total {
    i64 sum;
    i64 x_coeff;

    total() {}

    total(i64 s, i64 xc): sum(s), x_coeff(xc) {
    }

    total operator+(const total& rhs) {
        total res(0, 0);
        res.sum = this->sum + rhs.sum;
        res.x_coeff = this->x_coeff + rhs.x_coeff;

        return res;
    }

    total operator-(const total& rhs) {
        return (*this) + (total((-rhs.sum), (-rhs.x_coeff)));
    }

    i64 eval_with_x(i64 x) {
        return sum + x_coeff * x;
    }
};

void print_total(const total& v) {
    printf("%lld", v.sum);

    if (v.x_coeff != 0) {
        if (v.x_coeff == -1) printf(" - x");
        else printf(" + x");
    }
}

void work(void) {
    i64 x_value = -1;

    cin >> N;
    H.resize(N);

    for (i64 i = 0; i < N; i++) cin >> H[i];

    vector<total> F(N);
    vector<total> upd_H(N);
    F[0] = total(H[0], -1);
    upd_H[0] = F[0];
    
    for (i64 i = 1; i < N; i++) {
        upd_H[i] = total(H[i], 0) - F[i - 1];
        total this_F = upd_H[i] - total(0, 1);
        F[i] = this_F;

        if ((F[i].x_coeff == 0 && F[i].sum < 0) ||
            (upd_H[i].x_coeff == 0 && upd_H[i].sum < 0)) {
            printf("-1\n");
            return;
        }
    }

    // for (i64 i = 0; i < N; i++) {
    //     printf("[i=%lld] steps: ", i);
    //     print_total(F[i]); 
    //     printf(", upd_H: ");
    //     print_total(upd_H[i]);
    //     printf("\n");
    // }

    if (N == 2) {

        if (H[0] == H[1]) {
            printf("0\n");
            return;
        } else {
            printf("-1\n");
            return;
        }

    } else if (N % 2 == 1) {
        total fin = upd_H[N - 1];
        // plug this in, if it works, great, otherwise this one failed
        x_value = fin.sum;
    } else {
        total fin = upd_H[N - 1];

        // the sum value should be 0, do some tests
        // to check, this is the equation that must be satisfied
        if (fin.sum != 0) {
            printf("-1\n");
            return;
        }

        // now, to minimize x, loop through the values
        i64 x_min = 1e9;

        for (i64 i = 0; i < N; i++) {
            x_min = min(x_min, H[i]);

            if (upd_H[i].x_coeff == 0) {
                x_min = min(x_min, upd_H[i].sum);
            }
        }

        if (x_min == 1e9) {
            exit(-9);
        }

        x_value = x_min;
    }

    i64 all_sum = 0;
    for (i64 i = 0; i < N; i++) {
        i64 eval = upd_H[i].eval_with_x(x_value);
        if (eval < 0) {
            printf("-1\n");
            return;
        }
        all_sum += H[i] - x_value;
    }

    printf("%lld\n", all_sum);
}

int main(void) {
    i64 T; cin >> T;
    for (i64 t = 0; t < T; t++) work();
}