
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

const int MN = 1000111;

int n, m, b[MN], cnt[MN], bad, id[MN];
long long a[MN];
set<long long> res;

long long dist(int u, int v) {
    if (u < v) return a[v] - a[u];
    else return a[u] - a[v];
}

void init() {
    FOR(i,1,n) id[i] = i;

    int dir = -1;
    FOR(i,n+1,MN-1) {
        id[i] = id[i-1] + dir;
        if (id[i] == 1) dir = 1;
        else if (id[i] == n) dir = -1;
    }
//    PR(id, 20);

    FOR(i,n+1,MN-1) {
        a[i] = a[i-1] + dist(id[i], id[i-1]);
    }
//    PR(a, 20);
}

void reduce(int u) {
    if (cnt[u] == 0) ++bad;
    --cnt[u];
    if (cnt[u] == 0) --bad;
}

void add(int u) {
    if (cnt[u] == 0) ++bad;
    ++cnt[u];
    if (cnt[u] == 0) --bad;
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        init();

        memset(cnt, 0, sizeof cnt);
        scanf("%d", &m);
        FOR(i,1,m) {
            scanf("%d", &b[i]);
            cnt[b[i]]++;
        }
        res.clear();

        bad = 0;
        FOR(i,1,n) if (cnt[i]) ++bad;

        int from = 1, to = m;
        FOR(i,1,m) {
            reduce(id[i]);
        }

        if (bad == 0) res.insert(a[to] - a[from]);
        FOR(i,2,n+n+n) {
            add(id[from]);
            ++from;
            ++to;
            reduce(id[to]);

            if (bad == 0) res.insert(a[to] - a[from]);
        }

        if (res.size() == 1) cout << *res.begin() << endl;
        else cout << -1 << endl;
    }
    return 0;
}
