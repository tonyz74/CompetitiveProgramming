#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>

using namespace std;

#define MAX_A ((int) (3 * 1e5 + 2))

int n;
vector<int> a;

// 1 means it's not a prime
int check[MAX_A];

void sieve() {
    check[0] = 1;
    check[1] = 1;
    for (int i = 2; i < MAX_A; i++) {
        if (check[i] == 0) {
            for (int j = 1; i * j < MAX_A; j++) {
                check[i * j] = 1;
            }
            check[i] = 0;
        }
    }
}

#define SPIDER_NODE 1
#define FACTOR_NODE 2

int counter;

map<int, int> prime_to_node;
map<int, int> node_to_prime;

vector<vector<int> > graph;

void factorize(int X, int node) {
    if (X % 2 == 0) {
        while (X % 2 == 0) {
            X /= 2;
        }
        graph[node].push_back(prime_to_node[2]);
        graph[prime_to_node[2]].push_back(node);
    }

    for (int i = 3; i * i <= X; i += 2) {
        if (X % i == 0) {
            graph[node].push_back(prime_to_node[i]);
            graph[prime_to_node[i]].push_back(node);
            while (X % i == 0) {
                X /= i;
            }
        }
    }

    // remaining value, if it exists, will be a prime
    if (X != 1) {
        graph[node].push_back(prime_to_node[X]);
        graph[prime_to_node[X]].push_back(node);
    }
}

int main(void) {
    int n; cin >> n;

    int mx_a = 0;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        mx_a = max(mx_a, a[i]);
    }

    counter = n + 1;

    sieve();
    for (int i = 2; i <= mx_a; i++) {
        if (check[i] == 0) {
            prime_to_node[i] = counter;
            node_to_prime[counter] = i;
            counter++;
        }
    }
    graph.resize(counter);

    for (int i = 1; i <= n; i++) {
        factorize(a[i], i);
    }

    // for (int i = 1; i < counter; i++) {
    //     if (i <= n) {
    //         printf("[%d]: node (a[%d]) => %d, connects to: ", i, i, a[i]);
    //     } else {
    //         printf("[%d]: node (prime) => %d, connects to: ", i, node_to_prime[i]);
    //     }

    //     for (int x: graph[i]) {
    //         printf("%d ", x);
    //     }
    //     printf("\n");
    // }

    int s, t; cin >> s >> t;
    int max_node = counter - 1;
    vector<int> from(max_node + 1, -1);
    deque<pair<int, int> > dq;
    dq.push_back(make_pair(s, s));

    while (!dq.empty()) {
        pair<int, int> top = dq.front();
        dq.pop_front();
        if (from[top.first] != -1) {
            continue;
        }
        from[top.first] = top.second;

        for (int x: graph[top.first]) {
            if (from[x] == -1) {
                dq.push_back(make_pair(x, top.first));
            }
        }
    }

    if (from[t] == -1) {
        printf("%d\n", -1);
        return 0;
    }

    vector<int> path;
    int now = t;
    while (now != s) {
        path.push_back(now);
        now = from[now];
    }
    path.push_back(s);
    std::reverse(path.begin(), path.end());

    printf("%lu\n", path.size() / 2 + 1);
    int index = 0;
    for (int x: path) {
        if (index % 2 == 0) {
            printf("%d ", x);
        }
        index++;
    }
    printf("\n");
}