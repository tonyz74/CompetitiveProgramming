#include <iostream>
#include <vector>

using namespace std;

typedef long long ll;

vector<ll> words;
ll min_lines;

inline ll min_lines_for_width(ll W) {
    ll lines = 1;
    ll current = 0;
    ll i = 0;

    while (i < words.size()) {
        current += words[i];
        
        if (current > W) {
            current = words[i] + 1;
            lines++;
        } else {
            current++;
        }

        i++;
    }

    return lines;
}

ll find_result(ll left, ll right) {
    ll min_val = right;

    while (left < right) {
        ll mid = left + ((right - left) / 2);
        ll ml = min_lines_for_width(mid);

        // too bad, this one won't work, needs too many lines
        if (ml > min_lines) {
            left = mid + 1;
        }
        // this could potentially be improved by sliding left
        else {
            right = mid;
        }
    }

    return left;
}

int main(void) {
    ll sum = 0;
    int N;
    cin >> N;
    cin >> min_lines;
    ll max_word_size = 0;

    words.resize(N);
    for (int i = 0; i < N; i++) {
        cin >> words[i];
        sum += words[i];
        max_word_size = max(words[i], max_word_size);
    }
    sum += N + 1;

    // skip over impossible cases by starting at max word size,
    // otherwise my min_lines_.. func would infinite loop
    ll res = find_result(max_word_size, sum);
    cout << (res) << endl;
}