#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 500111;
const int MAXV = 500111;
int m, n, nId;

string a[MN], l[MN], r[MN];
map<string,int> id;
string idToStr[MN];

pair<int,int> f[MN];
vector<int> ke[MN];

#define PB push_back

int dfs_num[MAXV + 5], dfs_low[MAXV + 5], visited[MAXV + 5];
int dfsNumberCounter, numSCC;
int V;
vector <int> S;

void init() {
    FOR(i,1,nId) ke[i].clear();
    nId = 0;
    id.clear();

    memset(dfs_num, -1, sizeof dfs_num);
    memset(dfs_low, 0, sizeof dfs_low);
    memset(visited, 0, sizeof visited);
    dfsNumberCounter = numSCC = 0;

}

void store(const string &s) {
    if (!id.count(s)) {
        id[s] = ++nId;
        idToStr[nId] = s;
    }
}

void upcase(string &s) {
    REP(x,s.length())
        if (s[x] >= 'a' && s[x] <= 'z')
            s[x] ^= ' ';
}

pair<int,int> get(const string &r) {
    int a = 0, b = r.length();
    REP(x,b) {
        if (r[x] == 'R') ++a;
    }
    return make_pair(a, b);
}

void dfs(int u) {
    visited[u] = true;

    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (!visited[v]) {
            dfs(v);
        }

        f[u] = min(f[u], f[v]);
    }
}

#define SIZE(x) ((int) (x).size())

void tarjanSCC(int u) {
    dfs_low[u] = dfs_num[u] = dfsNumberCounter++;
    S.PB(u);
    visited[u] = 1;
    REP (j, SIZE(ke[u])) {
        int v = ke[u][j];
        if (dfs_num[v] == -1) tarjanSCC(v);
        if (visited[v]) dfs_low[u] = min(dfs_low[u], dfs_low[v]);
    }
    if (dfs_low[u] == dfs_num[u]) {
        ++numSCC;
        // printf("SCC %d:", ++numSCC);
        vector<int> cur;
        pair<int,int> res = f[u];
        while (1) {
            int v = S.back(); S.pop_back(); visited[v] = 0;
            // printf(" %d", v);
            cur.push_back(v);
            res = min(res, f[v]);
            if (u == v) break;
        }
        REP(x,cur.size()) {
            int v = cur[x];
            f[v] = min(f[v], res);
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m) {
        init();

        FOR(i,1,m) {
            cin >> a[i];
            upcase(a[i]);
            store(a[i]);
        }

        cin >> n;
        FOR(i,1,n) {
            cin >> l[i] >> r[i];
            upcase(l[i]); store(l[i]);
            upcase(r[i]); store(r[i]);

            ke[id[l[i]]].push_back(id[r[i]]);
        }

        FOR(i,1,nId) {
            f[i] = get(idToStr[i]);
        }

        FOR(i,1,nId) {
            if (!visited[i]) {
                dfs(i);
            }
        }

        memset(visited, 0, sizeof visited);
        FOR(i,1,nId) {
            if (dfs_num[i] < 0) {
                tarjanSCC(i);
            }
        }

        memset(visited, 0, sizeof visited);

        FOR(i,1,nId) {
            if (!visited[i]) {
                dfs(i);
            }
        }

        FOR(i,1,nId) {
            // cout << idToStr[i] << ' ' << f[i].first << ' ' << f[i].second << endl;
        }

        long long x = 0, y = 0;
        FOR(i,1,m) {
            x += f[id[a[i]]].first;
            y += f[id[a[i]]].second;
        }
        cout << x << ' ' << y << endl;
    }
    return 0;
}
