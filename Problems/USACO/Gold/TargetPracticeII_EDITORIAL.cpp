#include <iostream>
#include <vector>
#include <algorithm>
#include <ctgmath>

using namespace std;
const int N=1e6+10;
#define int long long
struct re{
	int X1,X2,Y1,Y2;
};
re ve[N];
int mx,mn,gg;
vector<int> v1,v2;
bool check1(vector<pair<int,int> > S, int x){
	vector<int> v;
	if (gg==-1){
		v=v2;
	} else v=v1;
	vector<int> q;
	for (auto v:S){
		q.push_back(floor((long double)1.0*(v.second-x)/v.first)); 
	}
	sort(q.begin(),q.end());
	sort(v.begin(),v.end());
	for (int i=0;i<(int)v.size();i++)
	  if (v[i]>q[i]) return 0;
	return 1;
}
bool check2(vector<pair<int,int> > S, int x){
	vector<int> v;
	if (gg==-1){
		v=v2;
	} else v=v1;
	vector<int> q;
	for (auto v:S){
		q.push_back(ceil((long double)1.0*(v.second-x)/v.first)); 
	}
	sort(q.begin(),q.end());
	sort(v.begin(),v.end());
	for (int i=0;i<(int)v.size();i++)
	  if (v[i]<q[i]) return 0;
	return 1;
}

void solve(vector<pair<int,int> > S,int g){
	gg=g;
	int h=-4e18,t=4e18;
	while (h<t){
		int mid=(h+t+1)/2;
		if (check1(S,mid)) h=mid;
		else t=mid-1;
	}
	mn=min(mn,h); 
	h=-4e18,t=4e18;
	while (h<t){
		int mid=(h+t)/2;
		if (mid<0) mid=(h+t-1)/2;
		if (check2(S,mid)) t=mid;
		else h=mid+1;
	}
	mx=max(mx,h);
}
signed main(){
	ios::sync_with_stdio(false);
	int T;
	cin>>T;
	while (T--){
		int n,X1,Y1,Y2,X2;
		cin>>n>>X1;
		vector<pair<int,int> > S1,S2;
		vector<int> jl;
		for (int i=1;i<=n;i++){
			cin>>Y1>>Y2>>X2;
			jl.push_back(Y1); jl.push_back(Y2);
			S1.push_back({X2,Y2});
			S2.push_back({X2,Y1});
		}
		v1.clear(); v2.clear();
		vector<int> ss;
		for (int i=1;i<=4*n;i++){
			int x;
			cin>>x;
			ss.push_back(abs(x));
			if (x>0) v1.push_back(x);
			else v2.push_back(x);
		}
		if ((int) v1.size()<n||(int) v2.size()<n){
			cout<<-1<<endl;
			continue;
		}
		int k=v1.size()-n;
		sort(jl.begin(),jl.end());
		reverse(jl.begin(),jl.end());
		for (int i=0;i<k;i++)
		  S2.push_back({X1,jl[i]});
		for (int i=k;i<(int) jl.size();i++)
		  S1.push_back({X1,jl[i]});
		mn=1e18;
		mx=0;
		sort(ss.begin(),ss.end());
		solve(S1,-1); 
		solve(S2,1);
		cout<<mx-mn<<endl;
	}
	return 0;
}
