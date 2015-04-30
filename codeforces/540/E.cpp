
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

const int MN = 600111;
pair<int,int> queries[MN];
int nQuery;

int c[MN], s;

void RR() {
    FOR(i,1,nQuery) c[i] = queries[i].first;
    sort(c+1, c+nQuery+1);
    s = unique(c+1, c+nQuery+1) - c - 1;

    FOR(i,1,nQuery)
        queries[i].first = lower_bound(c+1, c+s+1, queries[i].first) - c;
}

#define _(X) ((X) & (-(X)))

int bit[MN];
int get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

void update(int u, int val) {
    while (u <= s) {
        bit[u] += val;
        u += _(u);
    }
}

int main() {
    int n;
    while (scanf("%d", &n) == 1) {
        map<int,int> a;
        FOR(i,1,n) {
            int u, v; scanf("%d%d", &u, &v);
            if (!a.count(u)) a[u] = u;
            if (!a.count(v)) a[v] = v;

            swap(a[u], a[v]);
        }
//        for(auto p : a) cout << p.first << ' ' << p.second << endl;

        int last = 0;
        nQuery = 0;
        for(auto p : a) {
            if (last + 1 != p.first) {
                int cnt = p.first - 1 - last;
                queries[++nQuery] = make_pair(p.first - 1, cnt);
            }
            queries[++nQuery] = make_pair(p.second, 1);

            last = p.first;
        }
        RR();

        memset(bit, 0, sizeof bit);

        long long res = 0;
        FOR(i,1,nQuery) {
            res += queries[i].second * ((long long) get(s) - get(queries[i].first));

            update(queries[i].first, queries[i].second);
        }
        cout << res << endl;
    }
    return 0;
}
