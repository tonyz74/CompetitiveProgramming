#include <iostream>

using namespace std;
#define rep(i,h,t) for (int i=h;i<=t;i++)
#define dep(i,t,h) for (int i=t;i>=h;i--)
#define int long long
#define ll long long
const int N=305;
const int mo=1e9+7; 
int a[N],n;
int C[N][N],ans[N][N];
int dp[N][20][20][2][2];
ll fsp(int x,int y)
{
    if (y==0) return 1;
    if (y==1) return x;
    ll ans=fsp(x,y/2);
    ans=ans*ans%mo;
    if (y%2==1) ans=ans*x%mo;
    return ans; 
}
int ss[20];
void solve(int x)
{
 int tt=0; int xx=x;
 while (xx>0)
 {
  ss[++tt]=xx%10; xx/=10;
 }
 reverse(ss+1,ss+tt+1);
 rep(i,1,n)
   rep(j,i,n)
   {
    rep(k,0,min(j-i+1,tt-1)) (ans[i][j]+=C[j-i+1][k]*fsp(2,k)%mo)%=mo; 
   }

 rep(j,1,n)
 {
   memset(dp,0,sizeof(dp));
   dp[j+1][0][0][0][0]=1;
   dep(i,j,1)
   {
    rep(i1,0,tt)
      rep(i2,0,tt-i1)
        rep(i3,0,1)
          rep(i4,0,1)
          {
           (dp[i][i1][i2][i3][i4]+=dp[i+1][i1][i2][i3][i4])%=mo;
           if (i3==1||ss[i1+1]>=a[i])
           {
            int ii3=i3||(ss[i1+1]>a[i]);
            (dp[i][i1+1][i2][ii3][i4]+=dp[i+1][i1][i2][i3][i4])%=mo;
           }
           int ii4=(ss[tt-i2]>a[i])||((ss[tt-i2]==a[i]&&!i4));
           ii4=!ii4;
           (dp[i][i1][i2+1][i3][ii4]+=dp[i+1][i1][i2][i3][i4])%=mo;
     }
  rep(i1,0,tt)
  {
   int i2=tt-i1;
   rep(i3,0,1)
     rep(i4,0,1)
       if (i3||!i4) (ans[i][j]+=dp[i][i1][i2][i3][i4])%=mo;
  }
      }
    }
}
signed main()
{
 ios::sync_with_stdio(false);
 int A,B;
 cin>>n>>A>>B;
 rep(i,0,n)
 {
   C[i][0]=1;
   rep(j,1,i) C[i][j]=(C[i-1][j]+C[i-1][j-1])%mo;
    }
 rep(i,1,n) cin>>a[i];
 solve(A-1);

 rep(i,1,n)
   rep(j,i,n) ans[i][j]=-ans[i][j];
 solve(B);

  for (int i = 0; i <= 5; i++) {
    for (int j = 0; j <= 5; j++) {
      printf("%3lld ", ans[i][j]);
    }
    printf("\n");
  }
  return 0;


 int Q;
 cin>>Q;
 rep(i,1,Q)
 {
  int l,r;
  cin>>l>>r;
  cout<<ans[l][r]<<endl;
 }
 return 0; 
}