#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

typedef long long ll;

int n, k, p;

template<>
struct std::hash<pair<int, vector<int> > > {
     size_t operator()(const pair<int, vector<int>>& p) const {
        int a = p.first * 100000;

        int b = 0;
        int x = 1;
        for (int i = 0; i < p.second.size(); i++) {
            b += x * p.second[i];
            x *= 10;
        }

        return a + b;
    }
};

const int N = 105;
unordered_map<pair<int, vector<int> >, ll> M;
int a[N][6];
int value[N];

ll dfs(int x, vector<int> v, ll sum) {
    if (M[make_pair(x, v)]) return M[make_pair(x, v)] + sum;

    if (x == n + 1) {
        bool tt = 1;
        for (int i = 0; i < k; i++) {
            if (v[i] < p) tt = 0;
        }
        
        if (tt) return sum;
        return 1e18;
    }

    ll ans = dfs(x + 1, v, sum);
    vector<int> save = v;
    for (int i = 0; i < k; i++) {
        v[i] += a[x][i];
        v[i] = min(v[i], p);
    }

    ans = min(ans, dfs(x + 1, v, sum + value[x]));
    M[make_pair(x, save)] = ans - sum;

    return ans;
}

int main(void) {
    cin >> n >> k >> p;

    for (int i = 1; i <= n; i++) {
        cin >> value[i];
        for (int j = 0; j < k; j++) {
            cin >> a[i][j];
            a[i][j] = min(a[i][j], p);
        }
    }

    vector<int> v;
    for (int i = 0; i < k; i++) v.push_back(0);

    ll ans = dfs(1, v, 0);

    if (ans >= 1e17)
        cout << -1 << endl;
    else
        cout << ans << endl;
}
