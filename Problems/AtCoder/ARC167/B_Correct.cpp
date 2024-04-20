#include<iostream>
#include<vector>
#include<cmath>
using namespace std;
const long long modv = 998244353;
const long long halfconst = 499122177;
long long findans(long long a, long long b) {
    bool bOdd = b%2;
    b = b%modv;
    vector<long long> factors;
    for(long long i = 2; i <= sqrt(a)+5; i++) {
        long long cnt = 0;
        while(a%i == 0) {
            a /= i;
            cnt++;
        }
        if(cnt != 0) {
            factors.push_back(cnt%modv);
        }
    }
    if(a != 1) factors.push_back(1);
    long long ans = b;
    bool fEven = true;
    for(long long i = 0; i < factors.size(); i++) {
        if(factors[i]%2 == 1) fEven = false;
        ans = (ans*((((factors[i]*b)%modv)+((long long) 1))%modv))%modv;
    }
    if(fEven == false || bOdd == false) return ((((ans%modv)+modv)%modv)*halfconst)%modv;
    return (((((ans-1)%modv)+modv)%modv)*halfconst)%modv;
}
int main () {
    long long a,b;
    scanf("%lld%lld",&a,&b);
    printf("%lld\n",findans(a,b));
    return 0;
}