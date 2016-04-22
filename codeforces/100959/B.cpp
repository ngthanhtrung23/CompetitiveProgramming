
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

int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 100111;
int n;
pair<int,int> a[MN];

int lab[MN];
struct DSU {
    void init(int n) {
        REP(i,n+1) lab[i] = -1;
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

int dist(int u, int v) {
    return llabs(a[u].first - a[v].first)
        + llabs(a[u].second - a[v].second);
}
bool check(int val) {
    DSU dsu;
    dsu.init(n);

    FOR(u,1,min(8LL,n)) FOR(v,1,n) 
        if (dist(u, v) >= val)
            dsu.merge(u, v);

    int cnt = 0;
    FOR(i,1,n) if (lab[i] < 0) ++cnt;
    return cnt == 1;
}

pair<int,int> getKey(int turn, int i) {
    switch (turn) {
        case 1:
            return make_pair(a[i].first + a[i].second, a[i].first);
        case 2:
            return make_pair(a[i].first + a[i].second, -a[i].first);
        case 3:
            return make_pair(a[i].first - a[i].second, a[i].first);
        case 4:
            return make_pair(a[i].first - a[i].second, -a[i].first);
        case 5:
            return make_pair(-a[i].first + a[i].second, a[i].first);
        case 6:
            return make_pair(-a[i].first + a[i].second, -a[i].first);
        case 7:
            return make_pair(-a[i].first - a[i].second, a[i].first);
        case 8:
            return make_pair(-a[i].first - a[i].second, -a[i].first);
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        FOR(i,1,n) {
            GI(a[i].first);
            GI(a[i].second);
        }
        random_shuffle(a+1, a+n+1);

        FOR(turn,1,min(8LL,n)) {
            FOR(i,turn+1,n)
                if (getKey(turn,turn) > getKey(turn,i))
                    swap(a[turn], a[i]);
        }

        int l = 0, r = 2000111000, res = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) res = mid, l = mid + 1;
            else r = mid - 1;
        }
        cout << res << endl;
    }
}
