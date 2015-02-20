
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
int l[MN], r[MN];

#define MOVE { moved = true; if (cur < f) { putchar('R'); ++cur; } else { putchar('L'); --cur; } }

int main() {
    int n, q, s, f;
    while (scanf("%d%d%d%d", &n, &q, &s, &f) == 4) {
        memset(l, -1, sizeof l);
        memset(r, -1, sizeof r);

        while (q--) {
            int t, u, v; scanf("%d%d%d", &t, &u, &v);
            if (t < MN) l[t] = u, r[t] = v;
        }

        int cur = s, time = 0;
        while (cur != f) {
            bool moved = false;
            ++time;
            if (l[time] < 0) MOVE
            else {
                int next = cur;
                if (next < f) ++next;
                else --next;

                if (cur < l[time] || r[time] < cur)
                    if (next < l[time] || r[time] < next)
                        MOVE;
            }
            if (!moved) putchar('X');
        }
        puts("");
    }
    return 0;
}
