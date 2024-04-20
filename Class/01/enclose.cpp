#include <iostream>
#include <vector>

using namespace std;

int main() {
    cout.sync_with_stdio(false);
    cin.sync_with_stdio(false);

    int n, c, d;

    cin >> n;
    cin >> c;
    cin >> d;

    vector<pair<int, int> > data(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        cin >> a;
        cin >> b;
        data[i] = make_pair(a, b);
    }

    sort(data.begin(), data.end());

    int count = 0;
    int max_end = data[0].second;
    int target = c;
    int final = d;

    for (int i = 1; i < n; i++) {
        if (data[i].first > target) {
            if (data[i].first > max_end) {
                count = -1;
                break;
            }

            count++;
            target = max_end;
        }

        if (data[i].second > max_end) {
            max_end = data[i].second;
        }

        if (data[i].second > final) {
            count++;
            break;
        } 
    }

    cout << count << endl;
}
