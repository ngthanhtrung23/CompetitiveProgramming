#include <cmath>
#include <algorithm>
#include <vector>
#include <iostream>
#include <cstdio>
#include <complex>
#include <iomanip>
#include <cstring>
using namespace std;
#define For(i,a,b) for(int i=a;i<=b;i++)
#define FOR(i,a,b) for(int i=(a),_b=(b);i<=_b;i++)
#define Ford(i,a,b) for(int i=a;i>=b;i--)
#define fi first
#define se second
#define sr(x) (int)x.size()
#define BUG(x) {cout << #x << " = " << x << endl;}
#define PR(x,a,b) {cout << #x << " = "; For(_,a,b) cout << x[_] << ' '; cout << endl;}
#define Bit(s,i) ((s&(1<<i))>0)
#define Two(x) (1<<x)
const int modul = 1000000007;
const int nmax = 1000;
const double e = 1e-8;
const double pi = acos(-1);
typedef long long ll;
typedef pair<int,int> pii;

int a[111], price[111], n, f[111];

int main() {
//    freopen("input.txt", "r", stdin);
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n;
        FOR(i,1,n) {
            cin >> a[i] >> price[i];
            a[i] += a[i-1];
        }
        f[0] = 0;
        FOR(i,1,n) {
            f[i] = f[i-1] + price[i] * (a[i] - a[i-1] + 10);
            FOR(j,0,i-1)
                f[i] = min(f[i], f[j] + price[i] * (a[i] - a[j] + 10));
        }
        cout << f[n] << endl;
    }
}