
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;

int n, m;
int eu[MN], ev[MN];
int vao[MN];
vector<int> ke[MN];

bool check(int m) {
    FOR(i,1,n) {
        ke[i].clear();
        vao[i] = 0;
    }
    FOR(i,1,m) {
        int u = eu[i], v = ev[i];
        vao[v]++;
        ke[u].push_back(v);
    }

    queue<int> qu;
    FOR(i,1,n) if (vao[i] == 0) qu.push(i);

    REP(turn,n) {
        if (SZ(qu) != 1) return false;
        int u = qu.front(); qu.pop();

        for(int v : ke[u]) {
            --vao[v];
            if (vao[v] == 0) qu.push(v);
        }
    }
    return true;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%lld%lld", &n, &m) == 2) {
        FOR(i,1,m) scanf("%lld%lld", &eu[i], &ev[i]);
        if (!check(m)) {
            puts("-1");
        }
        else {
            int l = 1, r = m, res = m;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (check(mid)) res = mid, r = mid - 1;
                else l = mid + 1;
            }
            printf("%lld\n", res);
        }
    }
}
