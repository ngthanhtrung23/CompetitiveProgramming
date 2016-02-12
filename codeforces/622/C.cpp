
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
vector<int> it[MN * 4];
vector<int> id[MN * 4];
int a[MN];

void add(int i, int x) {
    if (!it[i].empty() && it[i].back() == a[x]) return ;
    it[i].push_back(a[x]);
    id[i].push_back(x);
}

void build(int i, int l, int r) {
    if (l == r) {
        it[i].clear();
        it[i].push_back(a[l]);
        id[i].push_back(l);
        return ;
    }
    int mid = (l + r) >> 1;
    int left = i<<1;
    int right = i<<1|1;

    build(left, l, mid);
    build(right, mid+1, r);

    it[i].clear();
    int x = 0, y = 0;
    while (x < SZ(it[left]) || y < SZ(it[right])) {
        if (x >= SZ(it[left])) {
            add(i, id[right][y++]);
        }
        else if (y >= SZ(it[right])) {
            add(i, id[left][x++]);
        }
        else if (it[left][x] <= it[right][y]) {
            add(i, id[left][x++]);
        }
        else {
            add(i, id[right][y++]);
        }
    }

    if (SZ(it[i]) > 2) {
        it[i].resize(2);
        id[i].resize(2);
    }
}

void get(int i, int l, int r, int u, int v, int x) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        if (SZ(it[i]) == 1 && *it[i].begin() == x) return ;

        if (*it[i].begin() != x) throw *id[i].begin();
        throw id[i].back();
        return ;
    }
    int mid = (l + r) >> 1;
    get(i<<1, l, mid, u, v, x);
    get(i<<1|1, mid+1, r, u, v, x);
}

int main() {
    int n, q;
    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) scanf("%d", &a[i]);
        build(1, 1, n);
        while (q--) {
            int l, r, x; scanf("%d%d%d", &l, &r, &x);
            try {
                get(1, 1, n, l, r, x);
                puts("-1");
            }
            catch (int e) {
                printf("%d\n", e);
            }
        }
    }
}
