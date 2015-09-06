
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cerr << #x << " = "; cerr << (x) << endl; }
#define PR(a,n) { cerr << #a << " = "; FOR(_,1,n) cerr << a[_] << ' '; cerr << endl; }
#define PR0(a,n) { cerr << #a << " = "; REP(_,n) cerr << a[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int MN = 100111;

vector< pair<int,int> > ke[MN];
int n, m;
bool visited[MN];
int tr[MN], trc[MN], tr2[MN], len[MN];

int start;
vector<int> all;
void init() {
    memset(len, 0, sizeof len);
    FOR(i,1,n) ke[i].clear();
    memset(visited, 0, sizeof visited);
    memset(tr2, 0, sizeof tr2);
    memset(tr, 0, sizeof tr);
    memset(trc, 0, sizeof trc);
    start = 0;
    all.clear();
}

void trace(int u) {
    all.push_back(u);
    if (u == n) return ;

    if (tr[u]) {
        trace(tr[u]);

        if (trc[u]) start = 1;
        if (start) printf("%d", trc[u]);
    }
    else {
        trace(tr2[u]);
    }

}

int q[MN], first, last;

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        init();
        FOR(i,1,m) {
            int u, v, c; scanf("%d%d%d", &u, &v, &c);
            ++u; ++v;
            ke[u].push_back(make_pair(c, v));
            ke[v].push_back(make_pair(c, u));
        }
        FOR(i,1,n) sort(ke[i].begin(), ke[i].end());

        first = last = 1;
        q[1] = n;
        tr2[n] = n;
        len[n] = 1;
        while (first <= last) {
            int u = q[first++];
            for(auto e : ke[u]) if (e.first == 0) {
                int v = e.second;
                if (!tr2[v]) {
                    len[v] = len[u] + 1;
                    tr2[v] = u;
                    q[++last] = v;
                }
            }
        }
        queue<vector<int> > qu;
        vector<int> t;
        FOR(i,1,last) {
            t.push_back(q[i]);
            visited[q[i]] = true;
        }
        qu.push(t);

        while (!qu.empty()) {
            t = qu.front(); qu.pop();
            REP(turn,10) {
                vector<int> r;

                for(int u : t) {
                    for(auto e : ke[u]) {
                        int v = e.second, c = e.first;
                        if (c != turn) continue;
                        if (!visited[v]) {
                            visited[v] = true;
                            tr[v] = u;
                            trc[v] = c;

                            r.push_back(v);
                        }
                    }
                }
                if (!r.empty()) qu.push(r);
            }
        }

        assert(visited[1]);
        start = 0;
        all.clear();
        trace(1);
        if (!start) puts("0"); else puts("");
        printf("%d\n", all.size());
        for(int x : all) printf("%d ", x-1); puts("");
//        cerr << "-------" << endl;
    }
}
