
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 200111;
char s[MN];
ll h[20][1000111], p[1000111];
int to[20][1000111];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    p[0] = 1; FOR(i,1,MN-1) p[i] = p[i-1] * 31LL;

    int a, c, k, m, n;
    while (scanf("%d%d%d%d%d\n", &a, &c, &k, &m, &n) == 5) {
        scanf("%s\n", &s[1]);
        ll need = 0;
        FOR(i,1,n) if (s[i] == '1') need += p[i];

        REP(i,m) {
            ll z = i;
            z = ((z * a + c) / k) % m;

            to[0][i] = z;
            if (z < (m>>1)) h[0][i] = 0;
            else h[0][i] = p[1];
        }

        FOR(t,1,16) {
            REP(x,m) {
                // x -- [2^(t-1)] --> y
                int y = to[t-1][x];

                // y -- [2^(t-1)] --> z
                int z = to[t-1][y];

                to[t][x] = z;
                h[t][x] = h[t-1][x] + h[t-1][y] * p[1<<(t-1)];
            }
        }
        int res = 0;
        REP(x,m) {
            int mult = 0, z = x;
            ll hash = 0;
            FORD(t,16,0) if ((n >> t) & 1) {
                hash = hash + h[t][z] * p[mult];
                z = to[t][z];
                mult += 1<<t;
            }
            if (hash == need) ++res;
        }
        printf("%d\n", res);
    }
}
