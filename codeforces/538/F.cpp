
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

const int MN = 200111;

int a[MN];
pair<int,int> x[MN];
vector< pair<pair<int,int>,int> > queries[MN];
int bit[MN];
long long res[MN];

#define _(X) ((X) & (-(X)))

int get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}
void update(int u) {
    while (u < MN) {
        ++bit[u];
        u += _(u);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            x[i] = make_pair(a[i], i);
        }
        sort(x+1, x+n+1);
        memset(bit, 0, sizeof bit);

        FOR(k,1,n-1) {
            FOR(i,1,n) {
                int from = k*(i-1) + 2;
                int to = k*i + 1;

                if (from > n) break;
                if (to > n) to = n;

                queries[i].push_back(make_pair(make_pair(from, to), k));
            }
        }

        memset(res, 0, sizeof res);
        FOR(turn,1,n) {
            int i = x[turn].second;
            for(auto p : queries[i]) {
                res[p.second] += get(p.first.second) - get(p.first.first - 1);
            }
            update(i);
        }
        FOR(k,1,n-1) printf("%d ", res[k]); puts("");
    }
    return 0;
}
