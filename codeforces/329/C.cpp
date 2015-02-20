
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

int a[100111];

int main() {
    int n, m;
    while (scanf("%d%d", &n, &m) == 2) {
        set< pair<int,int> > bad;
        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            bad.insert(make_pair(u, v));
            bad.insert(make_pair(v, u));
        }

        REP(turn,1000) {
            FOR(i,1,n) a[i] = i;
            random_shuffle(a+1, a+n+1);

            bool failed = false;
            FOR(i,1,m) {
                int u = a[i];
                int v = (i == n) ? a[1] : a[i+1];

                if (bad.count(make_pair(u, v))) {
                    failed = true;
                    break;
                }
            }
            if (!failed) {
                FOR(i,1,m) {
                    int u = a[i];
                    int v = (i == n) ? a[1] : a[i+1];
                    printf("%d %d\n", u, v);
                }
                break;
            }

            if (turn == 999) {
                cout << -1 << endl;
            }
        }
    }
    return 0;
}
