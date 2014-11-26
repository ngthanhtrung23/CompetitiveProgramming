#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))

const int MN = 100111;
int n, q, a[MN];
set< pair<int,int> > segs[22];
long long res, f[MN];

void insertPair(int bit, int u, int v) {
    segs[bit].insert(make_pair(u, v));
    res += f[v-u+1] << (long long) bit;
}

void removePair(int bit, int u, int v) {
    segs[bit].erase(make_pair(u, v));
    res -= f[v-u+1] << (long long) bit;
}

void add(int bit, int u) {
//    cout << "Add: " << u << endl;
//    for(auto seg : segs[bit]) cout << seg.first << ' ' << seg.second << "   "; cout << endl;
    insertPair(bit, u, u);

    // Merge with next segment
    auto it = segs[bit].find(make_pair(u, u));
    ++it;
    if (it != segs[bit].end() && it->first == u+1) {
        int x = it->first, y = it->second;
        removePair(bit, u, u);
        removePair(bit, x, y);
        insertPair(bit, u, y);
    }

    // Merge with previous segment
    it = segs[bit].lower_bound(make_pair(u, u));
    int v = it->second;
    if (it != segs[bit].begin()) {
        --it;
        if (it->second == u-1) {
            int x = it->first, y = it->second;
            removePair(bit, u, v);
            removePair(bit, x, y);
            insertPair(bit, x, v);
        }
    }

//    for(auto seg : segs[bit]) cout << seg.first << ' ' << seg.second << "   "; cout << endl;
}

void remove(int bit, int u) {
//    cout << "Remove: " << u << endl;
//    for(auto seg : segs[bit]) cout << seg.first << ' ' << seg.second << "   "; cout << endl;
    auto it = segs[bit].upper_bound(make_pair(u, n+1));
    --it;
    int x = it->first, y = it->second;
    removePair(bit, x, y);

    if (x == y) {}
    else if (u == x) insertPair(bit, x+1, y);
    else if (u == y) insertPair(bit, x, y-1);
    else {
        insertPair(bit, x, u-1);
        insertPair(bit, u+1, y);
    }
//    for(auto seg : segs[bit]) cout << seg.first << ' ' << seg.second << "   "; cout << endl;
}

void init() {
    REP(bit,20) {
        segs[bit].clear();
        FOR(i,1,n) if (CONTAIN(a[i], bit)) {
            add(bit, i);
        }
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    f[0] = 0;
    FOR(i,1,100000) f[i] = i * (i+1LL) / 2;
    while (cin >> n >> q) {
        FOR(i,1,n) cin >> a[i];
        res = 0;
        init();
        while (q--) {
            int u, val; cin >> u >> val;
            REP(bit,20) {
                if (CONTAIN(val, bit) && !CONTAIN(a[u], bit)) {
                    add(bit, u);
                }
                if (!CONTAIN(val, bit) && CONTAIN(a[u], bit)) {
                    remove(bit, u);
                }
            }
            a[u] = val;
            cout << res << "\n";
        }
    }
    return 0;
}
