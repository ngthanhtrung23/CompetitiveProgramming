
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 200111;
const int INF = 1000111000111000111LL;

int a[MN], n, k;
pair<int,int> l[MN], r[MN], b[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (scanf("%lld%lld", &n, &k) == 2) {
        FOR(i,0,n) scanf("%lld", &a[i]);

        memset(l, 0, sizeof l);
        memset(r, 0, sizeof r);

        // go from left
        FOR(i,0,n-1) {
            // use a[i] --> b[i]
            if (i == 0) {
                // a[0] = -2 * b[0]
                if (a[i] % 2 != 0) {
                    break;
                }
                else {
                    b[i].first = 1;
                    b[i].second = a[i] / -2;
                }
            }
            else {
                // a[i] = b[i-1] - 2 * b[i]
                if ((a[i] - b[i-1].second) % 2) {
                    break;
                }
                else {
                    b[i].first = 1;
                    b[i].second = (a[i] - b[i-1].second) / -2;
                }
            }
            if (llabs(b[i].second) > INF) {
                b[i].first = 0;
                break;
            }
        }
//        FOR(i,0,n-1) cout << b[i].first << ' ' << b[i].second << endl;
        FOR(i,0,n-1) l[i] = b[i];

        // go from right
        FORD(i,n,1) {
            if (i == n) {
                b[i-1].first = 1;
                b[i-1].second = a[i];
            }
            else {
                // a[i] = b[i-1] - 2*b[i]
                b[i-1].first = 1;
                b[i-1].second = a[i] + 2*b[i].second;
            }
            if (llabs(b[i].second) > INF) {
                b[i].first = 0;
                break;
            }
        }

//        cout << endl;
//        FOR(i,0,n-1) cout << b[i].first << ' ' << b[i].second << endl;
        FOR(i,0,n-1) r[i] = b[i];

        int res = 0;
        FOR(i,0,n) {
            // if we change a[i]
//            DEBUG(i);
            if (i == 0) {
                int newa0 = -2 * r[0].second;
//                DEBUG(newa0);
                if (r[0].first && llabs(newa0) <= k && newa0 != a[0]) ++res;
            }
            else if (i == n) {
                if (l[n-1].first) {
                    int newa = l[n-1].second;
//                    DEBUG(newa);
                    if (llabs(newa) <= k && newa && newa != a[n]) ++res;
                }
            }
            else {
                if (l[i-1].first && r[i].first) {
                    ll b0 = l[i-1].second;
                    ll b1 = r[i].second;
                    ll newa = b0 - 2 * b1;
//                    DEBUG(newa);
                    if (llabs(newa) <= k && newa != a[i]) ++res;
                }
            }
        }
        cout << res << endl;
//        cout << "----" << endl;
    }
}
