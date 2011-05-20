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
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

const double PI = acos(-1.0);
const int MN = 100111;

ll a[MN], b[MN], c[MN], d[MN];
int n;

inline ll getNum() {
    int x; scanf("%d", &x);
    return (ll) x;
}

void process(ll a[], ll b[], ll k, ll t) {
    ll now = 0, kk = k;
    int j = 0;
    
    FOR(i,1,n) {
        now = a[i];
        if (kk > 0) {
            kk--;
            b[i] = now + t;
        }
        else {
            j++;
            now = max(now, b[j]);
            b[i] = now + t;
        }
    }
}

ll k1, k2, k3, t1, t2, t3;

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    k1 = getNum(); k2 = getNum(); k3 = getNum();
    t1 = getNum(); t2 = getNum(); t3 = getNum();
    n = getNum();
    
    FOR(i,1,n) a[i] = getNum();
    
    process(a, b, k1, t1);
    process(b, c, k2, t2);
    process(c, d, k3, t3);
    
    ll res = 0;
    FOR(i,1,n) res = max(res, d[i] - a[i]);
    cout << res;
    return 0;
}
