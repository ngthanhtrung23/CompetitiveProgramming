
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

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("crypto.in", "r", stdin);
    freopen("crypto.out", "w", stdout);
    int n, a, b;
    while (cin >> n >> a >> b) {
        int res = -1, savex = 1, savey = 1;
        FOR(x,1,n) {
            for(int y = x; y > 0; y = x & (y - 1)) {
                int cur = (a*x + b*y) ^ (a*y + b*x);
                if (cur > res) {
                    res = cur;
                    savex = x;
                    savey = y;
                }
            }
        }
        cout << savex << ' ' << savey << endl;
    }
}
