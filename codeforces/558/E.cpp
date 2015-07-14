
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

const int MN = 100111;

struct Node {
    int cnt[30];
    int sorted;
} it[MN * 4];
int n, q;
string s;

int cnt[30];

void refine(int i) {
    REP(c,27)
        it[i].cnt[c] = it[i<<1].cnt[c] + it[i<<1|1].cnt[c];
}

void build(int i, int l, int r) {
    if (l == r) {
        int u = s[l] - 'a';
        it[i].cnt[u]++;
        return ;
    }
    int mid = (l + r) >> 1;
    build(i<<1, l, mid);
    build(i<<1|1, mid+1, r);

    refine(i);
}

void down(int i, int l, int r, int mid) {
    if (it[i].sorted) {
        it[i<<1].sorted = it[i].sorted;
        it[i<<1|1].sorted = it[i].sorted;

        int cur;
        if (it[i].sorted == 1) cur = 'a' - 'a';
        else cur = 'z' - 'a';

        int left_size = mid - l + 1;
        memset(it[i<<1].cnt, 0, sizeof it[i<<1].cnt);
        memset(it[i<<1|1].cnt, 0, sizeof it[i<<1|1].cnt);
        if (it[i].sorted == 1) {
            REP(u,27) {
                if (left_size) {
                    int can = min(left_size, it[i].cnt[u]);
                    it[i<<1].cnt[u] = can;
                    left_size -= can;
                    it[i].cnt[u] -= can;
                }
                if (left_size == 0) {
                    int can = it[i].cnt[u];
                    it[i<<1|1].cnt[u] = can;
                }
            }
        }
        else {
            FORD(u,26,0) {
                if (left_size) {
                    int can = min(left_size, it[i].cnt[u]);
                    it[i<<1].cnt[u] = can;
                    left_size -= can;
                    it[i].cnt[u] -= can;
                }
                if (left_size == 0) {
                    int can = it[i].cnt[u];
                    it[i<<1|1].cnt[u] = can;
                }
            }
        }

        it[i].sorted = 0;
        refine(i);
    }
}

void get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        REP(c,27) cnt[c] += it[i].cnt[c];
        return ;
    }
    int mid = (l + r) >> 1;
    down(i, l, r, mid);

    get(i<<1, l, mid, u, v);
    get(i<<1|1, mid+1, r, u, v);

    refine(i);
}

int cur;
void update(int i, int l, int r, int u, int v, int typ) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        int need = r - l + 1;
        memset(it[i].cnt, 0, sizeof it[i].cnt);
        it[i].sorted = typ;
        while (need > 0) {
            while (cnt[cur] == 0) {
                cur += typ;
            }
            int can = min(need, cnt[cur]);
            it[i].cnt[cur] = can;
            need -= can;
            cnt[cur] -= can;
        }
        return ;
    }
    int mid = (l + r) >> 1;
    down(i, l, r, mid);

    update(i<<1, l, mid, u, v, typ);
    update(i<<1|1, mid+1, r, u, v, typ);

    refine(i);
}

void print(int i, int l, int r) {
    if (l == r) {
        REP(c,27) if (it[i].cnt[c]) {
            cout << (char) ('a' + c);
        }
        return ;
    }
    if (it[i].sorted == 1) {
        REP(c,27) if (it[i].cnt[c]) {
            char a = (char) ('a' + c);
            while (it[i].cnt[c]--) cout << a;
        }
        return;
    }
    if (it[i].sorted == -1) {
        FORD(c,26,0) if (it[i].cnt[c]) {
            char a = (char) ('a' + c);
            while (it[i].cnt[c]--) cout << a;
        }
        return ;
    }
    int mid = (l + r) >> 1;
    print(i<<1, l, mid);
    print(i<<1|1, mid+1, r);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> q) {
        cin >> s; s = " " + s;
        memset(it, 0, sizeof it);
        build(1, 1, n);
        FOR(i,1,q) {
            int u, v, typ; cin >> u >> v >> typ;
            if (typ == 0) typ = -1;
            memset(cnt, 0, sizeof cnt);
            get(1, 1, n, u, v);

//            cout << u << ' ' << v << ' ' << typ << endl;
//            PR0(cnt, 27);

            if (typ == 1) cur = 'a' - 'a';
            else cur = 'z' - 'a';
            update(1, 1, n, u, v, typ);
//            PR0(cnt, 27);
        }
        print(1, 1, n);
        cout << endl;
    }
}
