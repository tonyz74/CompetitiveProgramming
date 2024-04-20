#include <iostream>
#include <string>
#include <map>

using namespace std;

int main(void) {
    freopen("circlecross.in", "r", stdin);
    freopen("circlecross.out", "w", stdout);

    string S;
    cin >> S;

    map<char, int> start_pos;
    map<char, int> end_pos;

    for (int i = 0; i < (int) S.size(); i++) {
        if (start_pos[S[i]]) {
            end_pos[S[i]] = i + 1;
        } else {
            start_pos[S[i]] = i + 1;
        }
    }

    int total = 0;
    for (char cow1 = 'A'; cow1 <= 'Z'; cow1++) {
        for (char cow2 = 'A'; cow2 <= 'Z'; cow2++) {
            if (start_pos[cow2] > start_pos[cow1] && end_pos[cow1] < end_pos[cow2]
                && start_pos[cow2] < end_pos[cow1]) {
                total++;
            }
        }
    }

    cout << total << endl;
}