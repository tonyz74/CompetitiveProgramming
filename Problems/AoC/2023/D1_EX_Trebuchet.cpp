#include <iostream>
#include <string>
#include <string_view>

using namespace std;
typedef long long i64;

string matchings[10] = {
    "EMPTY",
    "one", "two", "three", "four", "five",
    "six", "seven", "eight", "nine"
};

int main(void) {
    i64 total = 0;

    string S;
    while (cin >> S) {
        string buf = "";

        i64 min_pos = 1e9;
        int first = 0;

        for (int d = 1; d <= 9; d++) {
            auto p_raw = S.find('0' + d);

            if (p_raw != string::npos && (i64) p_raw < min_pos) {
                min_pos = p_raw;
                first = d;
            }

            auto p_text = S.find(matchings[d]);
            if (p_text != string::npos && (i64) p_text < min_pos) {
                min_pos = p_text;
                first = d;
            }
        }

        i64 max_pos = -1;
        int last = 0;

        for (int d = 1; d <= 9; d++) {
            auto rp_raw = S.rfind('0' + d);

            if (rp_raw != string::npos && (i64) rp_raw > max_pos) {
                max_pos = rp_raw;
                last = d;
            }

            auto rp_text = S.rfind(matchings[d]);
            if (rp_text != string::npos && (i64) rp_text > max_pos) {
                max_pos = rp_text;
                last = d;
            }
        }

        total += first * 10 + last;
    }

    cout << total << endl;
}