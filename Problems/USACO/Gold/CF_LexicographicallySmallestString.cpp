#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

bool sort_special(const string& lhs, const string& rhs) {
    return lhs+rhs < rhs+lhs;
}

int main(void) {
    int N;
    cin >> N;

    int maxlen = 1;
    vector<string> strs(N);
    for (int i = 0; i < N; i++) {
        cin >> strs[i];
        maxlen = max(maxlen, (int) strs[i].size());
    }

    std::sort(strs.begin(), strs.end(), sort_special);

    string output;
    for (int i = 0; i < N; i++) {
        output += strs[i];
    }

    cout << output << endl;
}