#include <iostream>
#include <vector>

using namespace std;

template<typename K, typename V, typename hash_fn>
struct hashmap {
    vector<vector<pair<K, V> > > data;
    
    hashmap() {
        data.resize(1e5 + 7);
    }

    hashmap(int cap) {
        data.resize(cap);
    }

    void insert(K key, V value) {
        size_t hash = hash_fn()(key);
        int pos = hash % (data.size());
        data[pos].push_back(make_pair(key, value));
    }

    pair<K, V>* search(K key) {
        size_t hash = hash_fn()(key);
        int pos = hash % (data.size());

        for (int i = 0; i < int(data[pos].size()); i++) {
            if (data[pos][i].first == key) {
                return &data[pos][i];
            }
        }

        return nullptr;
    }
};