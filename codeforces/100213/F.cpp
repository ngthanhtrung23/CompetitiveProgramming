
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

const ll MOD = 1e9 + 7;
const int MN = 44;

struct Hash {
    ll x, y;

    Hash() {}
    Hash(ll x, ll y) : x(x), y(y) {}

    Hash operator + (const Hash& a) const { return Hash(x+a.x, (y+a.y) % MOD); }
    Hash operator - (const Hash& a) const { return Hash(x-a.x, (y-a.y+MOD) % MOD); }
    Hash operator * (const Hash& a) const { return Hash(x*a.x, y*a.y%MOD); }
    Hash operator * (ll k) { return Hash(x*k, y*k%MOD); }
};

bool operator < (const Hash& a, const Hash& b) {
    if (a.x != b.x) return a.x < b.x;
    return a.y < b.y;
}

int m[2], n[2];
char a[2][MN][MN];
Hash p[MN*MN];
Hash h[2][MN][MN];

map< Hash, pair<int,int> > all[MN][MN];

Hash getHash(int t, int i1, int j1, int i2, int j2) {
    return (h[t][i2][j2] - h[t][i2][j1-1] - h[t][i1-1][j2] + h[t][i1-1][j1-1])
        * p[40*(40-i2) + 40-j2];
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("money.in", "r", stdin);
    freopen("money.out", "w", stdout);

    p[0] = Hash(1, 1);
    FOR(i,1,MN*MN-1) p[i] = p[i-1] * 31;

    while (cin >> m[0] >> n[0]) {
        FOR(i,1,m[0]) FOR(j,1,n[0]) cin >> a[0][i][j];

        cin >> m[1] >> n[1];
        FOR(i,1,m[1]) FOR(j,1,n[1]) cin >> a[1][i][j];

        REP(t,2) {
            FOR(i,1,m[t]) FOR(j,1,n[t]) {
                h[t][i][j] = h[t][i-1][j] + h[t][i][j-1] - h[t][i-1][j-1]
                    + (p[40*i+j] * (a[t][i][j] - 'A' + 1));
            }
        }

        // build map of first image
        FOR(dx,1,m[0]) FOR(dy,1,n[0]) {
            all[dx][dy].clear();
            FOR(i,1,m[0]-dx+1)
                FOR(j,1,n[0]-dy+1) {
                    Hash cur = getHash(0, i, j, i+dx-1, j+dy-1);
                    all[dx][dy][cur] = make_pair(i, j);
                }
        }

        int best = 0, save_i1 = -1, save_i2 = -1, save_j1 = -1, save_j2 = -1, save_dx, save_dy;

        FOR(dx,1,m[1]) FOR(dy,1,n[1]) {
            FOR(i,1,m[1]-dx+1)
                FOR(j,1,n[1]-dy+1) {
                    Hash cur = getHash(1, i, j, i+dx-1, j+dy-1);
                    if (all[dx][dy].count(cur)) {
                        int now = dx * dy;
                        if (now > best) {
                            best = now;
                            save_dx = dx;
                            save_dy = dy;

                            save_i2 = i;
                            save_j2 = j;

                            save_i1 = all[dx][dy][cur].first;
                            save_j1 = all[dx][dy][cur].second;
                        }
                    }
                }
        }

        if (best == 0) { cout << 0 << ' ' << 0 << endl; continue; }
        cout << save_dx << ' ' << save_dy << endl;
        cout << save_i1 << ' ' << save_j1 << endl;
        cout << save_i2 << ' ' << save_j2 << endl;
    }
}

