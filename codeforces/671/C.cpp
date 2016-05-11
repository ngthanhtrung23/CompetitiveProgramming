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

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

const int MN = 200111;
int a[MN];
int n;


int x[MN], nx;
int brute() {
    int res = 0;
    FOR(i,1,n) FOR(j,i,n) {
        nx = 0;
        FOR(u,1,n) if (u < i || u > j) x[++nx] = a[u];

        if (nx <= 1) continue;

        int cur = 0;
        FOR(u,1,nx) FOR(v,u+1,nx) cur = max(cur, __gcd(x[u], x[v]));
        res += cur;
    }
    return res;
}

int id[MN];
vector< pair< pair<int,int>, int > > at[MN];


struct Node {
    int ln, sum;
    int lazy;
} it[MN*8];

void refine(int i) {
    it[i].ln = max(it[i<<1].ln, it[i<<1|1].ln);
    it[i].sum = it[i<<1].sum + it[i<<1|1].sum;
}
void setEqual(int i, int l, int r, int val) {
    it[i].ln = it[i].lazy = val;
    it[i].sum = (r - l + 1) * val;
}

void down(int i, int l, int r, int mid) {
    if (it[i].lazy >= 0) {
        int t = it[i].lazy; it[i].lazy = -1;

        setEqual(i<<1, l, mid, t);
        setEqual(i<<1|1, mid+1, r, t);
    }
}

void build(int i, int l, int r) {
    if (l == r) {
        it[i].ln = it[i].sum = l;
        it[i].lazy = -1;
        return ;
    }
    it[i].lazy = -1;
    int mid = (l + r) >> 1;
    build(i<<1,l,mid);
    build(i<<1|1,mid+1,r);
    refine(i);
}
int getSum(int i, int l, int r, int u, int v) {
    if (u > v) return 0;
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].sum;

    int mid = (l + r) >> 1;
    down(i,l,r,mid);
    
    int res = getSum(i<<1,l,mid,u,v) + getSum(i<<1|1, mid+1,r,u,v);

    refine(i);
    return res;
}
int findGreater(int i, int l, int r, int val) {
    if (it[i].ln <= val) return r + 1;
    if (l == r) return l;

    int mid = (l + r) >> 1;
    down(i,l,r,mid);

    int res;
    if (it[i<<1].ln >= val) res = findGreater(i<<1,l,mid,val);
    else res = findGreater(i<<1|1,mid+1,r,val);

    refine(i);

    return res;
}

void equal(int i, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        setEqual(i,l,r,val);
        return ;
    }
    int mid = (l + r) >> 1;
    down(i,l,r,mid);

    equal(i<<1,l,mid,u,v,val);
    equal(i<<1|1,mid+1,r,u,v,val);

    refine(i);
}

int solve() {
    memset(id, 0, sizeof id);
    FOR(i,1,n) id[a[i]] = i;

    memset(it, 0, sizeof it);
    build(1,1,n);

    int res = 0;
    FORD(g,200000,1) {
        nx = 0;
        for(int val=g; val <= 200000; val += g) if (id[val]) {
            x[++nx] = id[val];
        }

        if (nx < 2) continue;
        sort(x+1, x+nx+1);

        int cur = 0;
        // i > x2
        int j = findGreater(1,1,n,x[2]);
        if (j <= n) {
            cur += getSum(1,1,n,j,n) - (n-j+1)*x[2];
            equal(1,1,n,j,n,x[2]);
        }

        // j < x[nx-1]
        cur += getSum(1,1,n,1,x[nx-1]-1);
        equal(1,1,n,1,x[nx-1]-1,0);

        // i > x[1] && j < x[nx]
        j = findGreater(1,1,n,x[1]);
        if (j < x[nx]) {
            cur += getSum(1,1,n,j,x[nx]-1) - x[1] * (x[nx]-j);
            equal(1,1,n,j,x[nx]-1,x[1]);
        }
        res += g * cur;
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        FOR(i,1,n) GI(a[i]);

        int res = solve();
        cout << res << endl;
    }
}
