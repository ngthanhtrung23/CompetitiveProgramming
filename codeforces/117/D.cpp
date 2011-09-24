#pragma comment(linker, "/STACK:16777216")
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>
#include <sstream>
#include <iomanip>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define unsigned long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define ll long long

//Buffer reading
int INP,AM;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (feof(stdin)) memset(BUF, 0, sizeof BUF); else fread(BUF,1,BUFSIZE,stdin); \
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}
//End of buffer reading

using namespace std;

const double PI = acos(-1.0);

ll n, m, mod;

ll getSize(ll a, ll b) {
    return (n-1 - b) / a + 1;
}

int get(ll a, ll b, ll i, ll j, ll u, ll v) {
    if (b > a) return 0;
    if (b > v) return 0;
    ll sz = getSize(a, b);
//    cout << a << ' ' << b << ' ' << sz << ' ' << i << ' ' << j << endl;
    if (sz == 0) return 0;
    if (i > sz) return 0;
    if (j < 1) return 0;
    if (i < 1) i = 1;
    if (j > sz) j = sz;
    
//    cout << a << ' ' << b << ' ' << sz << endl;
    
    if (sz == 1) {
//        cout << "Add2: " << a << ' ' << b << ' ' << i << ' ' << j << endl;
        if (b < n && u <= b && b <= v) return (b + 1) % mod;
        else return 0;
    }
    
    if (i == 1 && j >= sz) {
        if (u % a != b) {
            if (u % a < b) u += b - u % a;
            else u += (a - u % a) + b;
        }
        
        if (v % a != b) {
            if (v % a > b) v -= v%a - b;
            else v -= v % a + (a - b);
        }
        
//        cout << "Add: " << u << ' ' << v << ' ' << a << endl;
        
        if (u > v) return 0;
        
        ll sl = (v - u) / a + 1;
        
        ll x = v + u;
        ll y = sl;
        if (x % 2 == 0) x /= 2;
        else y /= 2;
        x %= mod;
        y %= mod;
        return (x*y + sl) % mod;
    }
    
    ll leftA = a << 1, leftB = b;
    ll rightA = a << 1, rightB = a + b;
    
    return (get(leftA, leftB, i, j, u, v) + 
            get(rightA, rightB, i - getSize(leftA, leftB), j - getSize(leftA, leftB), u, v)) % mod;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    GN(n); GN(m); GN(mod);
    while (m--) {
        ll i, j, u, v;
        GN(i); GN(j); GN(u); GN(v);
//        cin >> i >> j >> u >> v;
        u--; v--;
        if (u >= n) {
            puts("0");
            continue;
        }
        if (v >= n) {
            v = n - 1;
        }
        printf("%d\n", get(1LL, 0, i, j, u, v));
    }
    return 0;
}
