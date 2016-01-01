
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

const int MN = 200111;
int k;

struct Node {
    int lazy;
    int first, last;
    int cnt[11][11];

    void init(int val, int len) {
        lazy = val;
        first = last = val;
        memset(cnt, 0, sizeof cnt);
        cnt[val][val] = len - 1;
    }
} it[MN * 4];

Node operator + (const Node& a, const Node& b) {
    Node res;
    res.lazy = -1;
    res.first = a.first;
    res.last = b.last;

    REP(i,k) REP(j,k) res.cnt[i][j] = a.cnt[i][j] + b.cnt[i][j];

    res.cnt[ a.last ][ b.first ]++;
    return res;
}

int n, q;
char a[MN];

void build(int i, int l, int r) {
    if (l == r) {
        it[i].init(a[l] - 'a', 1);
        it[i].lazy = a[l] - 'a';
        return ;
    }
    int mid = (l + r) >> 1;
    build(i<<1, l, mid);
    build(i<<1|1, mid+1, r);

    it[i] = it[i<<1] + it[i<<1|1];
}

void down(int i, int l, int r, int mid) {
    if (it[i].lazy < 0) return ;
    
    int t = it[i].lazy;

    it[i<<1].init(t, mid - l + 1);
    it[i<<1|1].init(t, r - mid);
}

void update(int i, int l, int r, int u, int v, int c) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].init(c, r - l + 1);
        return ;
    }
    int mid = (l + r) >> 1;
    down(i, l, r, mid);

    update(i<<1, l, mid, u, v, c);
    update(i<<1|1, mid+1, r, u, v, c);

    it[i] = it[i<<1] + it[i<<1|1];
}

char tmp[111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d%d%d\n", &n, &q, &k) == 3) {
        scanf("%s\n", &a[1]);
        build(1, 1, n);

//        REP(i,3) {
//            REP(j,3) cout << it[1].cnt[i][j] << ' ';
//            cout << endl;
//        }

        while (q--) {
            int typ; scanf("%d", &typ);
            if (typ == 1) {
                int u, v; char c;
                scanf("%d%d %c", &u, &v, &c);
                update(1, 1, n, u, v, c - 'a');
            }
            else {
                scanf(" %s\n", &tmp[0]);
                int res = 1;
                REP(i,k) FOR(j,i,k-1) {
                    int x = tmp[i] - 'a';
                    int y = tmp[j] - 'a';

                    res += it[1].cnt[y][x];
                }
                printf("%d\n", res);
            }
        }
    }
}
