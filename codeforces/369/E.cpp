
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

const int MN = 1000111;

int nSeg, nQuery;
int res[MN];
vector<int> segsAt[MN];
vector< pair<int,int> > queryAt[MN];
int bit[MN];

#define _(X) ((X) & (-(X)))
int get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

void update(int u, int val) {
    while (u < MN) {
        bit[u] += val;
        u += _(u);
    }
}

int cur[MN];
int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &nSeg, &nQuery) == 2) {
        FOR(i,1,nQuery) res[i] = nSeg;
        REP(i,MN) {
            segsAt[i].clear();
            queryAt[i].clear();
        }
        memset(bit, 0, sizeof bit);

        FOR(i,1,nSeg) {
            int l, r; scanf("%d%d", &l, &r);
            segsAt[l].push_back(r);
        }
        FOR(i,1,nQuery) {
            int k; scanf("%d", &k);
            FOR(j,1,k) scanf("%d", &cur[j]);
            int last = 0;
            FOR(j,1,k) {
                queryAt[last+1].push_back(make_pair(i, cur[j]-1));
                last = cur[j];
            }
            queryAt[last+1].push_back(make_pair(i, 1000000));
        }
        FORD(x,1000000,1) {
            REP(i,segsAt[x].size()) {
                int p = segsAt[x][i];
                update(p, 1);
            }
            REP(i,queryAt[x].size()) {
                pair<int,int> p = queryAt[x][i];
                res[p.first] -= get(p.second);
            }
        }
        FOR(i,1,nQuery) printf("%d\n", res[i]);
    }
}

