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
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 600111;
vector< pair<string,string> > at[MN];
int in[MN], out[MN];
int n, cnt;
vector<int> ke[MN];
map<long long,string> it[MN * 4];

#define hash hash_
inline long long hash(const string &s) {
    long long res = 0;
    REP(i,s.length()) res = res * 301 + s[i];
    return res;
}

void init() {
    FOR(i,1,n) {
        ke[i].clear(); at[i].clear();
    }
    FOR(i,1,4*n) it[i].clear();
    cnt = 0;
}

string tmp;
void read() {
    FOR(i,1,n) {
        int par, k;
        cin >> par >> k;
        ke[par].push_back(i);

        at[i].resize(k);
        REP(j,k) {
            cin >> tmp;
            REP(x,tmp.length()) if (tmp[x] == '=') {
                at[i][j].first = tmp.substr(0, x);
                at[i][j].second = tmp.substr(x+1);
                break;
            }
        }
    }
}

void dfs(int u) {
    in[u] = ++cnt;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        dfs(v);
    }
    out[u] = ++cnt;
}

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)
void update(int i, int l, int r, int u, int v, const long long &key, const string &value) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i][key] = value;
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, v, key, value);
    update(CP(i), mid+1, r, u, v, key, value);
}

void dfs2(int u) {
    REP(x,at[u].size()) {
        update(1, 1, n+n, in[u], out[u], hash(at[u][x].first), at[u][x].second);
    }
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        dfs2(v);
    }
}

string result;
void get(int i, int l, int r, int u, const long long &key) {
    if (u < l || r < u) return ;

    if (it[i].count(key)) result = it[i][key];
    if (l == r) return ;

    int mid = (l + r) >> 1;
    get(CT(i), l, mid, u, key);
    get(CP(i), mid+1, r, u, key);
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        init();
        read();
        dfs(1);
        // PR(in, n);
        // PR(out, n);

        dfs2(1);
        int q = 0;
        cin >> q;
        while (q--) {
            int u;
            string s;
            cin >> u >> s;

            result = "N/A";
            get(1, 1, n+n, in[u], hash(s));
            cout << result << endl;
        }
    }
    return 0;
}
