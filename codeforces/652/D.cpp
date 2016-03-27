
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

const int MN = 400111;

struct Seg {
    int l, r, id;
    int res;
} a[MN];

bool operator < (const Seg& a, const Seg& b) {
    return a.l > b.l;
}

int n, c[MN], nc;
int bit[MN];

int get(int u) {
    int res = 0;
    for(; u > 0; u -= u & -u)
        res += bit[u];
    return res;
}
void update(int u, int val) {
    for(; u < MN; u += u & -u)
        bit[u] += val;
}

bool cmpId(const Seg& a, const Seg& b) {
    return a.id < b.id;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        nc = 0;
        FOR(i,1,n) {
            cin >> a[i].l >> a[i].r; a[i].id = i;
            c[++nc] = a[i].l;
            c[++nc] = a[i].r;
        }
        sort(c+1, c+nc+1);
        nc = unique(c+1, c+nc+1) - c - 1;
        FOR(i,1,n) {
            a[i].l = lower_bound(c+1, c+nc+1, a[i].l) - c;
            a[i].r = lower_bound(c+1, c+nc+1, a[i].r) - c;
        }

        sort(a+1, a+n+1);

        memset(bit, 0, sizeof bit);
        FOR(i,1,n) {
            a[i].res = get(a[i].r - 1);
            update(a[i].r, 1);
        }
        sort(a+1, a+n+1, cmpId);
        FOR(i,1,n) cout << a[i].res << '\n';
    }
}
