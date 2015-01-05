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

int n, a[MN], b[MN], c[MN];
vector< pair<int,int> > add[MN], rem[MN];

struct Node {
    int cover;
    pair<int,int> ln;
} it[MN * 4];

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

void down(int i) {
    if (it[i].cover) {
        int k = it[i].cover;
        it[CT(i)].cover += k;
        it[CT(i)].ln.first += k;

        it[CP(i)].cover += k;
        it[CP(i)].ln.first += k;

        it[i].cover = 0;
    }
}

void up(int i) {
    it[i].ln = max(it[CT(i)].ln, it[CP(i)].ln);
}

void build(int i, int l, int r) {
    it[i].ln = make_pair(0, l);
    it[i].cover = 0;
    if (l == r) return ;

    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);
}

void update(int i, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].cover += val;
        it[i].ln.first += val;
        return ;
    }
    int mid = (l + r) >> 1;
    down(i);
    update(CT(i), l, mid, u, v, val);
    update(CP(i), mid+1, r, u, v, val);
    up(i);
}

pair<int,int> get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return make_pair(0, 0);
    if (u <= l && r <= v) return it[i].ln;
    int mid = (l + r) >> 1;
    down(i);

    auto res = max(get(CT(i), l, mid, u, v), get(CP(i), mid+1, r, u, v));
    up(i);
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,300000) {
            add[i].clear();
            rem[i].clear();
        }
        FOR(i,1,n) {
            cin >> a[i] >> b[i] >> c[i];
            add[a[i]].push_back(make_pair(b[i], c[i]));
            rem[b[i]].push_back(make_pair(b[i], c[i]));
        }
        int res = 0, saveX = 0, saveY = 0;
        build(1, 1, 300000);
        FOR(L,1,300000) {
            for(auto t : add[L]) {
                update(1, 1, 300000, t.first, t.second, 1);
            }
            pair<int,int> cur = get(1, 1, 300000, L, 300000);
            if (cur.first > res) {
                res = cur.first;
                saveX = L;
                saveY = cur.second;
            }
            for(auto t : rem[L]) {
                update(1, 1, 300000, t.first, t.second, -1);
            }
        }

        cout << res << endl;
//        DEBUG(saveX);
//        DEBUG(saveY);
        FOR(i,1,n)
            if (a[i] <= saveX && saveX <= b[i] && b[i] <= saveY && saveY <= c[i])
                cout << i << ' ';
        cout << endl;
    }
    return 0;
}
