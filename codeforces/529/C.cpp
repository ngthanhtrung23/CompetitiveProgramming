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

const int MN = 300111;

struct Rook {
    int row, col;
} rooks[MN];

struct Rect {
    int r1, c1, r2, c2, res;
} rects[MN];

int nRow, nCol, nRook, nRect;

int it[MN * 4];

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

vector< pair< pair<int,int>, int > > events;

void solve() {
    memset(it, 0, sizeof it);
    events.clear();
    FOR(i,1,nRook) {
        events.push_back(make_pair(make_pair(rooks[i].col, 0), rooks[i].row));
    }
    FOR(i,1,nRect) {
        events.push_back(make_pair(make_pair(rects[i].c2, 1), i));
    }
    sort(events.begin(), events.end());
    for(auto e : events) {
        if (e.first.second == 0) {
            update(1, 1, nRow, e.second, e.first.first);
        }
        else {
            int id = e.second;
            int x = get(1, 1, nRow, rects[id].r1, rects[id].r2);

            if (x >= rects[id].c1) {
                rects[id].res = 1;
            }
        }
    }
}

void rotate() {
    FOR(i,1,nRook) swap(rooks[i].row, rooks[i].col);
    FOR(i,1,nRect) {
        swap(rects[i].r1, rects[i].c1);
        swap(rects[i].r2, rects[i].c2);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> nRow >> nCol >> nRook >> nRect) {
        nRow = nCol = max(nRow, nCol);
        FOR(i,1,nRook) cin >> rooks[i].row >> rooks[i].col;
        FOR(i,1,nRect) {
            rects[i].res = 0;
            cin >> rects[i].r1 >> rects[i].c1 >> rects[i].r2 >> rects[i].c2;
        }
        solve();
        rotate();
        solve();
        FOR(i,1,nRect) cout << (rects[i].res ? "YES" : "NO") << "\n";
    }
    return 0;
}
