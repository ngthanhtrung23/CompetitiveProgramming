
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 200111;

int n, tr[MN], f[MN];
vector<int> ke[MN];

void dfs1(int u, int fu) {
    for(int v : ke[u]) if (v != fu) {
        tr[v] = u;
        f[v] = f[u] + 1;

        dfs1(v, u);
    }
}

int farthest(int u) {
    FOR(i,1,n) tr[i] = 0;
    FOR(i,1,n) f[i] = 0;

    f[u] = 1;
    dfs1(u, -1);

    return max_element(f+1, f+n+1) - f;
}

vector<int> findDiam() {
    int u = farthest(1);
    int v = farthest(u);

    vector<int> res;
    int x = v;
    while (x != u) {
        res.push_back(x);
        x = tr[x];
    }
    res.push_back(u);
    return res;
}

int visited[MN];

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n;
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        auto cur = findDiam();
//        PR0(cur, cur.size());

        int covered = 0;
        FOR(i,1,n) visited[i] = 0;
        stack<int> st;

        for(int res = 0; res <= n; ++res) {
            if (res == 0) {
                int u = cur[0], v = cur.back();
                visited[u] = visited[v] = 1;
                covered = 2;
                st.push(u); st.push(v);
            }
            else {
                REP(turn,2) {
                    stack<int> next;
                    while (!st.empty()) {
                        int u = st.top(); st.pop();

                        for(int v : ke[u]) if (!visited[v]) {
                            visited[v] = true;
                            next.push(v);
                            ++covered;
                        }
                    }
                    st = next;
                }
            }
            if (covered == n) {
                int x = cur[res], y = cur[cur.size()-1-res];
                if (x == y) {
                    y = 1;
                    while (y == x) ++y;
                }
                cout << res << ' ' << x << ' ' << y << endl;
                break;
            }
        }
    }
}

