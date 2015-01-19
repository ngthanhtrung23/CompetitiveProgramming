#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define left __left
#define right __right
using namespace std;

const int MK = 30;
const int MN = 200111;

long long f[MN][MK + 3], g[MN][MK + 3];
long long left[MK + 3], right[MK + 3];
int n;
vector<int> ke[MN];

void dfs(int u) {
    FOR(i,1,MK) {
        f[u][i] = i;
    }
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        dfs(v);

        FOR(i,1,MK) {
            f[u][i] += g[v][i];
        }
    }
    left[0] = right[MK+1] = 1000111000111000LL;
    FOR(i,1,MK) left[i] = min(left[i-1], f[u][i]);
    FORD(i,MK,1) right[i] = min(right[i+1], f[u][i]);

    FOR(i,1,MK) {
        g[u][i] = min(left[i-1], right[i+1]);
    }
    FOR(i,1,MK) {
        assert(f[u][i] >= i);
        assert(g[u][i] >= 1);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n;
        FOR(i,1,n) ke[i].clear();

        FOR(i,1,n) {
            int fi; cin >> fi;
            ke[fi].push_back(i);
        }

        dfs(1);

        cout << "Case #" << test << ": " << *min_element(f[1]+1, f[1]+MK+1) << "\n";
    }
    return 0;
}
