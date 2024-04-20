#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <tuple>

using namespace std;

typedef long long ll;
using p = tuple<ll, ll, ll>;

int N;

vector<p> TD;

int main(void) {
    cin >> N;
    TD.resize(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> get<0>(TD[i]) >> get<1>(TD[i]);
        get<1>(TD[i]) += get<0>(TD[i]);
        get<2>(TD[i]) = i;
    }

    // sort by increasing time for better simulation
    sort(TD.begin() + 1, TD.end());

    // begin simulation
    priority_queue<p, vector<p>, greater<p> > pq;

    ll time_counter = 0;
    ll sold = 0;

    // for (int i = 1; i <= N; i++) {
        // printf("%lld: start %lld, end %lld\n", get<2>(TD[i]), get<0>(TD[i]), get<1>(TD[i]));
    // }

    for (int i = 1; i <= N; i++) {
        time_counter = get<0>(TD[i]);

        // cout << "pushed " << get<2>(TD[i]) << " into pq" << endl;
        pq.push(make_tuple(get<1>(TD[i]), get<0>(TD[i]), get<2>(TD[i])));

        // as long as another event didn't happen
        bool necessary = (i + 1 != N + 1);
        while (!pq.empty() && ((!necessary) || (time_counter < get<0>(TD[i + 1])))) {
            // printf("top is (prod %lld (exit = %lld)), time is %lld\n", get<2>(pq.top()), get<0>(pq.top()),  time_counter);

            if (get<0>(pq.top()) >= time_counter) {
                // cout << "sold " << get<2>(pq.top()) << " at time " << time_counter << " (" << get<0>(pq.top()) << endl;
                sold++;
                time_counter++;
            }   
            pq.pop();
        }
    }

    cout << sold << endl;
}