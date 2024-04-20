#include <iostream>
#include <algorithm>
#include <iterator>
#include <string>

using namespace std;

int main(void) {
    string S; cin >> S;
    sort(S.begin(), S.end());

    vector<string> vs;

    do {
        vs.push_back(S);
    } while (next_permutation(S.begin(), S.end()));

    printf("%d\n", (int) vs.size());
    for (int i = 0; i < (int) vs.size(); i++) {
        cout << vs[i] << endl;
    }
}