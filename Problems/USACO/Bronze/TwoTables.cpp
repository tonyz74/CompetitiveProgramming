#include <iostream>
#include <cstdio>

typedef long double lf;
typedef long long ll;

using namespace std;

struct rect {
    ll left, right, top, bottom;

    ll w() { return right - left; }
    ll h() { return top - bottom; }

    bool oob(ll W, ll H) {
        if (left < 0 || right > W || bottom < 0 || top > H) return true;
        return false;
    }

    bool has_ix(rect other) {
        if (other.left >= this->right ||
            other.bottom >= this->top ||
            other.top <= this->bottom ||
            other.right <= this->left) {
            // printf("saying no ix\n");
            return false;
        }

        return true;
    }
};

void read_rect(rect* r) {
    scanf("%lld %lld %lld %lld", &r->left, &r->bottom, &r->right, &r->top);
}

void solve() {
    int W, H; cin >> W >> H;
    rect table1; read_rect(&table1);
    int w, h; cin >> w >> h;

    // if just impossible
    if (table1.w() + w > W && table1.h() + h > H) {
        printf("-1\n");
        return;
    }

    ll best_cost = 1e18;

    // try to put in a corner
    int bl_pos[4][2] = {
        { 0, 0 }, { 0, H - h }, { W - w, 0 }, { W - w, H - h }
    };

    for (int i = 0; i < 4; i++) {
        rect table2;
        table2.left = bl_pos[i][0];
        table2.bottom = bl_pos[i][1];
        table2.right = table2.left + w;
        table2.top = table2.bottom + h;

        if (!table2.has_ix(table1)) {
            best_cost = 0;
            break;
        }

        // definitely will just move straight, so try up down left right
        ll changes[4][2] = {
            { 0, table2.top - table1.bottom },
            { table2.right - table1.left, 0 },
            { 0, table2.bottom - table1.top },
            { table2.left - table1.right, 0 }
        };

        for (int mod = 0; mod < 4; mod++) {
            rect t1_dup = table1;
            t1_dup.left += changes[mod][0];
            t1_dup.right += changes[mod][0];
            t1_dup.top += changes[mod][1];
            t1_dup.bottom += changes[mod][1];

            // printf("%lld %lld %lld %lld\n", t1_dup.left, t1_dup.bottom, t1_dup.right, t1_dup.top);

            if (t1_dup.oob(W, H)) {
                // printf("(i = %d) change %d was impossible\n", i, mod);
                continue;
            }
            ll x_chg = changes[mod][0] < 0 ? -changes[mod][0] : changes[mod][0];
            ll y_chg = changes[mod][1] < 0 ? -changes[mod][1] : changes[mod][1];

            best_cost = min(best_cost, max(x_chg, y_chg));
        }
    }

    printf("%Lf\n", (lf) best_cost);
}

int main(void) {
    int t;
    cin >> t;

    for (int i = 0; i < t; i++) solve();
}
