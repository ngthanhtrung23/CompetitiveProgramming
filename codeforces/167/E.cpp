
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

const int MN = 611;
int n, m;
long long p;
int in[MN], out[MN];
int cnt[MN][MN];
long long c[MN][MN];
vector<int> ke[MN], rev[MN];

long long power(long long x, int k) {
    if (k == 0) return 1;
    if (k == 1) return x % p;
    long long mid = power(x * x % p, k >> 1);
    if (k & 1) return mid * x % p;
    else return mid;
}

long long inverse(long long x) {
    return power(x, p - 2);
}

int f[MN];

int dfs(int u) {
    if (f[u] >= 0) return f[u];
    f[u] = 0;
    for(int v : rev[u]) {
        f[u] = (f[u] + dfs(v)) % p;
    }
    return f[u];
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d%d", &n, &m, &p) == 3) {
//        cout << "-------------------\n";
        FOR(i,1,n) {
            in[i] = out[i] = 0;
            ke[i].clear();
            rev[i].clear();
        }
        
        // Use Floyd to calculate cnt[i][j] = number of path from i --> j
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            out[u]++;
            in[v]++;
            ke[u].push_back(v);
            rev[v].push_back(u);
        }
        FOR(i,1,n) if (in[i] == 0 && out[i]) {
            memset(f, -1, sizeof f);
            FOR(j,1,n) if (in[j] == 0 && out[j])
                if (j == i) f[j] = 1;
                else f[j] = 0;

            FOR(j,1,n) if (in[j] && out[j] == 0)
                cnt[i][j] = dfs(j);
        }

//        FOR(i,1,n) FOR(j,1,n) cout << cnt[i][j] << " \n"[j == n];

        // Init c matrix for all sources & sinks
        int nSource = 0;
        FOR(i,1,n) if (in[i] == 0 && out[i]) {
            ++nSource;
            int nSink = 0;
            FOR(j,1,n) if (out[j] == 0 && in[j]) {
                c[nSource][++nSink] = cnt[i][j];
            }
        }
//        FOR(i,1,nSource) FOR(j,1,nSource) cout << c[i][j] << " \n"[j == nSource];

        int bad = 0;
        FOR(i,1,n) if (in[i] == 0 && out[i] == 0) {
            int a = 0, b = 0;
            FOR(source,1,i-1) if (in[source] == 0 && out[source]) ++a;
            FOR(sink,1,i-1) if (in[sink] && out[sink] == 0) ++b;
            if (a % 2 != b % 2) ++bad;
        }
        bad %= 2;

        // Floyd to calculate determinant
        n = nSource;
        // Swap 2 rows --> multiply by -1
        // Multiply 1 row by k --> multiply by k
        long long mult = 1;

        FOR(j,1,n) {
            // now we will normalize column j
            // first, choose the row k that maximize c[k][j], so that it
            // will be different from 0
            int chosen = j;
            FOR(k,j+1,n)
                if (c[k][j] > c[chosen][j]) chosen = k;

            if (chosen != j) {
                // swap 2 rows
                bad = 1 - bad;
                FOR(k,1,n) swap(c[chosen][k], c[j][k]);
            }

            FOR(i,j+1,n) {
                // multiply row i by c[j][j]
                // multiply row j by c[i][j]

                long long mult_i = c[j][j], mult_j = c[i][j];
                mult = (mult * mult_i) % p;

                FOR(k,1,n)
                    c[i][k] = (c[i][k] * mult_i - c[j][k] * mult_j + p*p) % p;
            }
        }

        long long res = 1;
        FOR(i,1,n) res = res * c[i][i] % p;
        if (bad) res = (p - res) % p;

        res = res * inverse(mult) % p;
        cout << res << endl;
    }
    return 0;
}
