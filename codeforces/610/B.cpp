
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

const int MN = 200111;
int n, a[MN], f[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        int nn = *min_element(a+1, a+n+1);
        FOR(i,1,n) a[i] -= nn;

        FOR(start,1,n) if (a[start] == 0) {
            FORD(i,start,1) {
                if (a[i] == 0) f[i] = 0;
                else f[i] = f[i+1] + 1;
            }
            FORD(i,n,1) {
                if (a[i] == 0) f[i] = 0;
                else if (i == n) f[i] = f[1] + 1;
                else f[i] = f[i+1] + 1;
            }
            break;
        }

        ll res = nn * (ll) n + *max_element(f+1, f+n+1);
        cout << res << endl;
    }
}
