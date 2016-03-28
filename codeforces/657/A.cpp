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
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;
int n, h, d, x[MN], m;
pair<int,int> res[MN];

void addEdge(int u, int v) {
    res[++m] = make_pair(u, v);
}

#undef int
int main() {
#define int long long
    while (cin >> n >> d >> h) {
        if (h + h < d) {
            cout << -1 << endl;
            continue;
        }
        if (d == 1 && n > 2) {
            cout << -1 << endl;
            continue;
        }
        m = 0;
        int cur = 2;
        FOR(i,1,d+1) {
            if (i == h+1) x[i] = 1;
            else x[i] = cur++;
        }

        FOR(i,1,d) addEdge(x[i], x[i+1]);
        FOR(i,d+2,n) addEdge(x[2], i);

        FOR(i,1,m) printf("%lld %lld\n", res[i].first, res[i].second);
    }
}
