#include <iostream>
#include <vector>

using namespace std;

int main(void) {
    int N, M;
    cin >> N >> M;

    vector<int> days(M + 1, 0);
    for (int i = 1; i <= M; i++) {
        cin >> days[i];
    }

    int i = 1;
    for (int day = 1; day <= N; day++) {
        if (days[i] == day) {
            cout << 0 << endl;
            i++;
        } else {
            cout << days[i] - day << endl;
        }
    }
}