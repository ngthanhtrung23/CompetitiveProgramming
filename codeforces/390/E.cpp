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

const int MN = 4000111;

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)
struct IT {
    long long x[MN * 4], sum[MN * 4];

    void init() {
        memset(x, 0, sizeof x);
    }

    void down(int i, int l, int r, int mid) {
        if (x[i]) {
            x[CT(i)] += x[i];
            x[CP(i)] += x[i];
            sum[CT(i)] += x[i] * (mid - l + 1LL);
            sum[CP(i)] += x[i] * (r - mid + 0LL);
            x[i] = 0;
        }
    }
    void up(int i) {
        sum[i] = sum[CT(i)] + sum[CP(i)];
    }
    void update(int i, int l, int r, int u, int v, long long val) {
        if (v < l || r < u) return ;
        if (u <= l && r <= v) {
            x[i] += val;
            sum[i] += val * (r - l + 1LL);
            return ;
        }
        int mid = (l + r) >> 1;
        down(i, l, r, mid);

        update(CT(i), l, mid, u, v, val);
        update(CP(i), mid+1, r, u, v, val);
        up(i);
    }

    long long get(int i, int l, int r, int u, int v) {
        if (v < l || r < u) return 0;
        if (u <= l && r <= v) return sum[i];
        int mid = (l + r) >> 1;

        down(i, l, r, mid);
        long long res = get(CT(i), l, mid, u, v) + get(CP(i), mid+1, r, u, v);
        up(i);
        return res;
    }
} rows, cols;

int nRow, nCol, q;
long long total;
void update(int i1, int j1, int i2, int j2, long long val) {
    total += val * (i2 - i1 + 1LL) * (j2 - j1 + 1LL);
    rows.update(1, 1, nRow, i1, i2, val * (j2 - j1 + 1LL));
    cols.update(1, 1, nCol, j1, j2, val * (i2 - i1 + 1LL));
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> nRow >> nCol >> q) {
        nRow = nCol = max(nRow, nCol);
        rows.init(); cols.init();
        total = 0;
        while (q--) {
            int typ; cin >> typ;
            if (typ == 0) {
                int i1, j1, i2, j2;
                long long val;
                cin >> i1 >> j1 >> i2 >> j2 >> val;
                update(i1, j1, i2, j2, val);
            }
            else {
                int i1, j1, i2, j2;
                cin >> i1 >> j1 >> i2 >> j2;
                cout << rows.get(1, 1, nRow, i1, i2) + cols.get(1, 1, nCol, j1, j2) - total << "\n";
            }
        }
    }
    return 0;
}

