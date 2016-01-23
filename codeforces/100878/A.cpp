#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;
int n;
string a, b;
int f[MN], g[MN], nextDiff[MN], prevDiff[MN];

void init() {
    f[0] = 0;
    FOR(i,1,n) {
        f[i] = f[i-1];
        if (b[i] != b[i-1]) f[i]++;
    }

    g[n+1] = 0;
    FORD(i,n,1) {
        g[i] = g[i+1];
        if (b[i] != b[i+1]) g[i]++;
    }

    prevDiff[0] = 0;
    FOR(i,1,n) {
        if (a[i] != b[i]) prevDiff[i] = i;
        else prevDiff[i] = prevDiff[i-1];
    }

    nextDiff[n+1] = n+1;
    FORD(i,n,1) {
        if (a[i] != b[i]) nextDiff[i] = i;
        else nextDiff[i] = nextDiff[i+1];
    }
}

int solve() {
    init();

    int res = 1e9;
    FOR(i,0,n) {
        int t = 0;
        if (i > 0) t = max(t, f[prevDiff[i]]);
        if (i < n) t = max(t, g[nextDiff[i+1]]);

        res = min(res, t);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n >> a >> b;
        a = " " + a + " ";
        b = " " + b + " ";

        cout << "Case #" << test << ": " << solve() << endl;
    }
}
