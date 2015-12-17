
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

const int MN = 1000111;

struct Node {
    int ln, nn, add;
} it[MN * 4];

int n, a[MN], x[MN];
vector<int> ke[MN];
int getIn[MN], getOut[MN], dfsNum;

void dfs(int u) {
    getIn[u] = ++dfsNum;
    for(int v : ke[u]) dfs(v);
    getOut[u] = dfsNum;
}

void up(int i) {
    it[i].ln = max(it[i<<1].ln, it[i<<1|1].ln);
    it[i].nn = min(it[i<<1].nn, it[i<<1|1].nn);
}

void build(int i, int l, int r) {
    if (l == r) {
        it[i].ln = it[i].nn = x[l];
        it[i].add = 0;
        return ;
    }
    int mid = (l + r) >> 1;
    build(i<<1, l, mid);
    build(i<<1|1, mid+1, r);
    up(i);
    it[i].add = 0;
}

void add(int i, int val) {
    it[i].ln += val;
    it[i].nn += val;
    it[i].add += val;
}

void down(int i) {
    if (it[i].add) {
        add(i<<1, it[i].add);
        add(i<<1|1, it[i].add);
        it[i].add = 0;
    }
}

void update(int i, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        add(i, val);
        return ;
    }
    down(i);
    int mid = (l + r) >> 1;
    update(i<<1, l, mid, u, v, val);
    update(i<<1|1, mid+1, r, u, v, val);
    up(i);
}

const int INF = 1000111000;
pair<int,int> get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return make_pair(-INF, INF);
    if (u <= l && r <= v) {
        return make_pair(it[i].ln, it[i].nn);
    }
    down(i);
    int mid = (l + r) >> 1;
    auto left = get(i<<1, l, mid, u, v);
    auto right = get(i<<1|1, mid+1, r, u, v);
    up(i);

    return make_pair(
            max(left.first, right.first),
            min(left.second, right.second));
}

int main() {
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        scanf("%d", &n);
        dfsNum = 0;
        FOR(i,1,n) ke[i].clear();

        FOR(i,2,n) {
            int u; scanf("%d", &u);
            ke[u].push_back(i);
        }
        FOR(i,1,n) scanf("%d", &a[i]);

        dfs(1);
        FOR(i,1,n) x[getIn[i]] = a[i];
        build(1, 1, n);
//        PR(getIn, n);
//        PR(getOut, n);
        int q; scanf("%d", &q);
        while (q--) {
            char typ = ' '; while (typ < 'A' || typ > 'Z') scanf("%c", &typ);
            if (typ == 'Q') {
                int u; scanf("%d", &u);
                auto p = get(1, 1, n, getIn[u], getOut[u]);
                printf("%d\n", p.first - p.second);
            }
            else {
                int u, val; scanf("%d%d", &u, &val);
                update(1, 1, n, getIn[u], getOut[u], val);
            }
        }
    }
}
