
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

int n, m, k, q;
pair<int,int> rook[MN];
int it[MN*8];

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

void update(int i, int l, int r, int u, int val) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i] = val;
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, val);
    update(CP(i), mid+1, r, u, val);
    it[i] = min(it[CT(i)], it[CP(i)]);
}

int get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return MN;
    if (u <= l && r <= v) return it[i];

    int mid = (l + r) >> 1;
    return min(get(CT(i), l, mid, u, v), get(CP(i), mid+1, r, u, v));
}

tuple<int,int,int,int> rect[MN];
int res[MN];
vector<int> updateAt[MN], queryAt[MN];

void solve1() {
    // Check each row has a rook
    FOR(i,1,n) {
        updateAt[i].clear();
        queryAt[i].clear();
    }
    FOR(i,1,k) {
        updateAt[rook[i].second].push_back(rook[i].first);
    }
    FOR(i,1,q) {
        queryAt[get<3>(rect[i])].push_back(i);
    }

    memset(it, 0, sizeof it);
    FOR(i,1,n) {
        // Apply updates
        for(auto u : updateAt[i])
            update(1, 1, m, u, i);

        // Process queries
        for(auto id : queryAt[i]) {
            int l = get<0>(rect[id]);
            int r = get<2>(rect[id]);

            int nn = get(1, 1, n, l, r);
            if (nn >= get<1>(rect[id])) {
//                cout << id << " good row" << endl;
                res[id] = 1;
            }
        }
    }
}

void solve2() {
    // Check each col has a rook
    FOR(i,1,m) {
        updateAt[i].clear();
        queryAt[i].clear();
    }
    FOR(i,1,k) {
        updateAt[rook[i].first].push_back(rook[i].second);
    }
    FOR(i,1,q) {
        queryAt[get<2>(rect[i])].push_back(i);
    }

    memset(it, 0, sizeof it);
    FOR(i,1,n) {
        // Apply updates
        for(auto u : updateAt[i])
            update(1, 1, n, u, i);
        // Process queries
        for(auto id : queryAt[i]) {
            int l = get<1>(rect[id]);
            int r = get<3>(rect[id]);

            int nn = get(1, 1, n, l, r);
            if (nn >= get<0>(rect[id])) {
//                cout << id << " good col" << endl;
                res[id] = 1;
            }
        }
    }
}

int main() {
    while (scanf("%d%d%d%d", &m, &n, &k, &q) == 4) {
        m = n = max(m, n);
        FOR(i,1,k) scanf("%d%d", &rook[i].first, &rook[i].second);

        memset(res, 0, sizeof res);
        FOR(i,1,q) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);
            rect[i] = make_tuple(x1, y1, x2, y2);
        }

        solve1();
        solve2();

        FOR(i,1,q) if (res[i]) puts("YES"); else puts("NO");
    }
    return 0;
}
