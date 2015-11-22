
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    double R, v;
    while (cin >> n >> R >> v) {
        while (n--) {
            double s, f, len; cin >> s >> f;
            len = f - s;
            if (len < 0) len = -len;

            double each = 2*acos((double)-1.0)*R;
            double cnt = floor(len / each);
            len -= each * cnt;

            double l = 0;
            double r = len * 0.5 + R;
            REP(turn,60) {
                double mid = (l + r) / 2.0;
                if (mid + R*sin(mid / R) >= len * 0.5) {
                    r = mid;
                }
                else l = mid;
            }
            cout << ((l + r) + each * cnt) /v << '\n';
        }
    }
}
