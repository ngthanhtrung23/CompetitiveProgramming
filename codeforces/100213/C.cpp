
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

const int MN = 50111;

ll x[MN], y[MN];
int n;

int main() {
    ios :: sync_with_stdio(false);
    freopen("bw.in", "r", stdin);
    freopen("bw.out", "w", stdout);

    while (cin >> n) {
        FOR(i,1,n) cin >> x[i] >> y[i];
        ll nn = *min_element(x+1, x+n+1);
        if (nn % 2) --nn;
        FOR(i,1,n) x[i] -= nn;

        nn = *min_element(y+1, y+n+1);
        if (nn % 2) --nn;
        FOR(i,1,n) y[i] -= nn;

        ll black = 0, white = 0;
        FOR(i,1,n) {
            int j = i % n + 1;
            if (x[i] == x[j]) {
                ll all = llabs(y[j] - y[i]) * x[i];
                ll cur_black = all / 2;
                ll cur_white = all / 2;

                if (all % 2) {
                    if (min(y[i], y[j]) % 2 == 0) ++cur_black;
                    else ++cur_white;
                }

                if (y[i] < y[j]) {
                    black += cur_black;
                    white += cur_white;
                }
                else {
                    black -= cur_black;
                    white -= cur_white;
                }
            }
        }
        if (black < 0) {
            black = -black;
            white = -white;
        }
        cout << black << ' ' << white << endl;
    }
}
