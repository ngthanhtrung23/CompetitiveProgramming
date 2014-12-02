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

const int MN = 1000111;
int n, m, dx, dy;
pair<int,int> a[MN];
int at[MN];
int start[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m >> dx >> dy) {
        FOR(i,1,m) cin >> a[i].first >> a[i].second;
        int u = 0, v = 0;
        REP(turn,n) {
            at[u] = v;
            u = (u + dx) % n;
            v = (v + dy) % n;
        }
        memset(start, 0, sizeof start);
        FOR(i,1,m) {
            int u = a[i].first, v = a[i].second;
            // start (0, 0) --> visit (u, at[u])
            // start (0, ?) --> visit (u, v)
            // ? + at[u] == v

            int x = (v + n - at[u]) % n;
            start[x] += 1;
        }
        int ln = *max_element(start, start+n);
        REP(i,n) if (start[i] == ln) {
            cout << 0 << ' ' << i << endl;
            break;
        }
    }
    return 0;
}
