#include<cstdio>
#include<algorithm>
#include<cstring>
#include<vector> 
using namespace std;
typedef long long ll;

const int maxn = 100010;

int T, n, m;
int dp[maxn][2];

int h[maxn], cnt = 0;
struct E{
	int to, next;
}e[maxn << 1];
void add(int u, int v){
	e[++cnt].to = v;
	e[cnt].next = h[u];
	h[u] = cnt;
}

struct Node{
	int sum;
}t[2][maxn << 2];

struct Chain{
	int u, v, w;
}c[maxn];

int dep[maxn], sz[maxn], fa[maxn], son[maxn];
int top[maxn], st[maxn], dfn = 0;
vector<Chain> ch[maxn]; // 以 i 为 lca 的链的集合 

void dfs1(int u, int par){
    dep[u] = dep[par] + 1;
	sz[u] = 1;
	fa[u] = par;
    int maxson=-1;
	for(int i = h[u] ; i != -1 ; i = e[i].next){
		int v = e[i].to;
		if(v == par) continue;
		dfs1(v, u);
		sz[u] += sz[v];
		if(sz[v] > maxson){
			maxson = sz[v];
			son[u] = v;
		}
	}
}

void dfs2(int u, int tp){
	top[u] = tp;
	st[u] = ++dfn;
	if(!son[u]) return;
	
	dfs2(son[u], tp);
	for(int i = h[u] ; i != -1 ; i = e[i].next){
		int v = e[i].to;
		if(v == fa[u] || v == son[u]) continue;
		dfs2(v, v); 
	}
}

void pushup(int i, int P){
	t[P][i].sum = t[P][i << 1].sum + t[P][i << 1 | 1].sum;
}

void build(int i,int l,int r, int P){
    if (l==r){
        t[P][i].sum = dp[st[l]][P];
        return;
    }
    int mid = (l + r) >> 1;
    build(i << 1, l, mid, P);
    build(i << 1 | 1, mid + 1, r, P);
    pushup(i, P);
}

void modify(int i, int k, int l, int r, int p, int P){
	if(l == r){
		t[P][i].sum = k;
		return;
	}
    
    int mid = (l + r) >> 1;
    if(p <= mid) modify(i << 1, k, l, mid, p, P);
    else modify(i << 1 | 1, k, mid + 1, r, p, P);
    pushup(i, P);
}

int query(int i, int l, int r, int x, int y, int P){
    if (x <= l && r <= y){
        return t[P][i].sum;
    }
    
    int mid = (l + r) >> 1;
    int ans = 0;
    if(x <= mid) ans += query(i << 1, l, mid, x, y, P);
    if(y > mid) ans += query(i << 1 | 1, mid + 1, r, x, y, P);
    return ans;
}

int LCA(int u, int v){
	while(top[u] != top[v]){
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		u = fa[top[u]];
	}
	return dep[u] < dep[v] ? u : v;
}

int qry(int u, int v, int P){
	int ans = 0;
	while(top[u] != top[v]){
		if(dep[top[u]] < dep[top[v]]) swap(u, v);
		ans += query(1, 1, n, st[top[u]], st[u], P);
		u = fa[top[u]];
	}
	if(dep[u] > dep[v]) swap(u, v);
	ans += query(1, 1, n, st[u], st[v], P);
	return ans;
}

void dfs(int u, int par){
	dp[u][0] = dp[u][1] = 0;
	
	for(int i = h[u] ; i != -1 ; i = e[i].next){
		int v = e[i].to;
		if(v == par) continue;
		dfs(v, u);
		dp[u][0] += dp[v][1];
	}
	
	dp[u][1] = dp[u][0]; // 不选链 
	modify(1, dp[u][0], 1, n, st[u], 0);
	
	for(int i = 0 ; i < (int) ch[u].size() ; ++i){ // 选链 
		Chain no = ch[u][i];
		dp[u][1] = max(dp[u][1], qry(no.u, no.v, 0) - qry(no.u, no.v, 1) + no.w);
	} 
	
	modify(1, dp[u][1], 1, n, st[u], 1);
}

ll read(){ ll s = 0, f = 1; char ch = getchar(); while(ch < '0' || ch > '9'){ if(ch == '-') f = -1; ch = getchar(); } while(ch >= '0' && ch <= '9'){ s = s * 10 + ch - '0'; ch = getchar(); } return s * f; }

int main(){
	T = read();
	while(T--){
		memset(h, -1, sizeof(h)); cnt = 0;
		memset(son, 0, sizeof(son));
		memset(dp, 0, sizeof(dp));
		for(int i = 1 ; i <= n ; ++i) ch[i].clear(); 
		
		dfn = 0;
		
		n = read(), m = read();
		int u, v;
		for(int i = 1 ; i <= n - 1 ; ++i){
			u = read(), v = read();
			add(u, v); add(v, u);
		}
		
		dfs1(1, 0);
		dfs2(1, 1);		
		
		for(int i = 1 ; i <= m ; ++i){ 
			c[i].u = read(), c[i].v = read(), c[i].w = read(); 
			int lca = LCA(c[i].u, c[i].v);
			ch[lca].push_back(c[i]);
		}

		build(1, 1, n, 0);
		build(1, 1, n, 1);
		dfs(1, 0);
		
		printf("%d\n", dp[1][1]);
	}
	return 0;
}