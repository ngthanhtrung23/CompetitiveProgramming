
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

const int MN = 100111;

int n, a[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);

        for(int val = 1, i = 1, j = n; i <= j; ++i, --j, ++val) {
            a[i] -= val;
            if (j != i) a[j] -= val;
        }
        int ln = 0;
        map<int,int> cnt;
        FOR(i,1,n) {
            cnt[a[i]]++;
            if (a[i] >= 0)
                ln = max(ln, cnt[a[i]]);
        }
        cout << n - ln << endl;
    }
}
