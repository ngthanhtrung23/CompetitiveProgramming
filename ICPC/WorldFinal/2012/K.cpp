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

int n;
vector<int> a[55];
int c[55*55], nc;
set<int> ls[55*55];
int f[2511][55];
const int INF = 1000111000;

void init() {
    FOR(i,1,n) a[i].clear();
    nc = 0;
    FOR(i,1,2500) ls[i].clear();

    FOR(i,0,2500) FOR(j,0,n) f[i][j] = INF;
}

void update(int&f, int val) {
    f = min(f, val);
}

int solve() {
    for(auto x : ls[1]) {
        f[1][x] = SZ(ls[1]) - 1;
    }
    FOR(val,1,nc-1) FOR(u,1,n) {
        int t = f[val][u]; if (t == INF) continue;

        if (SZ(ls[val+1]) == 1 && ls[val+1].count(u)) {
            update(f[val+1][u], t);
        }
        else {
            for(int v : ls[val+1]) if (v != u) {
                int add = SZ(ls[val+1]);
                if (ls[val+1].count(u)) --add;

                update(f[val+1][v], t + add);
            }
        }
    }

    int res = INF;
    FOR(i,1,n) res = min(res, f[nc][i]);
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    /*
       no. merge = no. stack + no. split - 1
       --> min. no. split
       x = no. split
       --> res = n + 2*x - 1

       f[val][u] = already filled values 1..val. Currently at stack u
       --> update f(val+1, v)

       ls[val+1] = {u} --> f(val+1, u) = f(val, u)
       ls[val+1] = {u, v} --> f(val+1, v) = f(val, u) + 1
       ls[val+1] = {u, v, x1, x2, xk} --> f(val+1, v) = f(val, u) + 1 + k

       1 1 2 2     3 3
       1 1     2 2 3 3
    */
    int test = 0;
    while (cin >> n) {
        init();
        FOR(i,1,n) {
            int k; cin >> k;
            a[i].resize(k);
            REP(j,k) {
                cin >> a[i][j];
                c[++nc] = a[i][j];
            }
        }
        sort(c+1, c+nc+1);
        nc = unique(c+1, c+nc+1) - c - 1;
        FOR(i,1,n) {
            REP(j,SZ(a[i])) {
                a[i][j] = lower_bound(c+1, c+nc+1, a[i][j]) - c;
            }
        }
//        FOR(i,1,n) {
//            PR0(a[i], SZ(a[i]));
//        }
        FOR(i,1,n) {
            REP(j,SZ(a[i])) ls[a[i][j]].insert(i);
        }
        cout << "Case " << ++test << ": " << 2*solve() - n + 1 << endl;
    }
}
