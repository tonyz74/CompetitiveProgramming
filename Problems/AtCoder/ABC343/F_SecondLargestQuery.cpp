#include <iostream>
#include <vector>
#include <set>

using namespace std;

#define MAX_N ((int) (2 * 1e5 + 4))

#define get_mid() ((h + t) / 2)

multiset<int> a[MAX_N * 4];
int state[MAX_N];

void build_tree(int x, int h, int t) {
    if (h == t) {
        a[x].insert(state[h]);
        return;
    }


}

int main(void) {

}