#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int cnt[2][311];
int n[2];

struct Node {
    int child[26];
} nodes[2][100111];
int nNode[2];

int dfs(int t, int u) {
    int res = 1;
    REP(c,26) {
        if (nodes[t][u].child[c]) {
            res += dfs(t, nodes[t][u].child[c]);
            if (u) ++cnt[t][c];
        }
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n[0] >> n[1] && n[0]) {
        memset(cnt, 0, sizeof cnt);
        memset(nodes, 0, sizeof nodes);

        nNode[0] = nNode[1] = 1;
        REP(turn,2) {
            REP(i,n[turn]) {
                string a; cin >> a;
                if (turn == 1) reverse(a.begin(), a.end());

                int p = 0;
                for(char c : a) {
                    if (!nodes[turn][p].child[c - 'a']) {
                        nodes[turn][p].child[c - 'a'] = nNode[turn]++;
                    }
                    p = nodes[turn][p].child[c - 'a'];
                }
            }
        }

        long long res = 0;
        res += (dfs(0, 0) - 1LL) * (dfs(1, 0) - 1LL);
        REP(c,26) res -= cnt[0][c] * cnt[1][c];
        cout << res << endl;
    }
    return 0;
}

