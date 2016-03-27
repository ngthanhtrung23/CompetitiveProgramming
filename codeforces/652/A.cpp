
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

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int h1, h2, a, b;
    while (cin >> h1 >> h2 >> a >> b) {
        int can = 0;
        FOR(day,0,1000111) {
            if (day == 0) {
                h1 -= 4 * a;
            }
            h1 += 12 * a;
            if (h1 >= h2) {
                cout << day << endl;
                can = 1;
                break;
            }

            h1 -= 12 * b;
        }
        if (!can) cout << -1 << endl;
    }
}
