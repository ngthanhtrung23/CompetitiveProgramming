
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;
const ll P = 1e6 + 3;
#define hash hash___

vector<int> ke[MN];
vector<int> h[MN];
map<ll,int> id;
int hash[MN];
int n;

void dfs(int u) {
    if (ke[u].empty()) {
        hash[u] = 1;
        return ;
    }
    for(int v : ke[u]) {
        dfs(v);
        h[u].push_back(hash[v]);
    }
    sort(h[u].begin(), h[u].end());
    ll sum = 0;
    for(int x : h[u]) {
        sum = sum * P + x;
    }
    if (!id.count(sum)) {
        int cur = SZ(id) + 1;
        id[sum] = cur;
    }
    hash[u] = id[sum];
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("tree.in", "r", stdin);
    freopen("tree.out", "w", stdout);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();
        id.clear();
        FOR(i,1,n) h[i].clear();

        FOR(i,2,n) {
            int pi; scanf("%d", &pi);
            ke[pi].push_back(i);
        }
        id[0] = 1;
        dfs(1);

        FOR(i,1,n) printf("%d ", hash[i]);
    }
}
