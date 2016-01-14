
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

int n;
ll A, cf, cm, can, s[MN];
pair<ll,int> a[MN];
int res[MN];

ll read() {
    ll x; scanf("%I64d", &x);
    return x;
}

ll get(ll x, int n) {
    if (n <= 0) return 0;

    int l = 0, r = n, res = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (a[mid].first < x) res = mid, l = mid + 1;
        else r = mid - 1;
    }

    return x*res - s[res];
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d", &n) == 1) {
        A = read();
        cf = read();
        cm = read();
        can = read();
        FOR(i,1,n) {
            a[i].first = read();
            a[i].second = i;
        }
        sort(a+1, a+n+1);
        FOR(i,1,n) s[i] = s[i-1] + a[i].first;

        int savek = 0, savex = 0;
        ll best = 0;
        FOR(k,0,n) {
            ll cost = 0;
            ll score = 0;

            // n-k+1 --> n: == A
            cost += A * k - (s[n] - s[n-k]);
            score += k * cf;

            if (cost > can) continue;

            // what is minimum?
            ll l = 0, r = A, res = 0;
            while (l <= r) {
                ll mid = (l + r) >> 1;
                if (get(mid, n-k) + cost <= can) {
                    res = mid;
                    l = mid + 1;
                }
                else r = mid - 1;
            }

            score += res * cm;

            if (score > best) {
                best = score;
                savek = k;
                savex = res;
            }
        }

        printf("%I64d\n", best);
        ll cost = 0;
        FOR(i,1,n-savek) {
            int id = a[i].second;
            res[id] = a[i].first;
            if (res[id] < savex) {
                res[id] = savex;
                cost += savex - a[i].first;
            }
        }
        FOR(i,n-savek+1,n) {
            int id = a[i].second;
            cost += A - a[i].first;
            res[id] = A;
        }
        assert(cost <= can);
        FOR(i,1,n) printf("%d ", res[i]); puts("");
    }
}
