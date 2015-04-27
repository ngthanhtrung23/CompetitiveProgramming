
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

const int MN = 50111;
vector<int> ke[MN];
string s;
int n, q, qu[MN], first, last, visited[MN];

int main() {
    ios :: sync_with_stdio(false);
    int test; cin >> test;
    while (test--) {
        cin >> n >> q;
        FOR(i,1,n) ke[i].clear();

        cin >> s;
        s = " " + s;
        for(int i = 1, j = n; i < j; i++, j--) {
            ke[i].push_back(j);
            ke[j].push_back(i);
        }

        while (q--) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        memset(visited, 0, sizeof visited);
        long long res = 1;
        FOR(i,1,n) if (!visited[i]) {
            first = last = 1;
            qu[1] = i;
            visited[i] = true;

            while (first <= last) {
                int u = qu[first++];
                for(int v : ke[u]) {
                    if (!visited[v]) {
                        qu[++last] = v;
                        visited[v] = true;
                    }
                }
            }

            char cur = '?';
            FOR(x,1,last) {
                int u = qu[x];
                if (s[u] != '?') {
                    if (cur == '?') cur = s[u];
                    else if (cur != s[u]) res = 0;
                }
            }

            if (cur == '?')
                res = (res * 26) % 1000000007;
        }
        cout << res << endl;
    }
    return 0;
}
