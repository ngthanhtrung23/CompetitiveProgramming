
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

ll a[66], res[66];
int visited[66][66];
int trone[66][66];
int trx[66][66];

int nbit[66], n, k;

int length(ll x) {
    int res = 0;
    if (x == 0LL) return 1;
    while (x > 0) {
        ++res;
        x /= 2;
    }
    return res;
}

ll sum;
void trace(int u2, int one2) {
    assert(visited[u2][one2]);
    if (u2 == 0) return ;
    int u = u2 - 1;
    int one = trone[u2][one2];

    trace(u, one);

    int x = trx[u2][one2];
    int y = nbit[u2] - x;

    res[u2] = 0;
    REP(i,k) {
        int t = (sum >> i) & 1LL;
        if (t) {
            if (x) {
                --x;
                res[u2] ^= 1LL << i;
            }
        }
        else {
            if (y) {
                --y;
                res[u2] ^= 1LL << i;
            }
        }
    }
    assert(x == 0);
    assert(y == 0);

    sum ^= res[u2];
    assert(__builtin_popcountll(sum) == one2);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);

    freopen("xor.in", "r", stdin);
    freopen("xor.out", "w", stdout);

    while (cin >> n) {
        k = 0;
        FOR(i,1,n) {
            cin >> a[i];
            nbit[i] = __builtin_popcountll(a[i]);
            k = max(k, length(a[i]));
        }
//        DEBUG(k);
//        PR(nbit, n);

        queue<int> qu, qone;
        qu.push(0); qone.push(0);
        memset(visited, 0, sizeof visited);
        visited[0][0] = 1;

        while (!qu.empty()) {
            int u = qu.front(); qu.pop();
            int one = qone.front(); qone.pop();
            int zero = k - one;
            if (u == n) continue;

            int cur = nbit[u+1];
            FOR(x,0,min(one,cur)) {
                int u2 = u + 1;
                int y = cur - x;
                if (y < 0 || zero < y) continue;

                int one2 = one - x + y;

                if (!visited[u2][one2]) {
                    visited[u2][one2] = true;
                    qu.push(u2);
                    qone.push(one2);

                    trone[u2][one2] = one;
                    trx[u2][one2] = x;
                }
            }
        }

        if (!visited[n][0]) {
            cout << "impossible" << endl;
        }
        else {
            sum = 0;
            trace(n, 0);
            FOR(i,1,n) cout << res[i] << ' '; cout << endl;

            assert(sum == 0);
            FOR(i,1,n) {
                assert(__builtin_popcountll(res[i]) == __builtin_popcountll(a[i]));
            }
        }
    }
}
