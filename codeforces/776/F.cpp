
#include <sstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define PI (2 * acos((double)0))
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define y0 u9cqu3jioajc

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 300111;
vector<int> ke[MN];  // 0-based index
struct PolygonRegion {  // everything is 0-based index
    int n;
    set<int> vertices;
    vector< pair<int,int> > diagonals;
    vector< vector<int> > regions;

    PolygonRegion(int n) : n(n) {
        vertices.clear();
        REP(i,n) vertices.insert(i);
        diagonals.clear();
    }

    void addEdge(int a, int b) {
        assert(a != b);
        if (a > b) swap(a, b);
        assert(a + 1 != b);
        if (a == n) assert(b != 1);

        diagonals.emplace_back(b - a, a);
    }

    void init() {
        diagonals.emplace_back(n-1, 0);
        regions.clear();

        REP(i,n+1) ke[i].clear();

        sort(diagonals.begin(), diagonals.end());
        REP(idiag,SZ(diagonals)) {
            auto diagonal = diagonals[idiag];

            // (s, t) = current diagonal
            int s = diagonal.second;
            int t = s + diagonal.first;

            // extract polygon
            auto it = vertices.find(s); ++it;
            vector<int> cur;
            cur.push_back(s);
            while (true) {
                if (*it == t) break;
                cur.push_back(*it);
                vertices.erase(it++);
            }
            cur.push_back(t);

            // update adjacent list.
            REP(j,SZ(cur)-1) {  // consider all edges except (s, t)
                if (cur[j+1] - cur[j] > 1) {
                    int low = lower_bound(diagonals.begin(), diagonals.end(), make_pair(cur[j+1] - cur[j], cur[j])) - diagonals.begin();
                    ke[low].push_back(idiag);
                    ke[idiag].push_back(low);
                }
            }

            regions.push_back(cur);
        }
    }
};

vector< pair< vector<int>, int > > id;

bool block[MN];
int color[MN], len[MN], tr[MN];

void dfs(int u, int fu, int& last) {
    for(int v : ke[u]) {
        if (v == fu || block[v]) continue;

        len[v] = len[u] + 1;
        tr[v] = u;
        dfs(v, u, last);

        if (len[v] > len[last]) last = v;
    }
}

void solve(int root, int c) {
    len[root] = 0;
    tr[root] = root;
    int last = root;
    dfs(root, -1, last);

    len[last] = 0;
    dfs(last, -1, last);

    REP(turn,len[last]/2) last = tr[last];

    color[last] = c;
    block[last] = true;

    for(int u : ke[last]) {
        if (!block[u]) solve(u, c+1);
    }
}

int32_t main() {
    int n, m;
    while (GI(n) == 1 && GI(m) == 1) {
        PolygonRegion a(n);
        while (m--) {
            int u, v; GI(u); GI(v);
            --u; --v;
            a.addEdge(u, v);
        }
        a.init();

        /*
        cout << "All regions: " << endl;
        REP(i,SZ(a.regions)) {
            auto region = a.regions[i];
            PR0(region, SZ(region));
            PR0(ke[i], SZ(ke[i]));
        }
        */

        id.resize(SZ(a.regions));
        REP(i,SZ(a.regions)) {
            auto region = a.regions[i];
            sort(region.begin(), region.end(), greater<int>());

            id[i].first = region;
            id[i].second = i;
        }
        sort(id.begin(), id.end());

        memset(block, 0, sizeof block);
        solve(0, 1);

        REP(i,SZ(id)) {
            printf("%lld ", color[id[i].second]);
        }
        puts("");
        puts("");
    }
}
