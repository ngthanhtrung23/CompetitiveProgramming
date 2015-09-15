
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

const int MN = 100111;

int l, n;
string s;
int mat[MN], a[MN];
ll sz[MN], res;
vector<int> ke[MN];

int gen(int l, int r) {
    int cur = ++n;
    a[cur] = r - l + 1;
    int i = l + 1;

    while (i < r) {
        int j = mat[i];

        int v = gen(i, j);
        ke[cur].push_back(v);

        i = j + 1;
    }
    return cur;
}

void dfs(int u) {
    sz[u] = 0;
    for(int v : ke[u]) {
        dfs(v);

        res += a[u] * sz[u] * sz[v];

        sz[u] += sz[v];
    }
    sz[u] += 1;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> s) {
        l = s.length(); s = " " + s;
        FOR(i,1,l) ke[i].clear();
        stack<int> st;
        FOR(i,1,l) {
            if (s[i] == '(') {
                st.push(i);
            }
            else {
                int u = st.top(); st.pop();
                mat[u] = i;
                mat[i] = u;
            }
        }
//        PR(mat, l);
        n = 0;
        int root = gen(1, l);

        res = 0;
        memset(sz, 0, sizeof sz);
        dfs(root);
        cout << res << endl;
    }
}
