
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
#define double long double
using namespace std;

double dist;
int n;
int maxBound;

double pos[55], height[55];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> dist >> n >> maxBound) {
        FOR(i,1,n) cin >> pos[i] >> height[i];

        double minv = 1e100;
        FOR(b,0,maxBound) {
            double each = dist / (b + 1);
            vector<double> x; x.push_back(0);
            FOR(i,1,b+1) x.push_back(each * i);

            double vy = sqrt(each / 2);

            bool can = true;
            FOR(part,0,b) {
                double from = x[part];
                double to = x[part+1];

                FOR(i,1,n) {
                    if (fabs(pos[i] - from) < 1e-9) {
                        can = false;
                        break;
                    }
                    if (fabs(pos[i] - to) < 1e-9) {
                        can = false;
                        break;
                    }

                    if (pos[i] < from || to < pos[i]) continue;

                    double t = (pos[i] - from) / (to - from);
                    double need = sqrt(height[i] / 2 / (t - t*t));

                    vy = max(vy, need);
                }
            }

            if (!can) continue;

            double vx = each / 2 / vy;
            minv = min(minv, sqrt(vx*vx + vy*vy));
        }
        cout << (fixed) << setprecision(9) << minv << endl;
    }
}
