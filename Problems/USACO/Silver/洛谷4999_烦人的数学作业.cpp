#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
using i64 = long long;

const i64 MODULUS = 1e9 + 7;

i64 fastpow(i64 x, i64 power) {
    i64 answer = 1;

    // x^12 = x^4 * x^8
    // effectively splitting into powers of two

    while (power != 0) {
        if (power % 2 == 1) {
            answer = answer * x;
            power -= 1;
        }

        x = x * x;
        x %= MODULUS;
        answer %= MODULUS;
        power /= 2;
    }

    return answer;
}

// x^(mod - 2) => the modular inverse of x under base mod
i64 modular_inverse(i64 x) {
    // compute x^(base - 2) % base
    return fastpow(x, MODULUS - 2);
}

string S;

i64 p10_table[20];
i64 inv10;

i64 pow10_mod(i64 power) {
    return p10_table[power];
}

pair<i64, i64> dfs(i64 x, bool smaller) {
    i64 n = 0;
    i64 digit_sum = 0;

    if (x == (i64) S.length()) {
        return make_pair(0, 1);
    }

    if (!smaller) {
        for (i64 digit = 0; digit <= S[x] - '0'; digit++) {
            bool lesser = (digit < (S[x] - '0'));
            auto next = dfs(x + 1, lesser);

            digit_sum += next.first;
            digit_sum += next.second * digit;
            digit_sum %= MODULUS;

            // printf("[%lld] %d: %lld\n", x, digit, digit_sum);

            n += next.second;
            n %= MODULUS;

        }
    } else {
        i64 digits_left = S.length() - x;
        n = pow10_mod(digits_left);

        digit_sum = (((n * inv10) % MODULUS) * digits_left * 45) % MODULUS;
    }

    return make_pair(digit_sum, n);
}

i64 solve(i64 R) {
    if (R <= 0) return 0;
    S = to_string(R);
    return dfs(0, false).first;
}

void testcase() {
    i64 L, R; cin >> L >> R;
    i64 final_ans = solve(R) - solve(L - 1);

    final_ans = ((final_ans % MODULUS) + MODULUS) % MODULUS;

    printf("%lld\n", final_ans);
}

int main(void) {
    i64 power = 1;
    for (i64 i = 0; i < 20; i++) {
        p10_table[i] = power;
        power *= 10;
        power %= MODULUS;
    }

    inv10 = modular_inverse(10);

    i64 T; cin >> T;
    for (i64 i = 0; i < T; i++) testcase();

}
