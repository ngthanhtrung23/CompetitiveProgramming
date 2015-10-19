
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 200111;

int n, k, c[MN], nc;
pair<int,int> a[MN];

struct Node {
    int ln, add;
} it[MN * 4];

void RR() {
    nc = 0;
    FOR(i,1,n) {
        c[++nc] = a[i].first;
        c[++nc] = a[i].second;
    }
    sort(c+1, c+nc+1);
    nc = unique(c+1, c+nc+1) - c - 1;

    FOR(i,1,n) {
        a[i].first = lower_bound(c+1, c+nc+1, a[i].first) - c;
        a[i].second = lower_bound(c+1, c+nc+1, a[i].second) - c;
    }
}

void down(int i, int l, int r, int mid) {
    if (it[i].add) {
        int t = it[i].add;
        it[i<<1].add += t;
        it[i<<1].ln  += t;

        it[i<<1|1].add += t;
        it[i<<1|1].ln  += t;
        it[i].add = 0;
    }
}

void update(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].add += 1;
        it[i].ln += 1;
        return ;
    }
    int mid = (l + r) >> 1;
    down(i, l, r, mid);

    update(i<<1, l, mid, u, v);
    update(i<<1|1, mid+1, r, u, v);

    it[i].ln = max(it[i<<1].ln, it[i<<1|1].ln);
}

int get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].ln;

    int mid = (l + r) >> 1;
    down(i, l, r, mid);

    int res = max(
            get(i<<1, l, mid, u, v),
            get(i<<1|1, mid+1, r, u, v)
            );

    it[i].ln = max(it[i<<1].ln, it[i<<1|1].ln);
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &n, &k) == 2) {
        FOR(i,1,n) {
            scanf("%d%d", &a[i].second, &a[i].first);
            --a[i].first;
        }
        RR();
        sort(a+1, a+n+1);
        memset(it, 0, sizeof it);

        int res = 0;
        FOR(i,1,n) {
            if (get(1, 1, nc, a[i].second, a[i].first) < k) {
                update(1, 1, nc, a[i].second, a[i].first);
                ++res;
            }
        }
        cout << res << endl;
    }
}

