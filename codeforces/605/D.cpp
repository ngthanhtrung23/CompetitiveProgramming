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

const int MN = 100111;
const int INF = 1000111000;

struct Spell {
    int a, b, c, d;
    friend istream& operator >> (istream& cin, Spell& x) {
        cin >> x.a >> x.b >> x.c >> x.d;
        return cin;
    }
} a[MN];
int cx[MN], cy[MN], sx, sy;

int n;

set< pair<int,int> > it[MN * 4];

void RR() {
    sx = 0;
    cx[++sx] = 0;
    cx[++sx] = INF;
    FOR(i,1,n) {
        cx[++sx] = a[i].a;
    }
    sort(cx+1, cx+sx+1);
    sx = unique(cx+1, cx+sx+1) - cx - 1;
//    PR(cx, sx);
    FOR(i,1,n) {
        a[i].a = lower_bound(cx+1, cx+sx+1, a[i].a) - cx;
        a[i].c = upper_bound(cx+1, cx+sx+1, a[i].c) - cx - 1;
    }

    sy = 0;
    cy[++sy] = 0;
    cy[++sy] = INF;
    FOR(i,1,n) cy[++sy] = a[i].b;
    sort(cy+1, cy+sy+1);
    sy = unique(cy+1, cy+sy+1) - cy - 1;
//    PR(cy, sy);

    FOR(i,1,n) {
        a[i].b = lower_bound(cy+1, cy+sy+1, a[i].b) - cy;
        a[i].d = upper_bound(cy+1, cy+sy+1, a[i].d) - cy - 1;
    }
}

void add(int i, int l, int r, int x, int y, int id) {
    if (x < l || r < x) return ;

    it[i].insert(make_pair(y, id));
    if (l == r) return ;

    int mid = (l + r) >> 1;
    add(i<<1, l, mid, x, y, id);
    add(i<<1|1, mid+1, r, x, y, id);
}

void remove(int i, int l, int r, int x, int y, int id) {
    if (x < l || r < x) return ;
    
    it[i].erase(make_pair(y, id));
    if (l == r) return ;

    int mid = (l + r) >> 1;
    remove(i<<1, l, mid, x, y, id);
    remove(i<<1|1, mid+1, r, x, y, id);
}

pair<int,int> getMinY(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return make_pair(INF, INF);
    if (u <= l && r <= v) {
        if (it[i].empty()) return make_pair(INF, INF);
        return *it[i].begin();
    }

    int mid = (l + r) >> 1;
    return min(getMinY(i<<1, l, mid, u, v),
            getMinY(i<<1|1, mid+1, r, u, v));
}

int visited[MN], tr[MN];

void trace(int u) {
    if (u == 0) return ;
    trace(tr[u]);
    cout << u << ' ';
}

void bfs() {
    queue<int> qu;
    memset(visited, -1, sizeof visited);
    visited[0] = 0;
    qu.push(0);

    a[0].c = 1;
    a[0].d = 1;

    while (!qu.empty()) {
        int u = qu.front();
        int c = a[u].c, d = a[u].d;
        qu.pop();

        if (u == n) {
            cout << visited[u] << endl;
            trace(u);
            cout << endl;
            return;
        }

        while (true) {
            auto p = getMinY(1, 1, sx, 1, c);
            if (p.first > d) break;

            int v = p.second;
//            cout << u << " --> " << v << endl;
            remove(1, 1, sx, a[v].a, a[v].b, v);

            visited[v] = visited[u] + 1;
            tr[v] = u;
            qu.push(v);
        }
    }
    
    cout << -1 << endl;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        RR();
        FOR(i,1,n) add(1, 1, sx, a[i].a, a[i].b, i);
        bfs();
    }
}
