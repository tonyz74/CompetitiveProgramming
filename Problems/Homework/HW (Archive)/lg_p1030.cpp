#include <iostream>
#include <string>
#include <string_view>

using namespace std;

struct tnode {
    char value;
    tnode *left = nullptr;
    tnode *right = nullptr;
};

tnode * make_tree(string_view mid, string_view back) {
    // cout << "mid: " << mid << ", back: " << back << endl;

    if (mid.length() == 0) {
        return nullptr;
    }

    if (mid.length() == 1) {
        tnode *ret = new tnode;
        ret->value = mid[0];
        return ret;
    }

    char last = back[back.size() - 1];
    tnode *root = new tnode;
    root->value = last;

    int mid_root_index = -1;
    for (int i = 0; i < (int) mid.length(); i++) {
        if (mid[i] == last) {
            mid_root_index = i;
            break;
        }
    }
    // assert(mid_root_index != -1);

    string_view left_mid = mid.substr(0, mid_root_index);
    string_view right_mid = mid.substr(mid_root_index + 1);

    // this'll be what it is if there's nothing on the right
    string_view left_back = back.substr(0, back.length() - 1);
    string_view right_back;

    if (right_mid.length() != 0) {
        left_back = back.substr(0, left_mid.length());
        right_back = back.substr(left_mid.length());
        right_back = right_back.substr(0, right_back.length() - 1);
    }

    // cout << "with back value " << last << endl;
    // cout << left_mid << " " << right_mid << endl;
    // cout << left_back << " " << right_back << endl;

    root->left = make_tree(left_mid, left_back);
    root->right = make_tree(right_mid, right_back);

    return root;
}

void print_tree(tnode *node) {
    cout << node->value;

    if (node->left != nullptr) {
        print_tree(node->left);
    }
    if (node->right != nullptr) {
        print_tree(node->right);
    }
}

int main(void) {
    string mid, back;
    cin >> mid >> back;

    tnode * tree = make_tree(mid, back);
    print_tree(tree);
    cout << endl;
}