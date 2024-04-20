#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

map<string, int> zodiacs = {
    {"Ox", 0},
    {"Tiger", 1},
    {"Rabbit", 2},
    {"Dragon", 3},
    {"Snake", 4},
    {"Horse", 5},
    {"Goat", 6},
    {"Monkey", 7},
    {"Rooster", 8},
    {"Dog", 9},
    {"Pig", 10},
    {"Rat", 11}
};

int zodiac_to_yr_idx(string z) {
    for (auto x: zodiacs) {
        if (z == x.first) return x.second;
    }
    return 1e9;
}

struct info {
    int order;
    string dst;
    string src;
};

int main(void) {
    int N; cin >> N;

    set<string> known;
    map<string, int> yr_index;
    map<string, int> birth_year;

    vector<info> data(N);
    for (int i = 0; i < N; i++) {
        string first, last, rel, zod, trash;
        cin >> first >> trash >> trash >> rel >> zod >> trash >> trash >> last;

        data[i] = (info) {
            .order = (rel == "previous") ? -1 : 1,
            .dst = first,
            .src = last
        };

        yr_index[first] = zodiac_to_yr_idx(zod);
    }

    yr_index["Bessie"] = 0;
    birth_year["Bessie"] = 0;
    known.insert("Bessie");

    while (true) {
        bool done_anything = false;

        for (int i = 0; i < N; i++) {
            if (!known.count(data[i].src) || known.count(data[i].dst)) continue;

            int src_zod_n = yr_index[data[i].src];
            int dst_zod_n = yr_index[data[i].dst];

            int src_birth = birth_year[data[i].src];
            int diff = 0;

            if (data[i].order == -1) {
                // Before
                if (dst_zod_n < src_zod_n) {
                    diff = -(src_zod_n - dst_zod_n);
                } else {
                    diff = -((12 - dst_zod_n) + src_zod_n);
                }
            } else {
                // After
                diff = dst_zod_n - src_zod_n;
                if (diff <= 0) diff += 12;
            }

            // printf("setting %s's birth year to %s's (%d) + (%d) = %d\n",
            //     data[i].dst.c_str(), data[i].src.c_str(), src_birth, diff, src_birth + diff);
            known.insert(data[i].dst);
            birth_year[data[i].dst] = src_birth + diff;
            done_anything = true;
        }

        if (!done_anything) break;
    }
    
    cout << abs(birth_year["Elsie"]) << endl;
}
