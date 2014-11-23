#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int cur;
bool c[1011][1011];
int x[33], y[33], z[33];

void connect(int target, int between) {
    FOR(i,1,between) z[i] = ++cur;
    z[between+1] = target;

    z[0] = 1;
    FOR(i,0,between) c[z[i]][z[i+1]] = true;
}

int main() {
    // ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        memset(c, 0, sizeof c);
        cur = 2;
        FOR(i,1,30) x[i] = ++cur;
        FOR(i,1,30) y[i] = ++cur;

        c[x[30]][2] = c[y[30]][2] = true;
        FOR(i,1,29) {
            c[x[i]][x[i+1]] = true;
            c[y[i]][y[i+1]] = true;
            c[y[i]][x[i+1]] = true;
            c[x[i]][y[i+1]] = true;
        }
        FORD(i,29,0) if ((1<<i) <= n) {
            n -= 1<<i;
            connect(x[30-i], 30-i-1);
        }
        cout << cur << endl;
        FOR(i,1,cur) {
            FOR(j,1,cur) if (c[i][j] || c[j][i]) putchar('Y');
            else putchar('N');
            puts("");
        }
    }
    return 0;
}