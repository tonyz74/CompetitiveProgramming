#include <iostream>
#include <vector>

using namespace std;

enum class object : char {
    tree,
    hole,
    sprout
};

void print_state(const vector<object> &objs) {
    for (int i = 0; i < objs.size(); i++) {
        if (objs[i] == object::tree) cout << "T ";
        if (objs[i] == object::hole) cout << ". ";
        if (objs[i] == object::sprout) cout << "s ";
    }
    cout << endl;
}

int main(void) {
    int L, N;
    cin >> L >> N;

    vector<object> objs(L + 1, object::tree);

    long long sprouts_destroyed = 0;
    long long sprouts_existing = 0;

    // print_state(objs);

    for (int i = 0; i < N; i++) {

        int ty; cin >> ty;
        int l, r; cin >> l >> r;

        if (ty == 0) {
            for (int i = l; i <= r; i++) {
                if (objs[i] == object::tree) {
                    objs[i] = object::hole;
                }

                if (objs[i] == object::sprout) {
                    objs[i] = object::hole;
                    sprouts_destroyed++;
                    sprouts_existing--;
                }
            }
        } else {
            for (int i = l; i <= r; i++) {
                if (objs[i] == object::hole) {
                    objs[i] = object::sprout;
                    sprouts_existing++;
                }
            }
        }

        // print_state(objs);
    }

    cout << sprouts_existing << endl;
    cout << sprouts_destroyed << endl;
}