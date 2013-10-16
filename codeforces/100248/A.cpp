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

int n;
int x[11];
int d[1211], qu[1211], first, last;

int main()
{
//    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        FOR(i,1,6) cin >> x[i];
        
        memset(d, -1, sizeof d);
        first = last = 1; qu[1] = 600; d[600] = 0;
        
        while (first <= last) {
            int u = qu[first++];
            FOR(i,1,6) {
                int v = u - x[i];
                if (v >= 0 && d[v] < 0) d[v] = d[u] + 1, qu[++last] = v;
                
                v = u + x[i];
                if (v <= 1200 && d[v] < 0) d[v] = d[u] + 1, qu[++last] = v;
            }
        }
        
        int ln = 0, sum = 0;
        FOR(i,601,700) {
            ln = max(ln, d[i]);
            sum += d[i];
        }
        cout << (fixed) << setprecision(2) << sum / 100.0 << ' ' << ln << endl;
    }
    return 0;
}
