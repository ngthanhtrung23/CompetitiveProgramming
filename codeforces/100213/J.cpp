
#include <bits/stdc++.h>
#include <ext/rope>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;
using namespace __gnu_cxx;

const int MN = 40;
int n, t, p;
int a[2][40];
pair<int,int> mv[MN];

ll p6[40];

#define hash hash__
ll hash(int r[]) {
    ll res = 0;
    REP(i,n) {
        int x = r[i];
        res = res * 41 + x;
    }
    return res;
}

int f[40], tmp[40];
unordered_map< ll, ll > all;

void apply(int v[], int u) {
    REP(i,n) tmp[i] = v[i];

    int from = n - mv[u].first - mv[u].second;
    int to = n - mv[u].first;

    int cur = 0;
    FOR(i,from,to-1) v[cur++] = tmp[i];
    FOR(i,0,from-1) v[cur++] = tmp[i];
    FOR(i,to,n-1) v[cur++] = tmp[i];
}

void undo(int v[], int u) {
    REP(i,n) tmp[i] = v[i];

    int cur = 0;
    FOR(i,mv[u].second,n-mv[u].first-1) v[cur++] = tmp[i];
    FOR(i,0,mv[u].second-1) v[cur++] = tmp[i];
    FOR(i,n-mv[u].first,n-1) v[cur++] = tmp[i];
}

void attempt1(int i, int bound, ll sum, int a[]) {
    if (i > bound) {
        all[hash(a)] = sum;
        return ;
    }

    FOR(val,1,p) {
        f[i] = val;
        apply(a, val);
        attempt1(i+1, bound, sum + p6[i] * val, a);
        undo(a, val);
    }
}

void attempt2(int i, int bound, ll sum, int a[]) {
    if (i < bound) {
        ll h = hash(a);
        if (all.count(h)) {
            ll mask = sum + all[h];
    
            FOR(turn,1,t) {
                cout << (mask % p6[turn+1]) / p6[turn] << ' ';
            }
            cout << endl;
            throw 1;
        }
        return ;
    }

    FOR(val,1,p) {
        f[i] = val;
        undo(a, val);
        attempt2(i-1, bound, sum + p6[i] * val, a);
        apply(a, val);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);

    p6[0] = 1;
    FOR(i,1,19) p6[i] = p6[i-1] * 6LL;

    while (cin >> n >> t >> p) {
        REP(t,2) {
            REP(i,n) {
                cin >> a[t][i];
            }
        }
        FOR(i,1,p) cin >> mv[i].first >> mv[i].second;
        int left = t/2;

        // xuoi
        all.clear();

        int v[MN];
        REP(i,n) v[i] = a[0][i];

        attempt1(1, left, 0LL, v);

        // nguoc
        try {
            REP(i,n) v[i] = a[1][i];
            attempt2(t, left+1, 0LL, v);
            cout << "Impossible" << endl;
        } catch (...) {
        }
    }
}
