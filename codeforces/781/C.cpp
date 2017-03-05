
#include <sstream>
#include <fstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define PI (2 * acos((double)0))
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define y0 u9cqu3jioajc

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 400111;

int n;
vector<int> ke[MN];
int st[MN], top;
vector<int> tours[MN];
bool visited[MN];

void dfs(int u) {
    visited[u] = true;
    st[++top] = u;
    for(int v : ke[u]) {
        if (visited[v]) continue;
        dfs(v);
        st[++top] = u;
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        memset(visited, 0, sizeof visited);
        int m, k;
        GI(m); GI(k);

        FOR(i,1,n) ke[i].clear();
        FOR(i,1,k) tours[i].clear();

        FOR(i,1,m) {
            int u, v; GI(u); GI(v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        top = 0;
        dfs(1);
        int bound = (2*n + k - 1) / k;
        int clone = 1;


        FOR(i,1,top) {
            int u = st[i];
            tours[clone].push_back(u);
            if (SZ(tours[clone]) == bound) ++clone;
        }

        FOR(i,1,k) {
            if (tours[i].empty()) tours[i].push_back(1);
            printf("%lld", SZ(tours[i]));
            for(int x : tours[i]) printf(" %lld", x);
            puts("");
        }
    }
    return 0;
}
