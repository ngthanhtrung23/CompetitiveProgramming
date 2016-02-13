#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define SZ(x) ((int) (x).size())
#define ll long long
using namespace std;

const int MOD = 1e9 + 7;
int n, k, a[211];
int f[2][211][1011];

void update(int& f, int x) {
    f += x;
    if (f >= MOD) f -= MOD;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> k) {
        memset(f, 0, sizeof f);
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);

        f[0][0][0] = 1;
        FOR(i,0,n-1) {
            int t = i % 2;
            memset(f[1-t], 0, sizeof f[1-t]);

            FOR(open,0,i) FOR(sum,0,k) {
                int cur = f[t][open][sum];
                if (!cur) continue;
                
                int val = a[i+1] - a[i];
                int sum2 = open * val + sum;
                if (sum2 > k) continue;

                // to new group, open & close immediately
                update(f[1 - t][open][sum2], cur);

                // to new group, open
                update(f[1 - t][open+1][sum2], cur);

                // add to existing
                if (open) {
                    update(f[1 - t][open][sum2], cur * (ll) open % MOD);
                }
                
                // add to existing, close
                if (open) {
                    update(f[1 - t][open-1][sum2], cur * (ll) open % MOD);
                }
            }
        }
        int t = n % 2, res = 0;
        FOR(sum,0,k) update(res, f[t][0][sum]);
        cout << res << endl;
    }
}
