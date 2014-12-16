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

long long mysqrt(long long n) {
    long long x = (long long ) round(sqrt(n));
    while (x*x > n) --x;
    while ((x+1)*(x+1) <= n) ++x;
    return x;
}

const int MN = 100111;
int n, lg[MN];
long long x[MN], a;
long long ln[22][MN], nn[22][MN];

#define TWO(X) (1<<(X))

long long getMax(int i, int j) {
    int len = j - i + 1;
    return max( ln[lg[len]][i], ln[lg[len]][j-TWO(lg[len])+1]);
}

long long getMin(int i, int j) {
    int len = j - i + 1;
    return min( nn[lg[len]][i], nn[lg[len]][j-TWO(lg[len])+1]);
}

int getFirst(int u, long long low_bound, long long up_bound) {
    int l = 1, r = u, res = u;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (getMax(mid, u) <= up_bound && getMin(mid, u) >= low_bound) res = mid, r = mid - 1;
        else l = mid + 1;
    }
    return res;
}

int getLast(int u, long long low_bound, long long up_bound) {
    int l = u, r = n, res = u;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (getMax(u, mid) <= up_bound && getMin(u, mid) >= low_bound) res = mid, l = mid + 1;
        else r = mid - 1;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    lg[1] = 0;
    for(int p = 1, i = 0; p < MN; p *= 2, ++i) {
        lg[p] = i;
    }
    FOR(i,1,MN-1)
        if (lg[i] == 0) lg[i] = lg[i-1];
    FOR(test,1,ntest) {
        cin >> n >> a;
        FOR(i,1,n) cin >> x[i];
        FOR(i,1,n) ln[0][i] = nn[0][i] = x[i];
        FOR(t,1,20)
            FOR(i,1,n-TWO(t)+1) {
                ln[t][i] = max(ln[t-1][i], ln[t-1][i+TWO(t-1)]);
                nn[t][i] = min(nn[t-1][i], nn[t-1][i+TWO(t-1)]);
            }


        int res = 0;
        FOR(i,1,n) {
            long long bound = mysqrt(2*a*x[i] + x[i]*x[i] + a*a);
            if (bound < x[i]) continue;
            int from = getFirst(i, x[i], bound);
            int to = getLast(i, x[i], bound);
            res = max(to - from + 1, res);
        }
        cout << "Case #" << test << ": " << res << endl;
    }
    return 0;
}

