
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

const int MN = 155;

int x[MN], n;
int f[MN];

bool good(int n, int val) {
    FOR(i,1,n) if (__gcd(x[i], val) > 1) return false;
    return true;
}

void attempt(int i, int sum) {
    f[sum] += 1;

    int last = x[i-1];
    FOR(val,last+1,150-sum) if (good(i-1, val)) {
        x[i] = val;
        attempt(i+1, sum + val);
    }
}

void init() {
    x[0] = 1;
    attempt(1, 0);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("prime.in", "r", stdin);
    freopen("prime.out", "w", stdout);
    init();
    while (cin >> n) {
        ll res = 0;
        FOR(i,0,n) res += f[i];
        cout << res << endl;
    }
}
