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

double f[111][100111];
int tr[111][100111];

double get(int n, int s, int t, double p) {
    if (s == n) return 1.0;
    if (s == 0) return 0.0;
    if (t == 0) return 0.0;

    double res = 0.0;
    int win = s + min(s, n - s);
    res += p * get(n, win, t-1, p);

    int lose = s - min(s, n - s);
    res += (1 - p) * get(n, lose, t-1, p);
    return res;
}

int main() {
    freopen("betting.in", "r", stdin);
    freopen("betting.out", "w", stdout);
    int n;
    double p;
    int s;
    int t;
    cout << (fixed) << setprecision(12);

    while (cin >> n >> s >> p >> t && n) {
        p /= 100.0;

        cout << get(n, s, t, p) << endl;
    }
    return 0;
}
