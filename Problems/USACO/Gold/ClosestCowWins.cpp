#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

using i64 = long long;

struct obj {
    i64 pos;
    i64 extra;

    bool operator<(const obj& rhs) const {
        return make_pair(pos, extra) < make_pair(rhs.pos, rhs.extra);
    }
};

struct region {
    vector<obj> grasses;
    i64 pre, post;
};

i64 K, M, N;
vector<obj> objs;

int main(void) {
    cin >> K >> M >> N; 
    for (i64 i = 0; i < K; i++) {
        obj item;
        cin >> item.pos;
        cin >> item.extra;
        objs.push_back(item);
    }

    for (i64 i = 0; i < M; i++) {
        obj nhoj_cow;
        cin >> nhoj_cow.pos;
        nhoj_cow.extra = -1;
        objs.push_back(nhoj_cow);
    }

    std::sort(objs.begin(), objs.end());


    // for (obj o: objs) {
    //     printf("[%lld].%lld ", o.pos, o.extra);
    // }
    // printf("\n");

    vector<i64> best_choices;

    region curr_reg;
    vector<region > contiguous_grass;
    for (i64 i = 0; i < M + K; i++) {
        if (objs[i].extra != -1) {
            curr_reg.grasses.push_back(objs[i]);
        }

        if (objs[i].extra == -1 || i == M + K - 1) {
            if (!curr_reg.grasses.empty()) {
                curr_reg.pre = i - curr_reg.grasses.size() - 1;
                curr_reg.post = (objs[i].extra == -1) ? i : -1;
                contiguous_grass.push_back(curr_reg);
            }
            curr_reg.grasses.clear();

        }
    }

    for (region v: contiguous_grass) {
        i64 sum = 0;
        for (obj o: v.grasses) {
            sum += o.extra;
        }

        if (v.pre == -1 || v.post == -1) {
            best_choices.push_back(sum);
        } else {

            // while there is a point such that i to p.x < i to L
            // and j to p.x < j to R, we accept this one

            // printf("{%lld} ", objs[v.pre].pos);
            // for (obj o: v.grasses) {
            //     printf("[%lld].%lld ", o.pos, o.extra);
            // }
            // printf("{%lld} ", objs[v.post].pos);
            // printf("\n");

            i64 G = v.grasses.size();

            i64 j = -1;
            i64 blk_sum = 0;
            i64 max_blk_sum = 0;
            vector<bool> seen(G, false);

            for (i64 i = 0; i < G; i++) {
                if (i != 0) {
                    blk_sum -= v.grasses[i - 1].extra;
                }

                if (j < i) {
                    j = i;
                    blk_sum += v.grasses[i].extra;
                }

                i64 dist_L = v.grasses[i].pos - objs[v.pre].pos;
                while (j != G - 1) {
                    i64 dist_R = objs[v.post].pos - v.grasses[j + 1].pos;
                    i64 pos_diff = v.grasses[j + 1].pos - v.grasses[i].pos;
                    if (dist_L + dist_R > pos_diff) {
                        blk_sum += v.grasses[j + 1].extra;
                        j++;
                    } else {
                        break;
                    }
                }

                max_blk_sum = max(max_blk_sum, blk_sum);
            }

            best_choices.push_back(max_blk_sum);
            best_choices.push_back(sum - max_blk_sum);
        }
    }

    std::sort(best_choices.begin(), best_choices.end());
    std::reverse(best_choices.begin(), best_choices.end());

    i64 res = 0;
    for (i64 i = 0; i < N && i < (i64) best_choices.size(); i++) {
        res += best_choices[i];
    }
    printf("%lld\n", res);
}