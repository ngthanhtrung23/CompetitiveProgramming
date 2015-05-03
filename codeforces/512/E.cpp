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

const int MN = 1011;
int n;

bool c[MN][MN];

vector< pair<int,int> > res;
void go(int u, int v, bool first) {
    if (u+1 == v) return ;

    FOR(x,u+1,v-1)
        if (c[u][x] && c[x][v]) {
            res.push_back((!first) ? make_pair(1, x) : make_pair(u, v));
            go(u, x, first);
            go(x, v, first);
            break;
        }
}

vector< pair<int,int> > solve(const vector< pair<int,int> >& edges, bool first) {
    res.clear();
    memset(c, 0, sizeof c);
    for(auto e : edges) c[e.first][e.second] = c[e.second][e.first] = true;

//    FOR(i,1,n) PR(c[i], n);

    int last = 2;
    FOR(i,3,n) if (c[1][i]) {
        go(last, i, first);
        last = i;
    }

//    cout << "RES = " << endl;
//    for(auto x : res) cout << x.first << ' ' << x.second << endl;
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        vector< pair<int,int> > edges[2];
        REP(turn,2) {
            FOR(i,1,n) {
                int j = (i == n) ? 1 : (i+1);
                edges[turn].push_back(make_pair(i, j));
            }
            FOR(i,1,n-3) {
                int u, v; cin >> u >> v;
                edges[turn].push_back(make_pair(u, v));
            }
        }

        auto ans1 = solve(edges[0], true);
        auto ans2 = solve(edges[1], false);

        cout << ans1.size() + ans2.size() << endl;
        reverse(ans2.begin(), ans2.end());
        for(auto x : ans1) cout << x.first << ' ' << x.second << endl;
        for(auto x : ans2) cout << x.first << ' ' << x.second << endl;
    }
    return 0;
}
