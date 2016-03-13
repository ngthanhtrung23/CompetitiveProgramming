
#include <bits/stdc++.h>
#define int long long
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
const int BLOCK = 511;

int blockId[MN], a[MN], lastInBlock[MN], cntBlock[MN];
int n, q;

pair<int,int> get(int i) {
    int to = i + a[i];
    if (to > n) return make_pair(i, 0);
    else if (blockId[to] != blockId[i]) return make_pair(i, 0);
    else return make_pair(lastInBlock[to], cntBlock[to] + 1);
}

void init() {
    FOR(i,1,n) blockId[i] = i / BLOCK;
    FORD(i,n,1) {
        auto t = get(i);
        lastInBlock[i] = t.first;
        cntBlock[i] = t.second;
    }
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%lld%lld", &n, &q) == 2) {
        FOR(i,1,n) scanf("%lld", &a[i]);
        init();
        while (q--) {
            int typ; scanf("%lld", &typ);
            if (typ == 0) {
                int u, val; scanf("%lld%lld", &u, &val);
                int b = blockId[u];
                a[u] = val;
                FORD(i,u,1) {
                    if (blockId[i] != b) break;
                    auto t = get(i);
                    lastInBlock[i] = t.first;
                    cntBlock[i] = t.second;
                }
            }
            else {
                int u; scanf("%lld", &u);
                int res = 0;
                while (true) {
                    // we go to last position in u 's block
                    res += cntBlock[u];
                    u = lastInBlock[u];

                    // from here we try to go to next block
                    int to = u + a[u];
                    ++res;
                    if (to > n) break;

                    u = to;
                }
                printf("%lld %lld\n", u, res);
            }
        }
    }
}
