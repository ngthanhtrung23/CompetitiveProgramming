
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

int good[2][111];
int cnt[2];

void on(int t, int u) {
    if (!good[t][u]) {
        good[t][u] = true;
        cnt[t]++;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n, m;
    while (cin >> n >> m) {
        memset(good, false, sizeof good);
        cnt[0] = cnt[1] = 0;
        REP(t,2) {
            int k; cin >> k;
            while (k--) {
                int u; cin >> u;
                on(t, u);
            }
        }

        bool can = false;
        REP(turn,10111) {
            int u = turn % n, v = turn % m;
            if (good[0][u] && good[1][v]) {}
            else if (good[0][u]) on(1, v);
            else if (good[1][v]) on(0, u);

            if (cnt[0] == n && cnt[1] == m) {
                can = true;
                break;
            }
        }
        if (can) cout << "Yes"; else cout << "No";
        cout << endl;
    }
    return 0;
}
