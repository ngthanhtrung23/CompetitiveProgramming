
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

#define int long long

const int MN = 100111;
int n, A, cf, cm, m;
pair<int,int> a[MN];
int res[MN], sum[MN];

int get(int x, int n) {
    if (a[n].first < x) return x*n - sum[n];
    int t = lower_bound(a+1, a+n+1, make_pair(x, 0LL)) - a - 1;
    return x * t - sum[t];
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> A >> cf >> cm >> m) {
        FOR(i,1,n) {
            cin >> a[i].first;
            a[i].second = i;
        }
        sort(a+1, a+n+1);
        FOR(i,1,n) sum[i] = sum[i-1] + a[i].first;

        int best = 0;
        int savef = 0, savem = 0;

        FOR(f,0,n) {
            int cost = A*f - (sum[n] - sum[n-f]);
            int score = f * cf;

            if (cost > m) continue;

            int l = 0, r = A, res = 0;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (get(mid, n-f) + cost <= m) {
                    res = mid;
                    l = mid + 1;
                }
                else r = mid - 1;
            }
            score += res * cm;

            if (score > best) {
                best = score;
                savef = f;
                savem = res;
            }
        }

        cout << best << endl;
        FOR(i,1,n) {
            int t = 0;
            if (i <= n - savef) {
                t = max(a[i].first, savem);
            }
            else t = A;

            res[a[i].second] = t;
        }
        FOR(i,1,n) cout << res[i] << ' '; cout << endl;
    }
}
