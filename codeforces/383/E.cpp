#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int a[TWO(24)];

void calc(int l, int r, int d) {
    if (d < 0) return ;

    calc(l, l + TWO(d), d-1);
    calc(l+TWO(d), r, d-1);

    REP(i,TWO(d))
        a[l + i + TWO(d)] += a[l + i];
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    int n;
    while (cin >> n) {
        memset(a, 0, sizeof a);
        FOR(i,1,n) {
            string s; cin >> s;
            int mask = 0;
            REP(t,3) mask |= TWO(s[t] - 'a');
            a[mask] += 1;
        }
        calc(0, TWO(24), 23);

        int res = 0;
        REP(i,TWO(24)) res ^= (n - a[i]) * (n - a[i]);
        cout << res << endl;
    }
    return 0;
}
