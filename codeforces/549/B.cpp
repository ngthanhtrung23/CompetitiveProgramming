
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

int n;
char a[111][111];
int x[111];
bool alive[111];
int go[111];

int hasZero() {
    FOR(i,1,n) if (alive[i] && x[i] == 0) return i;
    return 0;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];

        FOR(i,1,n) cin >> x[i];
        memset(alive, true, sizeof alive);
        memset(go, 0, sizeof go);

        while (true) {
            int t = hasZero();
            if (t == 0) break;

            go[t] = 1;
            FOR(i,1,n) if (a[t][i] == '1') --x[i];
        }

        int cnt = 0;
        FOR(i,1,n) cnt += go[i];
        cout << cnt << endl;
        FOR(i,1,n) if (go[i]) cout << i << ' '; cout << endl;
    }
}
