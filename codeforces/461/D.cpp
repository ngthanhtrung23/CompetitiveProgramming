#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 200111;
const long long MOD = 1000000007;

vector<pair< pair<int,int>,int> > restrictions[2];

pair<int,int> getRange(int i, int j, int n) {
    if (i > j) swap(i, j);
    if (j > n-i+1) {
        j = n - j + 1;
        swap(i, j);
        j = n - j + 1;
    }
    return make_pair(1 + j - i, i + j - 1);
}

struct DSU {
    int lab[MN];
    void init() {
        memset(lab, -1, sizeof lab);
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};
long long get(int n, vector<pair<pair<int,int>,int>>& restrictions) {
    DSU dsu;
    dsu.init();
    
    int N = n * 2 + 2;
    for(auto cur : restrictions) {
        int from = cur.first.first, to = cur.first.second;
        int val = cur.second;

        if (val == 0) {
            dsu.merge(2*from, 2*(to+1));
            dsu.merge(2*from+1, 2*(to+1)+1);
        }
        else {
            dsu.merge(2*from, 2*(to+1)+1);
            dsu.merge(2*from+1, 2*(to+1));
        }
    }
    FOR(i,1,n+1)
        if (dsu.getRoot(i*2) == dsu.getRoot(i*2+1))
            return 0;

    long long res = 0;
    FOR(i,1,n+1)
        if (dsu.getRoot(i*2) == i*2) {
            if (res == 0) res = 1;
            else res = (res * 2) % MOD;
        }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n, k;
    while (cin >> n >> k) {
        REP(t,2) restrictions[t].clear();
        int nOdd, nEven;
        nOdd = nEven = n / 2;
        if (n % 2 == 1) nOdd++;

        while (k--) {
            int i, j; char c;
            cin >> i >> j >> c;
            int value = (c == 'x') ? 0 : 1;
            pair<int,int> x = getRange(i, j, n);

            restrictions[x.first % 2].push_back(make_pair(make_pair(x.first/2 + x.first%2, x.second/2 + x.second%2), value));
        }
        cout << get(nEven, restrictions[0]) * get(nOdd, restrictions[1]) % MOD << endl;
    }
    return 0;
}
