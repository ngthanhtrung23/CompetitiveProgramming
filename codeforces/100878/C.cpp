
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

const int MN = 800111;
int n;
struct L {
    int x, h;
} a[MN];

bool operator < (const L& a, const L& b) {
    return a.x < b.x;
}

const int MOD = 1e9 + 7;

int c[MN], nc;
vector<int> id[MN];

void RR() {
    FOR(i,1,n) c[i] = a[i].h;
    sort(c+1, c+n+1);
    nc = unique(c+1, c+n+1) - c - 1;

    FOR(i,1,n) a[i].h = lower_bound(c+1, c+nc+1, a[i].h) - c;

    FOR(i,1,nc) id[i].clear();
    FOR(i,1,n) {
        id[ a[i].h ].push_back(i);
    }
}

int it[MN * 4];

void build(int i, int l, int r) {
    if (l == r) {
        it[i] = a[l].h;
        return ;
    }
    int mid = (l + r) >> 1;

    build(i<<1, l, mid);
    build(i<<1|1, mid+1, r);

    it[i] = max(it[i<<1], it[i<<1|1]);
}

int get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i];

    int mid = (l + r) >> 1;
    return max(get(i<<1, l, mid, u, v), get(i<<1|1, mid+1, r, u, v));
}

int get(const vector<int> &x) {
    if (x.empty()) return 0;

    int res = 0;

    int i = 0, j = 0;
    while (i < SZ(x)) {
        while (j < SZ(x) - 1 && get(1, 1, n, x[i], x[j+1]) <= a[x[i]].h) {
            ++j;
        }

        int sum2 = 0;
        int sum = 0;
        FOR(u,i,j) {
            int id = x[u];
            sum = (sum + a[id].x) % MOD;
            sum2 = (sum2 + sqr(a[id].x)) % MOD;
        }
        int k = j - i + 1;
        res = (res + (k-1LL) * sum2) % MOD;

        FOR(u,i,j) {
            int cur = a[x[u]].x;
            cur = (cur * (sum - a[x[u]].x)) % MOD;

            res = (res - cur + MOD) % MOD;
        }

//        FOR(u,i,j) FOR(v,u+1,j) {
//            int l = x[u];
//            int r = x[v];
//            int cur = sqr(a[l].x - a[r].x);
//            cout << l << ' ' << r << " --> " << cur << endl;
//
//            res = (res + cur) % MOD;
//        }

        i = j + 1;
    }
    return res;
}

int solve() {
    sort(a+1, a+n+1);
    RR();

    build(1, 1, n);

    int res = 0;
    FOR(h,1,nc) {
        res = (res + get(id[h])) % MOD;
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n;
        FOR(i,1,n) cin >> a[i].x >> a[i].h;
        cout << "Case #" << test << ": " << solve() << endl;
    }
}
