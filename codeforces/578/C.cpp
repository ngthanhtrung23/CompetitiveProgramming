
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
using namespace std;

const int MN = 200111;
double a[MN], s[MN];
int n;

double f(double x) {
    FOR(i,1,n) s[i] = s[i-1] + a[i] - x;

    double best = 0.0;
    double min_sum = 0, max_sum = 0;

    FOR(i,1,n) {
        best = max(best, fabs(s[i] - min_sum));
        best = max(best, fabs(s[i] - max_sum));

        min_sum = min(min_sum, s[i]);
        max_sum = max(max_sum, s[i]);
    }
    return best;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(12);
    while (cin >> n) {
        ll sum = 0;
        FOR(i,1,n) {
            cin >> a[i];
            sum += a[i];
        }
        double x = sum / (double) n;

        double l = -1e5, r = 1e5;
        REP(turn,100) {
            double x1 = (l + l + r) / 3.0;
            double x2 = (l + r + r) / 3.0;

            double y1 = f(x1);
            double y2 = f(x2);

            if (y1 < y2) r = x2;
            else l = x1;
        }
        cout << f(l) << endl;
    }
}
