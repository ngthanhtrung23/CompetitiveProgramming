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
const ll oo = 1000111000111000111LL;

struct rec {
    ll a, b;
    int c;
    int index;
} a[55];

bool operator < (rec a, rec b) {
    return a.c < b.c;
}

int N, M, K;
ll f[55][55][111];
int tracej[55][55][111], tracek[55][55][111];

ll get(int i, int j, int k) {
    if (i == 1) return k + a[j].a;
    if (f[i][j][k] > -oo) return f[i][j][k];
    
    ll res = -oo + 1;
    
    FOR(jj,1,j) if (a[jj].c < a[j].c) {
        ll cur = a[j].a + k;
        if (cur >= K) {
            ll prev = cur - K - a[jj].a;
            if (prev >= 0 && prev <= a[jj].b - a[jj].a) {
                ll now = get(i-1, jj, prev) + cur;
                if (now > res) {
                    res = now;
                    tracej[i][j][k] = jj;
                    tracek[i][j][k] = prev;
                }
            }
        }
        if (cur % K == 0) {
            ll prev = cur / K - a[jj].a;
            if (prev >= 0 && prev <= a[jj].b - a[jj].a) {
                ll now = get(i-1, jj, prev) + cur;
                if (now > res) {
                    res = now;
                    tracej[i][j][k] = jj;
                    tracek[i][j][k] = prev;
                }
            }
        }
    }
    return f[i][j][k] = res;
}

void trace(int i, int j, int k) {
    if (i == 0) return ;
    trace(i-1, tracej[i][j][k], tracek[i][j][k]);
    cout << a[j].index << ' ' << a[j].a + k << endl;
}

int main() {
//    freopen("C.in", "r", stdin);
//    freopen("C.out", "w", stdout);
    cin >> N >> M >> K;
    FOR(i,1,M) {
        cin >> a[i].a >> a[i].b >> a[i].c;
        a[i].index = i;
    }
    sort(a+1, a+M+1);
    
    FOR(i,0,N) FOR(j,0,M) FOR(k,0,100) f[i][j][k] = -oo;
    
    ll res = -1;
    int savej, savek;
    FOR(j,1,M) FOR(k,0,(int) (a[j].b-a[j].a)) {
        ll cur = get(N, j, k);
        if (cur > res) {
            res = cur;
            savej = j;
            savek = k;
        }
    }
    if (res == -1) {
        puts("NO");
    }
    else {
        puts("YES");
        trace(N, savej, savek);
    }
    return 0;
}
