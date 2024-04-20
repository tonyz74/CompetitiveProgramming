#include <iostream>
#include <vector>

// easier methods of writing:
// compute the entire answer array for A - 1, then negate
// all of them, then just += the answers while computing for B
// do transitions in reverse, dp[i + 1] updates dp[i], and don't do the
// std::reverse() business and the N - r + 1 stuff.

using namespace std;

using i64 = long long;

i64 pt[302][302];

#define MAX_DIGITS 19

const i64 MODULUS = 1e9 + 7;

i64 answers[302][302];
i64 DP[MAX_DIGITS + 2][MAX_DIGITS + 2][2][3];

i64 N;
vector<int> a;

void clear_dp() {
    for (int i = 0; i < MAX_DIGITS + 2; i++) for (int j = 0; j < MAX_DIGITS + 2; j++)
    for (int s = 0; s < 2; s++) for (int o = 0; o < 3; o++) DP[i][j][s][o] = 0;
}

vector<i64> calculate_dp(i64 L, vector<int> max_val) {
    int n_digits = max_val.size() - 1;
    vector<i64> fn_answers;

    clear_dp();
    DP[0][0][0][1] = 1;

    // the dp only calculates the number of configs with the same
    // digits as max val, so we can use the binomial theorem to do
    // everything with less than that

    i64 combis = 0;

    for (int R = L; R <= N; R++) {
        int digit = a[R];

        for (int i = n_digits - 1; i >= 0; i--) for (int j = n_digits - 1; j >= 0; j--)
        for (int s = 0; s < 2; s++) for (int ord = 0; ord < 3; ord++) {
            i64 self = DP[i][j][s][ord];

            // put at front
            if (!(s == 0 && digit > max_val[i + 1])) {
                DP[i + 1][j][s | (digit < max_val[i + 1])][ord] += self;
                DP[i + 1][j][s | (digit < max_val[i + 1])][ord] %= MODULUS;
            }

            // put at back
            int jdx = (n_digits - j - 1);
            int new_ord = ord;
            if (digit > max_val[jdx]) new_ord = 2;
            else if (digit == max_val[jdx]) new_ord = ord;
            else if (digit < max_val[jdx]) new_ord = 0;

            DP[i][j + 1][s][new_ord] += self;
            DP[i][j + 1][s][new_ord] %= MODULUS;

        }

        // in between:
        // (n choose 1) * 2^1 + (n choose 2) * 2^2 + (n choose 3) * 2^3
        // + (n choose 4) * 2^4 ... + (n choose n) ^ 2^n
        // so this becomes 

        // calculate answer
        i64 ans = 0;

        for (int i = 0; i < MAX_DIGITS; i++) for (int j = 0; j < MAX_DIGITS; j++) {
            if (i + j != n_digits) continue; 

            ans += DP[i][j][1][0];
            ans += DP[i][j][1][1];
            ans += DP[i][j][1][2];

            ans += DP[i][j][0][0];
            ans += DP[i][j][0][1];

            ans %= MODULUS;
        }

        // FIXME: we need to choose lt_digits from (R - L + 1) at most,
        // and choose 1 from (R - L + 1) at least, and 2^x for how many
        // you're picking as you go through. It's not just binomial expansion.
        // Precompute pascal's triangle.
        i64 lt_digits = min((i64) n_digits - 1, (R - L + 1));
        combis += pt[(R - L + 1)][lt_digits];
        combis %= MODULUS;

        // i64 lt_digits = min((i64) n_digits - 1, R - L + 1);
        fn_answers.push_back((ans + combis) % MODULUS);
    }

    return fn_answers;
}

void get_pascals_triangle() {
    for (i64 row = 0; row < 302; row++) {
        pt[row][0] = 1;
        pt[row][row] = 1;

        for (int i = 1; i < row; i++) {
            pt[row][i] = pt[row - 1][i - 1] + pt[row - 1][i];
            pt[row][i] %= MODULUS;
        }
    }
}

int main(void) {
    cin >> N;
    i64 A, B; cin >> A >> B;

    a.resize(N + 1);
    for (int i = 1; i <= N; i++) cin >> a[i];
    std::reverse(a.begin() + 1, a.end());

    get_pascals_triangle();

    string small_str = to_string(A - 1);
    string B_str = to_string(B);
    vector<int> small_val;
    vector<int> B_val;

    small_val.push_back(-1);
    B_val.push_back(-1);
    
    for (char c: small_str) small_val.push_back(c - '0');
    for (char c: B_str) B_val.push_back(c - '0');

    for (int L = 1; L <= N; L++) {

        // valid states usually are 1, empty states are 0

        vector<i64> lte_B = calculate_dp(L, B_val);
        vector<i64> lt_A = calculate_dp(L, small_val);

        i64 i = 0;
        for (i64 R = L; R <= N; R++) {
            answers[L][R] = lte_B[i] - lt_A[i];
            i++;
        }
    }

    // 1 2 3
    // [13, 327]
    // 1. 

    i64 Q; cin >> Q;
    for (int q = 0; q < Q; q++) {
        i64 l, r; cin >> l >> r;
        printf("%lld\n", answers[N - r + 1][N - l + 1]);
    }
}