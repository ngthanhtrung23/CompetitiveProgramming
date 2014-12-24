#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const long long MOD = 1000000007LL;

long long gt[100111];
long long c[1055][1055];
int f[1011][55][1011];

void add(int &x, int val) {
    x = (x + val) % MOD;
}

void init() {
    FOR(i,0,1050) {
        c[i][0] = 1;
        FOR(j,1,i)
            c[i][j] = (c[i-1][j] + c[i-1][j-1]) % MOD;
    }
    gt[0] = 1;
    FOR(i,1,100000) gt[i] = (gt[i-1] * i) % MOD;

    f[0][0][0] = 1;
    FOR(i,1,1000) {
        FOR(x,0,49) FOR(cur,0,1000)
            if (f[i-1][x][cur]) {
                add(f[i][x][cur], f[i-1][x][cur]);
                if (cur + i <= 1000)
                    add(f[i][x+1][cur+i], f[i-1][x][cur]);
            }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(6);
    init();
    int test; cin >> test;
    while (test--) {
        int n, k; cin >> n >> k;
        long long res = 0;
        if (k > 50) {
            cout << 0 << endl;
            continue;
        }
        FOR(sum,0,n) {
            res = (res + f[1000][k][sum] * gt[k] % MOD * c[n-sum+k][k]) % MOD;
        }
        cout << res << endl;
    }
    return 0;
}
