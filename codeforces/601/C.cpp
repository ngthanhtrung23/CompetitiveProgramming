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

#define double long double
int n, m, a[111], x[111], saven;
double f[2][100111], sum[2][100111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(12);
    while (cin >> n >> m) {
        int sumA = 0;
        FOR(i,1,n) {
            int x; cin >> x;
            --x;
            a[i] = x;
            sumA += x;
        }

        if (m == 1) {
            cout << 1.0 << endl;
            continue;
        }

        FOR(i,1,n) {
            int cur = i % 2;
            memset(f[cur], 0, sizeof f[cur]);

            if (i == 1) {
                REP(val,m*i)
                    if (val < m && val != a[i]) f[cur][val] = 1;
            }
            else {
                REP(val,m*i) {
                    f[cur][val] = sum[1-cur][val];
                    if (val >= m)
                        f[cur][val] -= sum[1-cur][val-m];
                    f[cur][val] -= f[1-cur][val - a[i]];
                }
            }
            
            REP(val,m*(i+1)) {
                sum[cur][val] = f[cur][val];
                if (val > 0)
                    sum[cur][val] += sum[cur][val-1];
            }
        }
        double t = sum[n % 2][sumA-1];
        REP(turn,n) t /= (m-1);
        cout << t * (m-1.0) + 1 << endl;
    }
}