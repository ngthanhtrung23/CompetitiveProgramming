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

const int MN = 200111;
const int SQ = 500;

struct Query {
    int l, r, id;
} q[MN];
int n, a[MN], nq;
ll res[MN], sum;
int cnt[1000111];

bool operator < (const Query& a, const Query& b) {
    if (a.l / SQ != b.l / SQ) return a.l / SQ < b.l / SQ;
    return a.r < b.r;
}

void add(int i, int val) {
    sum -= a[i] * (ll) cnt[a[i]] * cnt[a[i]];
    cnt[a[i]] += val;
    sum += a[i] * (ll) cnt[a[i]] * cnt[a[i]];
}

int main() {
    while (scanf("%d%d", &n, &nq) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]);
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,nq) {
            scanf("%d%d", &q[i].l, &q[i].r);
            q[i].id = i;
        }
        sort(q+1, q+nq+1);

        sum = 0;
        int l = 0, r = 0;
        FOR(i,1,nq) {
            while (r < q[i].r) {
                ++r;
                add(r, +1);
            }
            while (l > q[i].l) {
                --l;
                add(l, +1);
            }

            while (r > q[i].r) {
                add(r, -1);
                --r;
            }
            while (l < q[i].l) {
                add(l, -1);
                ++l;
            }

            res[q[i].id] = sum;
        }

        FOR(i,1,nq) printf("%lld\n", res[i]);
    }
}
