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

int n, a[MN], l[MN], r[MN], st[MN], top;
int res[MN];

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);

        top = 0; st[0] = 0; a[0] = 0;
        FOR(i,1,n) {
            while (top && a[st[top]] >= a[i]) --top;
            l[i] = st[top] + 1;
            st[++top] = i;
        }
        top = 0; st[0] = n+1; a[n+1] = 0;
        FORD(i,n,1) {
            while (top && a[st[top]] >= a[i]) --top;
            r[i] = st[top] - 1;
            st[++top] = i;
        }
        memset(res, 0, sizeof res);
        FOR(i,1,n) {
            int len = r[i] - l[i] + 1;
            res[len] = max(res[len], a[i]);
        }

        FORD(i,n-1,1) res[i] = max(res[i], res[i+1]);

        FOR(i,1,n) printf("%d ", res[i]); puts("");
    }
    return 0;
}

