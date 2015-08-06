
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

const int MN = 100111;
int a[MN];

int main() {
    ios :: sync_with_stdio(false);
    int n, k;
    while (cin >> n >> k) {
        int pieces = 0;
        int res = 0, chain = 0;
        FOR(i,1,k) {
            int len; cin >> len;
            FOR(i,1,len) cin >> a[i];
            a[len+1] = 0;
            if (a[1] == 1) {
                chain = 1;
                while (a[chain+1] == chain + 1) ++chain;

                pieces += len - chain + 1;
                res += len - chain;
            }
            else {
                pieces += len;
                res += len - 1;
            }
        }
        res += pieces - 1;
        cout << res << endl;
    }
}

