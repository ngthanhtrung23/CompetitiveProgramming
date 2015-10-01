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

const int MN = 55;
int N, H, S, P, M;
int s[MN], p[MN], m[MN];

int f[55][55][55], tra[55][55][55], trb[55][55][55], trc[55][55][55], tr[55][55][55];

void update(int i, int j, int k, int i2, int j2, int k2, int val, int typ) {
    if (f[i][j][k] < val) {
        f[i][j][k] = val;
        tr[i][j][k] = typ;

        tra[i][j][k] = i2;
        trb[i][j][k] = j2;
        trc[i][j][k] = k2;
    }
}

void trace(int i, int j, int k) {
    if (i == 0) return ;

    trace(i-1, trb[i][j][k], trc[i][j][k]);
    cout << (tr[i][j][k] == 0 ? 'D' : 'E');
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("princess.in", "r", stdin);
    freopen("princess.out", "w", stdout);

    while (cin >> N >> H >> S >> P >> M) {
        FOR(i,1,N) cin >> s[i] >> p[i] >> m[i];

        memset(f, -1, sizeof f);
        f[0][0][H] = M;
        FOR(i,0,N-1) FOR(x1,0,i) FOR(curH,1,H)
            if (f[i][x1][curH] >= 0) {
                int x2 = i - x1;
                
                int curS = S + x1;
                int curP = P + x2;
                int curM = f[i][x1][curH];

                // defeat
                int loseH = max(2*s[i+1] - curS, 0);
                if (curH > loseH && curS >= s[i+1]) {
                    update(i+1, x1+1, curH - loseH, i, x1, curH, curM, 0);
                }
                // enchant
                if (curP >= p[i+1] && curM >= m[i+1]) {
                    update(i+1, x1, curH, i, x1, curH, curM - m[i+1], 1);
                }
            }

        try {
            FOR(x1,0,N)
                FOR(curH,1,H)
                    if (f[N][x1][curH] >= 0) {
                        trace(N, x1, curH);
                        cout << endl;
                        throw 1;
                    }
            cout << "UNLUCKY" << endl;
        } catch (...) {
        }
    }
}
