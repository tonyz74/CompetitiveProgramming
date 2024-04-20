#include <iostream>
#include <vector>
#include <string>
#include <limits.h>
#include <inttypes.h>

using namespace std;

typedef unsigned long long llu;

const int MAX_DIGITS = 32;

template<int MAX>
class bigint {
    public:

    // store in backwards order: 12345
    // is represented as {5,4,3,2,1}
    int data[MAX] = {0};
    int len = 0;

    bigint(const string& str) {
        for (int i = 0; i < str.length(); i++) {
            if (str[i] != '0') {
                len = str.length() - i;
                break;
            }
        }

        for (int i = 0; i < len; i++) {
            data[i] = str[str.length() - 1 - i] - '0';
        }
    }

    bigint(long long n) {
        len = 0;

        while (n > 0) {
            int rem = n % 10;
            n /= 10;
            data[len++] = rem;
        }
    }

    bigint operator+(const bigint& other) const {
        bigint result(0);

        int maxlen = max(len, other.len);
        
        int carry = 0;
        for (int i = 0; i < maxlen; i++) {
            int dig_sum = other.data[i] + data[i] + carry;
            carry = dig_sum / 10;
            result.data[result.len++] = dig_sum % 10;
        }
        
        if (carry) {
            result.data[result.len++] = carry;
        }

        return result;
    }

    bigint operator-(const bigint& other) const {
        bigint big = other;
        bigint small = *this;

        if (big < small) {
            bigint tmp = big;
            big = small;
            small = tmp;
        }

        int carry = 0;
        for (int i = 0; i < big.len; i++) {
            big.data[i] -= other.data[i]; 
        }

        for (int i = 0; i < big.len; i++) {
            if (big.data[i] < 0) {
                big.data[i] += 10;
                big.data[i + 1]--;
            }
        }

        for (int i = big.len - 1; i >= 0; i--) {
            if (big.data[i] != 0) {
                big.len = i + 1;
                break;
            } 
        }

        return big;
    }

    bigint operator*(const bigint& other) const {
        bigint result(0);

        // pick a digit
        for (int i = 0; i < len; i++) {
            // do multiplication by 1 digit
            for (int j = 0; j < other.len; j++) {
                // we normalize it later
                result.data[i + j] += (data[i] * other.data[j]);
            }
        }

        int combined = len + other.len;
        
        for (int i = 0; i < combined; i++) {
            result.data[i + 1] += result.data[i] / 10;
            result.data[i] %= 10;
        }

        for (int i = combined - 1; i >= 0; i--) {
            if (result.data[i] != 0) {
                result.len = i + 1;
                break;
            } 
        }

        return result;
    }

    bigint divmod(bigint n, bigint* rem) const {
        int taken = len - 1;
        bigint tmp(0);

        string s;

        while (taken >= 0) {
            tmp.prepend_digit(data[taken--]); 

            // valid tmp
            int mini_div = 0;
            while (tmp >= n) {
                mini_div++;
                tmp = tmp - n;
            }

            s += '0' + mini_div;
        }

        if (rem != nullptr) {
            *rem = tmp;
        }

        return bigint(s);
    }

    bigint operator/(bigint n) const {
        return divmod(n, nullptr); 
    }

    bigint operator%(bigint n) const {
        bigint rem(0);
        divmod(n, &rem);
        return rem;
    }

    bool operator>(const bigint& other) const {
        if (other.len < len) {
            return true;
        }

        for (int i = other.len - 1; i >= 0; i--) {
            if (other.data[i] > data[i]) {
                return false;
            } else if (other.data[i] < data[i]) {
                return true;
            }
        }

        return false;
    }


    bool operator==(const bigint& other) const {
        return !(*this > other) && !(other > *this);
    }

    bool operator!=(const bigint& other) const {
        return !(*this == other);
    }

    bool operator<(const bigint& other) const {
        return (other > (*this)) && (other != (*this));
    }

    bool operator>=(const bigint& other) const {
        return *this > other || *this == other; 
    }

    bool operator<=(const bigint& other) const {
        return *this < other || *this == other; 
    }

    void print() const {
        for (int i = len - 1; i >= 0; i--) {
            printf("%d", data[i]);
        } 
    }

    void prepend_digit(int d) {
        for (int i = len - 1; i >= 0; i--) {
            data[i + 1] = data[i];
        }

        len++;
        data[0] = d;
    }

    static bigint max_value() {
        string s;

        for (int i = 0; i < MAX; i++) {
            s.append("9");
        }

        return bigint(s);
    }
};

typedef bigint<32> bi32;

#define MAX_NODE 9

int main(void) {
    // Run Floyd-Warshall on the transformations, until you
    // know which transformations can get to which other
    // transformations. Then, multiply.

    string s;
    cin >> s;

    int N;
    cin >> N;

    vector<vector<int> > dis(MAX_NODE + 1, vector<int>(MAX_NODE + 1, 1e9));
    for (int i = 0; i < N; i++) {
        int from, to;
        cin >> from >> to;
        dis[from][to] = 1;
        dis[from][from] = 1;
        dis[to][to] = 1;
    }

    // Floyd-Warshall: all pairs
    for (int midp = 0; midp <= MAX_NODE; midp++) {
        for (int startp = 0; startp <= MAX_NODE; startp++) {
            for (int endp = 0; endp <= MAX_NODE; endp++) {
                if (dis[startp][endp] > dis[startp][midp] + dis[midp][endp]) {
                    dis[startp][endp] = dis[startp][midp] + dis[midp][endp];
                }
            }
        }
    }

    vector<int> trans_count(MAX_NODE + 1, 1);
    for (int from = 0; from <= MAX_NODE; from++) {
        for (int to = 0; to <= MAX_NODE; to++) {
            if (dis[from][to] != 1e9 && to != from) {
                trans_count[from]++;
            }
        }
    }

    bi32 total(1);
    for (int i = 0; i < s.length(); i++) {
        int digit = s[i] - '0';
        total = total * bi32(trans_count[digit]);
    }

    // for (int i = MAX_DIGITS - 1; i >= 0; i--) {
    //     printf("%d", total.data[i]);
    // }

    total.print();
    printf("\n");
    // cout << "total transitions: " << endl;
    // for (int i = 0; i < 10; i++) {
    //     cout << i << " -> " << trans_count[i] << endl;
    // }
}