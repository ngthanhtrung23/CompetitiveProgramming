
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 100111;
int n, d;
pair<int,int> a[MN];
ll sum[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> d) {
        FOR(i,1,n) cin >> a[i].first >> a[i].second;
        sort(a+1, a+n+1);

        FOR(i,1,n) sum[i] = sum[i-1] + a[i].second;

        int j = 1;
        ll res = 0;
        FOR(i,1,n) {
            while (a[i].first - a[j].first >= d) {
                ++j;
            }
            res = max(res, sum[i] - sum[j-1]);
        }
        cout << res << endl;
    }
}
