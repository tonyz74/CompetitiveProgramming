
#include <iostream>
#include <vector>
#include <map>

#define C int(1e6+7)
#define el '\n'
#define pb push_back
using namespace std;
typedef long long ll;

//using freq is faster than unorder_map:v
int mp[C];
int main(){

    int n,k;cin>>n>>k;
    for(int i=1;i<=n;i++){
        int x;cin>>x;
        mp[x]++;
    }
    vector<int> res;
    int l=1,r=n;
    auto check = [&](int mid){
        int tt=0;
        for(int i=0;i<=2e5;i++)tt += mp[i]/mid;
        if(tt >= k)return true;
        return false;
    };  
    while(l<r){
        int mid = (l+r)/2;
        if(check(mid))l = mid+1;
        else r=mid;
    }

    cout << max(1, l - 1) << endl;
    for(int i=0;i<=2e5;i++){
        for(int d=1;d <= mp[i]/max(1,l-1) && (int) res.size()<k;d++)res.pb(i);
    }
    for(auto it:res)cout<<it<<' ';
    cout << endl;
}
