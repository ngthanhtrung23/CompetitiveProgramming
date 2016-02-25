
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

const int MN = 411;
int n, a[MN];

// what greedy will return?
int greedy(int x) {
    int res = 0;
    FOR(i,1,n) {
        res += x / a[i];
        x %= a[i];
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        const int INF = 1000111000;
        int res = INF;

        FOR(i,2,n) {
            FOR(j,i,n) {
                int tmp = a[i-1] - 1;
                int am = 0;
                int w = 0;
                FOR(k,1,j) {
                    int cnt = tmp / a[k];
                    if (k == j) ++cnt;
                    tmp %= a[k];
                    am += cnt;
                    w += cnt * a[k];
                }

                if (am < greedy(w)) res = min(res, w);
            }
        }
        if (res == INF) res = -1;
        cout << res << endl;
    }
}
