
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 1000111;

int d[MN];

int main() {
    ios :: sync_with_stdio(false);
    FOR(i,1,MN-1) {
        for(int j = i; j < MN; j += i)
            d[j]++;
    }
    int a, b, c;
    while (cin >> a >> b >> c) {
        int res = 0;
        int MOD = 1<<30;
        FOR(i,1,a) FOR(j,1,b) FOR(k,1,c)
            res = (res + d[i*j*k]) & (MOD - 1);
        cout << res << endl;
    }
}
