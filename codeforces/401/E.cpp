#include<bits/stdc++.h>
#define MAX   200200
#define FOR(i,a,b) for (int i=(a);i<=(b);i=i+1)
#define FORD(i,b,a) for (int i=(b);i>=(a);i=i-1)
#define REP(i,n) for (int i=0;i<(n);i=i+1)
#define bit(x,i) ((x)&(1<<(i)))
using namespace std;
typedef long long ll;
const int INF=(int)1e9+7;
int prime[MAX];
int fls(ll x) {
    ll k=floor(sqrt(x));
    FOR(i,max(0LL,k-5),k+5) if (1LL*i*i>x) return (i-1);
}
int ces(ll x) {
    if (x<0) return (0);
    ll k=ceil(sqrt(x));
    FORD(i,k+5,max(0LL,k-5)) if (1LL*i*i<x) return (i+1);
}
int m,n,L,R,mod;
void eratosthene(void) {
    REP(i,2) prime[i]=-1;
    FOR(i,2,MAX-1) if (prime[i]==0)
        for (int j=2*i;j<MAX;j=j+i) prime[j]=i;
}
void anal(int x,vector<int> &v) {
    assert(0<x && x<MAX);
    v.clear();
    while (x>1) {
        if (prime[x]==0) {
            v.push_back(x);
            return;
        }
        int p=prime[x];
        assert(x%p==0);
        v.push_back(p);
        while (x%p==0) x=x/p;
    }
}
int countdiv(int x,int r) {
    if (r<x) return (0);
    int k=r/x;
    int tmp=(1LL*k*(n+1)-1LL*x*k*(k+1)/2)%mod;
    return ((tmp+mod)%mod);
}
int coprime(int x,int r) {
    if (r<=0) return (0);
    vector<int> div;
    anal(x,div);
    int res=0;
    REP(i,1<<div.size()) {
        int nb=0;
        int pro=1;
        REP(j,div.size()) if (bit(i,j)) {
            nb++;
            pro*=div[j];
        }
        if (nb%2==0) res=(res+countdiv(pro,r))%mod;
        else res=(res-countdiv(pro,r)+mod)%mod;
    }
    return (res);
}
int coprime(int x,int l,int r) {
    if (l>r) return (0);
    return ((coprime(x,r)-coprime(x,l-1)+mod)%mod);
}
void process(void) {
    cin >> m >> n >> L >> R >> mod;
    int res=(L==1)?((1LL*(m+1)*n+1LL*(n+1)*m)%mod):0;
    //printf("PRE %d\n",res);
    FOR(i,1,m) if (i<=R) {
        int l=max(1,ces(1LL*L*L-1LL*i*i));
        int r=min(n,fls(1LL*R*R-1LL*i*i));
        //printf("LIM %d %d\n",l,r);
        res=(res+2LL*(m-i+1)*coprime(i,l,r)%mod)%mod;
    }
    cout << res;
}
int main(void) {
#ifndef ONLINE_JUDGE
    freopen("tmp.txt","r",stdin);
#endif
    eratosthene();
    process();
    return 0;
}