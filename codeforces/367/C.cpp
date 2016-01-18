
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;

int a[MN];
ll cost[MN], sum[MN];
int n, m;

ll need(ll k) {
    if (k % 2 == 1) return k * (k-1) / 2;
    return k * (k-1) / 2 + k/2 - 1;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> m) {
        FOR(i,1,m) cin >> a[i] >> cost[i];
        sort(cost+1, cost+m+1);
        reverse(cost+1, cost+m+1);

        FOR(i,1,m) sum[i] = sum[i-1] + cost[i];

        ll res = 0;
        FOR(k,1,m) { // take k most expensive
            if (n-1 >= need(k)) {
                res = sum[k];
            }
        }
        cout << res << endl;
    }
}
