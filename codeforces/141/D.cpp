
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
using namespace std;

const int MN = 200111;

int n, L;
struct Ramp {
    int x, d, t, p;
} a[MN];

int c[MN], nc;
vector< pair<pair<int,int>, int> > ke[MN];

void addEdge(int u, int v, int c, int typ) {
    ke[u].push_back(make_pair(make_pair(v, c), typ));
}

void RR() {
    c[++nc] = 0;
    c[++nc] = L;
    FOR(i,1,n) if (a[i].x >= a[i].p) {
        c[++nc] = a[i].x - a[i].p;
        c[++nc] = a[i].x + a[i].d;
    }
    sort(c+1, c+nc+1);
    nc = unique(c+1, c+nc+1) - c - 1;

    FOR(i,1,nc) ke[i].clear();

    FOR(i,1,nc-1) {
        addEdge(i, i+1, c[i+1] - c[i], 0);
        addEdge(i+1, i, c[i+1] - c[i], 0);
    }
    FOR(i,1,n) if (a[i].x >= a[i].p) {
        int u = lower_bound(c+1, c+nc+1, a[i].x - a[i].p) - c;
        int v = lower_bound(c+1, c+nc+1, a[i].x + a[i].d) - c;
        addEdge(u, v, a[i].p + a[i].t, i);
    }
}

int f[MN], tru[MN], trt[MN];
vector<int> res;

void trace(int v) {
    if (v == 1) return ;

    int u = tru[v];
    trace(u);
    if (trt[v]) res.push_back(trt[v]);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> L) {
        FOR(i,1,n) cin >> a[i].x >> a[i].d >> a[i].t >> a[i].p;
        RR();

        FOR(i,1,nc) f[i] = 1000111000;
        f[1] = 0;
        set< pair<int, int> > s;
        s.insert(make_pair(0, 1));
        while (!s.empty()) {
            int l = s.begin()->first, u = s.begin()->second;
            s.erase(s.begin());
            if (l != f[u]) continue;

            for(auto e : ke[u]) {
                int v = e.first.first, c = e.first.second;

                if (f[v] > f[u] + c) {
                    f[v] = f[u] + c;
                    s.insert(make_pair(f[v], v));
                    tru[v] = u;
                    trt[v] = e.second;
                }
            }
        }
        cout << f[nc] << endl;
        res.clear();
        trace(nc);
        cout << res.size() << endl;
        for(auto x : res) cout << x << ' '; cout << endl;
    }
}

