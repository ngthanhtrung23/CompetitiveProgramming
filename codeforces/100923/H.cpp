#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;

int up[MN]; // parent in disjoint set
int same[MN]; // does u have same color as up[u]?

pair<int,int> getRoot(int u) {
    // returns: (root, same color as root?)

    if (up[u] < 0) return make_pair(u, 1);

    auto t = getRoot(up[u]);
    if (!same[u]) t.second ^= 1;

    return t;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("meciul.in", "r", stdin);
    freopen("meciul.out", "w", stdout);

    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        int n, m; scanf("%d%d", &n, &m);

        FOR(i,1,n) {
            up[i] = -1;
            same[i] = 1;
        }
        while (m--) {
            int u, v; scanf("%d%d", &u, &v);

            auto tu = getRoot(u);
            auto tv = getRoot(v);

            if (tu.first == tv.first) {
                if (tu.second == tv.second) puts("NO");
                else puts("YES");
            }
            else {
                if (up[tu.first] > up[tv.first]) {
                    swap(u, v);
                    swap(tu, tv);
                }

                int ru = tu.first;
                int rv = tv.first;

                up[ru] += up[rv];
                up[rv] = ru;

                same[rv] = tu.second ^ tv.second;
                puts("YES");
            }
        }
    }
}
