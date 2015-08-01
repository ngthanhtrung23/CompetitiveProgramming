
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
using namespace std;

const int MN = 1000111;
bool mark[MN];
int n, a[MN];

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        FOR(i,1,n) cin >> a[i];
        memset(mark, false, sizeof mark);

        FOR(i,1,n) FOR(j,i+1,n) {
            mark[abs(a[i] - a[j])] = true;
        }

        FOR(res,1,1000000) {
            bool ok = true;
            for(int j = res; j < MN; j += res)
                if (mark[j]) {
                    ok = false;
                    break;
                }
            if (ok) {
                cout << res << endl;
                break;
            }
        }
    }
}
