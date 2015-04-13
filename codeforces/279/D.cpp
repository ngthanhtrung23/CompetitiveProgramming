
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

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

int n, a[111], f[TWO(23)], x[33];

int main() {
    while (cin >> n) {
        REP(i,n) cin >> a[i];
        if (n == 1) {
            cout << 1 << endl;
            continue;
        }
        int res = n+1;
        // f(S) = minimum number of variable, such that we can have set of variables S
        //        Note that when we have set S, we know that the last variable just created is the largest bit,
        //        and we must create the variable greater than it

        REP(S,TWO(n)) f[S] = n+1;
        f[1] = 1;

        FOR(S,1,TWO(n)-2) {
            int last = -1;
            FORD(i,n-1,0) if (CONTAIN(S,i)) { last = i; break; }

            int cur = f[S];
            if (last == n-1) {
                res = min(res, cur);
                continue;
            }

            int next = last + 1;
            bool ok = false;

            int nx = 0;
            REP(i,n) if (CONTAIN(S,i)) x[++nx] = a[i];
            sort(x+1, x+nx+1);
            int j = nx, i = 1;
            while (i <= j) {
                if (x[i] + x[j] == a[next]) {
                    ok = true;
                    break;
                }
                else if (x[i] + x[j] > a[next]) {
                    --j;
                }
                else ++i;
            }

            if (!ok) continue; // we cannot create the variable next

            // we add new variable to store next
            int S2 = S | TWO(next);
            f[S2] = min(f[S2], max(cur, __builtin_popcount(S2)));
            // we reuse existing variable to store next

            REP(i,n) if (CONTAIN(S,i)) {
                S2 = S - TWO(i) + TWO(next);
                f[S2] = min(f[S2], max(cur, __builtin_popcount(S2)));
            }
        }
        if (res > n) cout << -1 << endl;
        else cout << res << endl;
    }
    return 0;
}
