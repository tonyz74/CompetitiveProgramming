/// could have done this with 2p instead of linked list

#include <iostream>
#include <map>
#include <algorithm>
#include <vector>

using namespace std;

struct ll_node {
    int value = -1;
    ll_node* next = nullptr;
};

void ll_print(ll_node* head) {
    ll_node* now = head;
    while (now != nullptr) {
        printf("%d", now->value);
        if (now->next != nullptr) {
            printf(" ");
        }
        now = now->next;
    }
    printf("\n");
}

void solve() {
    map<int, ll_node*> nodes;
    ll_node* head = nullptr;
    ll_node* now = nullptr;

    int n, m; cin >> n >> m;
    for (int i = 0; i < n; i++) {
        int x; cin >> x;
        ll_node* append = new ll_node;
        append->value = x;

        if (now == nullptr) {
            head = append;
        } else {
            now->next = append;
        }
        now = append; 
        nodes[x] = append;
    }

    vector<int> to_insert;
    for (int i = 0; i < m; i++) {
        int x; cin >> x;
        to_insert.push_back(x);
    }

    std::sort(to_insert.begin(), to_insert.end());
    // std::reverse(to_insert.begin(), to_insert.end());

    // ll_print(head);

    for (int x: to_insert) {
        ll_node* insert = new ll_node;
        insert->value = x;

        // find first value greater than or equal to x
        auto ref = nodes.lower_bound(x);

        if (ref == nodes.end()) {
            // printf("%d go to front\n", x);
            // everybody is smaller than me, i should go to the front
            insert->next = head;
            head = insert;
        } else {
            // printf("put %d after %d\n", x, ref->second->value);
            insert->next = ref->second->next;
            // if (insert->next == nullptr) {
            //     printf("now insert is the end of list\n");
            // } else {
            //     printf("now insert points to %d\n", insert->next->value);
            // }
            ref->second->next = insert;
        }

        if (nodes.find(x) == nodes.end()) {
            nodes[x] = insert;
        }

        // ll_print(head);
    }

    ll_print(head);
}

int main(void) {
    int T; cin >> T;
    while (T--) solve();
}
