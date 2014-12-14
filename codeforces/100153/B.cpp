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

double f[2][500111];
bitset<500111> tr[55];
int a[55], typ[55];
double b[55], x;
int n;

void trace(int n, int sum) {
    if (n == 0) return ;
    typ[n] = tr[n][sum];
    if (typ[n] == 0) trace(n-1, sum - a[n]);
    else trace(n-1, sum);
}

int main() {
    freopen("discount.in", "r", stdin);
    freopen("discount.out", "w", stdout);
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> x) {
        FOR(i,1,n) {
            cin >> a[i] >> b[i];
            b[i] = (100 - b[i]) / (double) 100.0;
        }
        FOR(i,0,1) FOR(sum,0,500100) f[i][sum] = 1e20;
        f[0][0] = x;
        int cur = 0;
        FOR(i,0,n-1) {
            FOR(sum,0,i*10000)
            if (f[cur][sum] < 1e19) {
                // mul
                double t = f[cur][sum] * b[i+1];
                if (t < f[1-cur][sum]) {
                    f[1-cur][sum] = t;
                    tr[i+1].set(sum);
                }
                // add
                if (f[cur][sum] < f[1-cur][sum+a[i+1]]) {
                    f[1-cur][sum+a[i+1]] = f[cur][sum];
                    tr[i+1].set(sum+a[i+1], 0);
                }
            }
            cur = 1 - cur;
        }
        double best = 1e20, save = 0;
        FOR(sum,0,n*10000)
            if (f[cur][sum] - sum < best) {
                best = f[cur][sum] - sum;
                save = sum;
            }
        trace(n, save);
        FOR(i,1,n) if (typ[i] == 1) cout << i << " reverse" << endl;
        FOR(i,1,n) if (typ[i] == 0) cout << i << " front" << endl;

        cout << endl;
    }
    return 0;
}

