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

const int MN = 100111;

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

enum Border {LEFT, UP, RIGHT, LOOP};

struct Node {
    pair<int,int> to[11];
} it[MN * 4];

int nRow, nCol, q;

void merge(const Node &a, const Node &b, Node &c) {
    FOR(j,1,nCol) {
        pair<int,int> x = a.to[j];
        if (x.first == LEFT || x.first == RIGHT || x.first == LOOP) {
            c.to[j] = x;
        }
        else {
            c.to[j] = b.to[x.second];
        }
    }
}

char a[MN][13];

void buildRow(int l, Node &it) {
    FOR(j,1,nCol)
        it.to[j] = make_pair(LOOP, -1);
    FOR(j,1,nCol)
        if (a[l][j] == '^') {
            it.to[j] = make_pair(UP, j);
            
            int x = j-1;
            while (a[l][x] == '>') it.to[x] = make_pair(UP, j), --x;
            x = j+1;
            while (a[l][x] == '<') it.to[x] = make_pair(UP, j), ++x;
        }

    int x = 1;
    while (a[l][x] == '<') it.to[x] = make_pair(LEFT, l), ++x;
    x = nCol;
    while (a[l][x] == '>') it.to[x] = make_pair(RIGHT, l), --x;
}

void build(int i, int l, int r) {
    if (l == r) {
        buildRow(l, it[i]);
        return ;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);
    merge(it[CP(i)], it[CT(i)], it[i]);
}

// precondition: u in [l, r]
pair<int,int> get(int i, int l, int r, int u, int v) {
    if (l == r) return it[i].to[v];

    int mid = (l + r) >> 1;
    if (u <= mid) return get(CT(i), l, mid, u, v);
    else {
        pair<int,int> cur = get(CP(i), mid+1, r, u, v);
        if (cur.first == UP) return it[CT(i)].to[cur.second];
        else return cur;
    }
}

void update(int i, int l, int r, int u, int v, char val) {
    if (u < l || r < u) return ;
    if (l == r) {
        a[u][v] = val;
        buildRow(l, it[i]);
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, v, val);
    update(CP(i), mid+1, r, u, v, val);
    merge(it[CP(i)], it[CT(i)], it[i]);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> nRow >> nCol >> q) {
        FOR(i,1,nRow) FOR(j,1,nCol) cin >> a[i][j];
        build(1, 1, nRow);
        while (q--) {
            char typ; cin >> typ;
            if (typ == 'A') {
                int u, v; cin >> u >> v;
                pair<int,int> cur = get(1, 1, nRow, u, v);
                if (cur.first == LOOP) cout << "-1 -1\n";
                else if (cur.first == UP) cout << "0 " << cur.second << "\n";
                else if (cur.first == LEFT) cout << cur.second << " 0" << "\n";
                else cout << cur.second << ' ' << nCol + 1 << "\n";
            }
            else {
                int u, v; char val; cin >> u >> v >> val;
                update(1, 1, nRow, u, v, val);
            }
        }
    }
    return 0;
}
