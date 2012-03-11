#include <iomanip>
#include <sstream>
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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

pair<int,int> x[1011], y[1011];
int nx, ny, px[1011], py[1011];
vector<int> kx[1011];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    int n, k;
    scanf("%d%d", &n, &k);
    FOR(i,1,n) {
        int c, t; scanf("%d%d", &c, &t);
        c *= 2;
        if (t == 1) x[++nx] = MP(c, i);
        else y[++ny] = MP(c, i);
    }
    sort(x+1, x+nx+1);
    sort(y+1, y+ny+1);
        
    int cur = k;
    FORD(i,nx,1) {
        kx[cur].PB(x[i].F);
        px[i] = cur;
        cur--; if (cur < 1) cur = 1;
    }
    FORD(i,ny,1) {
        kx[cur].PB(y[i].F);
        py[i] = cur;
        cur--; if (cur < 1) cur = 1;
    }
    
    ll sum = 0;
    FOR(i,1,k) {
        ll cur = 0;
        bool ok = false;
        FOR(x,1,nx) if (px[x] == i) ok = true;
        REP(x,kx[i].size()) cur += kx[i][x];
        sort(kx[i].begin(), kx[i].end());
        if (ok) cur -= kx[i][0] / 2;
        sum += cur;
    }
    
    cout << sum / 2 << '.' << ((sum % 2 == 0) ? 0 : 5) << endl;
    FOR(i,1,k) {
        int cnt = 0;
        FOR(u,1,nx) if (px[u] == i) cnt++;
        FOR(v,1,ny) if (py[v] == i) cnt++;
        printf("%d", cnt);
        FOR(u,1,nx) if (px[u] == i) printf(" %d", x[u].S);
        FOR(v,1,ny) if (py[v] == i) printf(" %d", y[v].S);
        puts("");
    }
    return 0;
}
