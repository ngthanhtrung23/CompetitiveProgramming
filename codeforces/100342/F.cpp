
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

int a[MN], c[MN], bit[MN], res[MN];
#define next next___
#define prev prev___
int next[MN], prev[MN];
int id[MN];

int get(int u) {
    int res = 0;
    for(int x = u; x > 0; x -= x & -x)
        res += bit[x];
    return res;
}
void update(int u, int val) {
    for(int x = u; x < MN; x += x & -x)
        bit[x] += val;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("mtf.in", "r", stdin);
    freopen("mtf.out", "w", stdout);
    int n;
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            c[i] = a[i];
        }
        sort(c+1, c+n+1);
        int nc = unique(c+1, c+n+1) - c - 1;
        FOR(i,1,n) a[i] = lower_bound(c+1, c+nc+1, a[i]) - c;

        memset(id, 0, sizeof id);
        memset(next, -1, sizeof next);
        FOR(i,1,n) {
            if (id[a[i]]) {
                int j = id[a[i]];
                next[j] = i;
                prev[i] = j;
            }
            else {
                prev[i] = 0;
            }
            id[a[i]] = i;
        }
        memset(bit, 0, sizeof bit);
        memset(res, 0, sizeof res);
        FOR(i,1,n) {
            if (prev[i] == 0) {
                res[i] = c[a[i]] + get(n) - get(a[i]);
                update(a[i], 1);
            }
        }
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) if (!prev[i]) update(i, +1);

        FOR(i,1,n) {
            update(i, -1);
            if (next[i] >= 0) {
                update(next[i], 1);
                res[next[i]] = 1 + get(next[i] - 1);
            }
        }
        FOR(i,1,n) printf("%d ", res[i]); puts("");
    }
}
