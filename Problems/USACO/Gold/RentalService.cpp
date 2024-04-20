#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

struct store {
    i64 unit_price;
    i64 quantity;

    bool operator<(const store& rhs) const {
        return unit_price < rhs.unit_price;
    }
};

int main(void) {
    freopen("rental.in", "r", stdin);
    freopen("rental.out", "w", stdout);

    i64 N; cin >> N;
    i64 M; cin >> M;
    i64 R; cin >> R;

    vector<i64> cows(N + 1);
    vector<store> stores(M + 1);
    vector<i64> rent(R + 1);

    for (i64 i = 1; i <= N; i++) cin >> cows[i];
    for (i64 i = 1; i <= M; i++) cin >> stores[i].quantity >> stores[i].unit_price;
    for (i64 i = 1; i <= R; i++) cin >> rent[i];

    // process high generating cows first
    std::sort(cows.begin() + 1, cows.end());
    std::reverse(cows.begin() + 1, cows.end());

    // prioritize high-selling stores first
    std::sort(stores.begin() + 1, stores.end());
    std::reverse(stores.begin() + 1, stores.end());

    // rent to high-paying farmers first
    std::sort(rent.begin() + 1, rent.end());
    std::reverse(rent.begin() + 1, rent.end());

    // PART 2: COMPUTING ANSWER
    
    // if we have n cows to rent, farmer price is fixed
    // so we enumerate the cows we're milking, and sell the rest

    vector<i64> rent_n(R + 1, 0);
    for (i64 i = 1; i <= R; i++) {
        rent_n[i] = rent_n[i - 1] + rent[i];
    }

    i64 store_i = 1;
    i64 selling_money = 0;

    i64 best = 0;

    for (i64 sold = 0; sold <= N; sold++) {
        // printf("[%lld]:\n", sold);
        // printf("%lld\n", cows[sold]);

        if (sold != 0) {
            while (cows[sold] != 0 && store_i != M + 1) {
                i64 to_sell = min(stores[store_i].quantity, cows[sold]);
                // printf("sold %lld to store with (%lld cents)\n", to_sell, stores[store_i].unit_price);
                selling_money += to_sell * stores[store_i].unit_price;
                stores[store_i].quantity -= to_sell;
                cows[sold] -= to_sell;

                if (stores[store_i].quantity == 0) store_i++;
            }
        }

        i64 renting_money = rent_n[min(max(N - sold, 0ll), R)];
        // printf("my value: %lld\n", renting_money + selling_money);
        best = max(renting_money + selling_money, best); 
    }

    cout << best << endl;
}