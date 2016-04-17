
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

int GI(int& x) {
    return scanf("%lld", &x);
}

bool check(int a, int b, int u, int v, int x, int y) {
    return max(u, x) <= a && v + y <= b;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int a, b, u, v, x, y;
    while (cin >> a >> b >> u >> v >> x >> y) {
        bool can = false;
        REP(t1,2) {
            REP(t2,2) {
                REP(t3,2) {
                    if (check(a, b, u, v, x, y)) can = true;
                    swap(x, y);
                }
                swap(u, v);
            }
            swap(a, b);
        }
        cout << (can ? "YES" : "NO") << endl;
    }
}
