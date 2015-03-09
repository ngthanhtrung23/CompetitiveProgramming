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
int n, m;
vector< pair<int,int> > ke[MN];
vector<int> busy[MN];
int d[2][MN];

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,n) {
            ke[i].clear();
            busy[i].clear();
        }
        FOR(i,1,m) {
            int u, v, c; scanf("%d%d%d", &u, &v, &c);
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));
        }
        FOR(i,1,n) {
            int k; scanf("%d", &k);
            while (k--) {
                int u; scanf("%d", &u);
                busy[i].push_back(u);
            }
            busy[i].push_back(1000111000);
            sort(busy[i].begin(), busy[i].end());
        }
        REP(t,2) FOR(i,1,n) d[t][i] = 1000111000;
        d[0][1] = 0;
        set< pair<int, pair<int,int> > > s;
        s.insert(make_pair(0, make_pair(0, 1)));
        while (!s.empty()) {
            int l = s.begin()->first;
            int t = s.begin()->second.first;
            int u = s.begin()->second.second;

            s.erase(s.begin());
            if (l != d[t][u]) continue;

            if (t == 0) {
                int l2 = l;
                while (*lower_bound(busy[u].begin(), busy[u].end(), l2) == l2) ++l2;
                if (d[1][u] > l2) {
                    d[1][u] = l2;
                    s.insert(make_pair(l2, make_pair(1, u)));
                }
            }
            else {
                for(auto e : ke[u]) {
                    int v = e.first, c = e.second;
                    if (d[0][v] > d[1][u] + c) {
                        d[0][v] = d[1][u] + c;
                        s.insert(make_pair(d[0][v], make_pair(0, v)));
                    }
                }
            }
        }
        if (d[0][n] == 1000111000) d[0][n] = -1;
        cout << d[0][n] << endl;
    }
    return 0;
}

