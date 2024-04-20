#include <iostream>
#include <vector>
#include <string>
#include <array>

using namespace std;

struct bi200 {
    int data[205] = {0};
    int len = 0;

    bi200(const string& str) {
        for (int i = 0; i < (int) str.length(); i++) {
            if (str[i] != '0') {
                len = str.length() - i;
                break;
            }
        }

        for (int i = 0; i < len; i++) {
            data[i] = str[str.length() - 1 - i] - '0';
        }
    }

    void fix(int max_len) {
        for (int i = 0; i < max_len; i++) {
            if (data[i] >= 10) {
                data[i + 1] += data[i] / 10;
                data[i] %= 10;
            } 
            
            if (data[i] < 0) {
                int tens_needed = -data[i] / 10;
                if ((-data[i]) % 10 != 0) tens_needed++;

                data[i] += tens_needed * 10;
                data[i + 1] -= tens_needed;
            } 
        }

        for (int i = max_len - 1; i >= 0; i--) {
            if (data[i] != 0) {
                len = i + 1;
                break;
            } 
        }
    }

    void display() const {
        for (int i = len - 1; i >= 0; i--) {
            printf("%d", data[i]);
        }
        printf("\n");
    }
};

bool operator>(const bi200& lhs, const bi200& rhs) {
    if (lhs.len > rhs.len) return true;
    else if (lhs.len < rhs.len) return false;

    for (int i = lhs.len - 1; i >= 0; i--) {
        if (lhs.data[i] > rhs.data[i]) return true;
        else if (lhs.data[i] < rhs.data[i]) return false;
    }

    return false;
}

bi200 operator*(const bi200& lhs, const bi200& rhs) {
    bi200 result("0");

    // pick a digit
    for (int i = 0; i < lhs.len; i++) {
        // do multiplication by 1 digit
        for (int j = 0; j < rhs.len; j++) {
            // we normalize it later
            result.data[i + j] += (lhs.data[i] * rhs.data[j]);
        }
    }

    int combined = lhs.len + rhs.len;
    result.fix(combined);

    return result;
}

void solve() {
    string a_str, b_str; cin >> a_str >> b_str;
    bi200 a(a_str), b(b_str);

    int digits = a_str.size();
    bi200 prod = a * b;

    for (int swap = digits - 1; swap >= 0; swap--) {
        if (a.data[swap] == b.data[swap]) continue;
        
        std::swap(a.data[swap], b.data[swap]);

        // test the swap
        bi200 alt = prod;
        for (int i = 0; i < digits; i++) {
            if (i == swap) continue;
            alt.data[i + swap] += (a.data[swap] * b.data[i]);
            alt.data[i + swap] += (b.data[swap] * a.data[i]);

            alt.data[i + swap] -= (b.data[swap] * b.data[i]);
            alt.data[i + swap] -= (a.data[swap] * a.data[i]);
        }

        int len = digits * 2;
        alt.fix(len);

        if (alt > prod) {
            prod = alt;
        } else {
            std::swap(a.data[swap], b.data[swap]);
        }
    }

    a.display();
    b.display();
    // prod.display();
}

int main(void) {
    int t; cin >> t;
    while (t--) solve();
}