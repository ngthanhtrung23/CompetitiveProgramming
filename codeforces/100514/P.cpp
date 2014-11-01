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

const int MN = 100111;
int n, a[MN], deg[MN];
string s;
vector<int> ke[MN];

void init() {
    FOR(i,1,n) ke[i].clear();
    FOR(i,1,n) deg[i] = 0;
}

int now = 0;
char code[MN];

void dfs(int u, int fu = -1) {
    code[u] = s[now++];
    for(auto v : ke[u]) {
        if (v == fu) continue;
        dfs(v, u);
    }
}

bool visited[MN];
void bfs(int u) {
    queue<int> qu;
    qu.push(u);
    memset(visited, false, sizeof visited); visited[u] = true;

    while (!qu.empty()) {
        u = qu.front(); qu.pop();
        cout << code[u];
        for(auto v : ke[u]) {
            if (!visited[v]) {
                visited[v] = true;
                qu.push(v);
            }
        }
    }
    cout << endl;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        cin >> s;
        FOR(i,1,n-2) cin >> a[i];
        init();
        set<int> zero;
        FOR(i,1,n-2) deg[a[i]]++;
        FOR(i,1,n) if (!deg[i]) zero.insert(i);

        FOR(i,1,n-2) {
            int u = *zero.begin();
            ke[u].push_back(a[i]);
            ke[a[i]].push_back(u);
            
            // cout << a[i] << ' ' << u << endl;
            
            zero.erase(u);
            --deg[a[i]];
            if (!deg[a[i]]) zero.insert(a[i]);
        }

        int u = *zero.begin(); zero.erase(zero.begin());
        int v = *zero.begin(); zero.erase(zero.begin());
        ke[u].push_back(v);
        ke[v].push_back(u);

        FOR(i,1,n) sort(ke[i].begin(), ke[i].end());

        now = 0;
        dfs(1);
        bfs(1);
    }
    return 0;
}
