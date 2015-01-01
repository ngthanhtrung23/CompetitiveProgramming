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

const int MN = 200111;
struct Domino {
    int pos, len;
} dominoes[MN];

struct Query {
    int x, y;
    int res;
} queries[MN];

int nDomino, nQuery;
vector<int> queryAt[MN];

struct Node {
    int sum;
    bool covered;
} it[MN * 8];

int c[MN * 2], s;

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)

void down(int i, int l, int r, int mid) {
    if (it[i].covered) {
        it[CT(i)].covered = true;
        it[CT(i)].sum = c[mid+1] - c[l];

        it[CP(i)].covered = true;
        it[CP(i)].sum = c[r+1] - c[mid+1];

        it[i].covered = false;
    }
}

void up(int i) {
    it[i].sum = it[CT(i)].sum + it[CP(i)].sum;
}

void update(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].covered = true;
        it[i].sum = c[r+1] - c[l];
        return ;
    }
    int mid = (l + r) >> 1;
    down(i, l, r, mid);
    update(CT(i), l, mid, u, v);
    update(CP(i), mid+1, r, u, v);
    up(i);
}

int get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].sum;
    int mid = (l + r) >> 1;
    down(i, l, r, mid);
    int res = get(CT(i), l, mid, u, v) + get(CP(i), mid+1, r, u, v);
    up(i);
    return res;
}


int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> nDomino) {
        FOR(i,1,nDomino) queryAt[i].clear();
        memset(it, 0, sizeof it);

        s = 0;
        FOR(i,1,nDomino) {
            cin >> dominoes[i].pos >> dominoes[i].len;
            c[++s] = dominoes[i].pos;
            c[++s] = dominoes[i].pos + dominoes[i].len;
        }
        sort(c+1, c+s+1);
        s = unique(c+1, c+s+1) - c - 1;
//        PR(c, s);

        cin >> nQuery;
        FOR(i,1,nQuery) {
            cin >> queries[i].x >> queries[i].y;
            queryAt[queries[i].x].push_back(i);
        }

        FORD(i,nDomino,1) {
            // Add this domino
            int u = lower_bound(c+1, c+s+1, dominoes[i].pos) - c;
            int v = lower_bound(c+1, c+s+1, dominoes[i].pos+dominoes[i].len) - c;
            update(1, 1, s, u, v - 1);
//            cout << "cover: " << u << ' ' << v-1 << endl;

            // Answer queries
            for(int id : queryAt[i]) {
                int u = lower_bound(c+1, c+s+1, dominoes[queries[id].x].pos) - c;
                int v = lower_bound(c+1, c+s+1, dominoes[queries[id].y].pos) - c;
                queries[id].res = dominoes[queries[id].y].pos - dominoes[queries[id].x].pos - get(1, 1, s, u, v - 1);
//                cout << "get: " << id << " " << u << ' ' << v-1 << " --> " << get(1, 1, s, u, v-1) << endl;
            }
        }

        FOR(i,1,nQuery) cout << queries[i].res << "\n";
    }
    return 0;
}
