#include <bits/stdc++.h>
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

const int MN = 300111;
const int INF = 1e9;

vector< pair<int,int> > it[1100111], all;
int n;

void build(int i, int l, int r) {
    it[i].push_back(make_pair(INF, INF));

    if (l == r) return ;
    int mid = (l + r) >> 1;
    build(i<<1, l, mid);
    build(i<<1|1, mid+1, r);
}

void update(int i, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].push_back(make_pair(val, min(val, it[i].back().second)));
        return ;
    }
    int mid = (l + r) >> 1;
    update(i<<1, l, mid, u, v, val);
    update(i<<1|1, mid+1, r, u, v, val);
}
void rem(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].pop_back();
        return ;
    }
    int mid = (l + r) >> 1;
    rem(i<<1, l, mid, u, v);
    rem(i<<1|1, mid+1, r, u, v);
}

int get(int i, int l, int r, int u) {
    if (l == r) return it[i].back().second;

    int res = it[i].back().second;

    int mid = (l + r) >> 1;
    if (u <= mid) res = min(res, get(i<<1, l, mid, u));
    else res = min(res, get(i<<1|1, mid+1, r, u));
    return res;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("invazia.in", "r", stdin);
    freopen("invazia.out", "w", stdout);

    int q;
    scanf("%d%d", &n, &q);
    build(1, 1, n);

    while (q--) {
        char c = ' ';
        while (c < 'A' || c > 'Z') scanf("%c", &c);

        if (c == 'I') {
            int u, v, val; scanf("%d%d%d", &u, &v, &val);
            update(1, 1, n, u, v, val);

            all.push_back(make_pair(u, v));
        }
        else if (c == 'R') {
            int u; scanf("%d", &u);
            int t = get(1, 1, n, u);
            if (t == INF) puts("GUITZZZ!");
            else printf("%d\n", get(1, 1, n, u));
        }
        else {
            rem(1, 1, n, all.back().first, all.back().second);
            all.pop_back();
        }
    }
}
