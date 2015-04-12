
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 200111;

int n;
long long A, d[MN], sumd;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> A) {
        sumd = 0;
        FOR(i,1,n) {
            cin >> d[i];
            sumd += d[i];
        }
        FOR(i,1,n) {
            long long nn = n-1;
            long long ln = sumd - d[i];

            long long lb = max(1LL, A - ln);
            long long ub = min(d[i], A - nn);

            cout << (d[i] - (ub - lb + 1)) << ' ';
        }
        cout << endl;
    }
    return 0;
}
