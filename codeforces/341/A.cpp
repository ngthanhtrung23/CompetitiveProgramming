#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <set>
#include <queue>
#include <map>
#include <string>
#include <cstring>
#include <ctime>
using namespace std;
#define For(i,a,b) for(int i=a;i<=b;i++)
#define Ford(i,a,b) for(int i=a;i>=b;i--)
#define Rep(i,c) for((type of c.begin()) i;i!=c.end();i++)
#define pb push_back
#define mp make_pair
#define fi first
#define se second
#define sr(x) (int)x.size()
#define modul 1000000007
#define nmax 100100
#define BUG(x) {cout << #x << " = " << x << endl;}
#define PR(x,a,b) {cout << #x << " = "; For(_,a,b) cout << x[_] << ' '; cout << endl;}
#define fillchar(x,a,b,delta) For(_,a,b) x[_]=delta;
#define Bit(s,i) ((s&(1<<i))>0)
#define Two(x) (1<<x)
#define pii pair<int,int>
#define ll long long
#define e 1e-6
#define PI acos(-1)
int n;
int a[nmax];
ll sum;
ll gcd(ll u,ll v) {
    if (v==0) return u;
    return gcd(v,u % v);
}
int main()
{
  //  freopen("codeforce.inp","r",stdin);
    scanf("%d",&n);
    For(i,1,n) scanf("%d",&a[i]);
    ll res=0;
    sort(a+1,a+n+1);
    sum=0;
    For(i,1,n) {
        res+=(ll)a[i]*(i-1) - sum;
        sum=sum+a[i];
    } 
    res*=2;
    For(i,1,n) res+=a[i];
    ll sol=gcd(res,n); 
    cout << res/sol << " " << n/sol;
    return 0;
}